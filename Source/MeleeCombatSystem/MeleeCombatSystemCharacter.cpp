// Copyright Epic Games, Inc. All Rights Reserved.

#include "MeleeCombatSystemCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "TargetingComponent.h"
#include "StatsComponent.h"
#include "StateManageComponent.h"
#include "CombatComponent.h"
#include "BaseWeapon.h"
#include "Kismet/KismetSystemLibrary.h"


//////////////////////////////////////////////////////////////////////////
// AMeleeCombatSystemCharacter

AMeleeCombatSystemCharacter::AMeleeCombatSystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
	StatsComponent = CreateDefaultSubobject<UStatsComponent>(TEXT("StatsComponent"));
	StateManageComponent = CreateDefaultSubobject<UStateManageComponent>(TEXT("StateManageComponent"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
}

void AMeleeCombatSystemCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMeleeCombatSystemCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMeleeCombatSystemCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMeleeCombatSystemCharacter::Look);

	}

}

void AMeleeCombatSystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMeleeCombatSystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMeleeCombatSystemCharacter::SetMovementSpeedMode(EMovementSpeedMode newSpeedMode)
{
	if (MovementSpeedMode != newSpeedMode)
	{
		MovementSpeedMode = newSpeedMode;
		TargetingComponent->UpdateRotationMode();
		switch (MovementSpeedMode)
		{
		case EMovementSpeedMode::Walking:
			GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
			break;
		case EMovementSpeedMode::Jogging:
			GetCharacterMovement()->MaxWalkSpeed = JoggingSpeed;
			break;
		case EMovementSpeedMode::Sprinting:
			GetCharacterMovement()->MaxWalkSpeed = SprintingSpeed;
			break;
		default:
			break;
		}
	}
}

EMovementSpeedMode AMeleeCombatSystemCharacter::GetCurrentSpeedMode() const
{
	return MovementSpeedMode;
}

void AMeleeCombatSystemCharacter::PerformAttack(FGameplayTag gameplayTag, int AttackIndex, bool isRandomIndex)
{
	if (CombatComponent->IsCombatEnabled())
	{
		TArray<UAnimMontage*> attackMontages = CombatComponent->GetMainWeapon()->GetActionMontages(gameplayTag);
		UAnimMontage* attackMontage = attackMontages[AttackIndex];
		if (IsValid(attackMontage))
		{
			PlayAnimMontage(attackMontages[AttackIndex]);
			StateManageComponent->SetAction(gameplayTag);
			StateManageComponent->SetState(FGameplayTag::RequestGameplayTag(TEXT("Character.State.Attacking"), true));
		}
	}
}

void AMeleeCombatSystemCharacter::PerformDodge(int MontageIndex, bool isRandomIndex)
{
	UAnimMontage* animMontage = CombatComponent->GetMainWeapon()->DodgeMontages[MontageIndex];
	if (IsValid(animMontage))
	{
		PlayAnimMontage(animMontage);
		StateManageComponent->SetState(FGameplayTag::RequestGameplayTag(TEXT("Character.State.Dodge"), true));
		StateManageComponent->SetAction(FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Dodget"), true));
	}
}

bool AMeleeCombatSystemCharacter::ResetChargeAttack()
{
	UKismetSystemLibrary::K2_ClearTimer(this, TEXT("Charge Attack Timer Event"));
	AttackHeldTime = 0.0f;
	if (IsAttackCharge)
	{
		return true;
	}
	else
	{
		IsAttackCharge = false;
		return false;
	}
}

FGameplayTag AMeleeCombatSystemCharacter::GetDesiredAttackType()
{
	if (GetCharacterMovement()->IsFalling())
	{
		return FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Attack.FallingAttack"), true);
	}
	else
	{
		if (MovementSpeedMode == EMovementSpeedMode::Sprinting)
		{
			return FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Attack.SprintAttack"), true);
		}
		else
		{
			if (IsHeavyAttack)
			{
				return FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Attack.LightAttack"), true);

			}
			else
			{
				return FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Attack.HeavyAttack"), true);
			}
		}
	}

	return FGameplayTag();
}

void AMeleeCombatSystemCharacter::SprintStaminaCost()
{
	StatsComponent->ModifyCurrentStatValue(EStats::Stamina, -2.0f, true);
}