// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetingComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerController = OwnerCharacter->GetController();
	FollowCamera = Cast<UCameraComponent>(OwnerCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
}

void UTargetingComponent::EnableLockOn()
{
	AActor* foundTargetActor;
	bool isFound = FindTarget(foundTargetActor);

	if (isFound && CanTargetActor(foundTargetActor))
	{
		SetTargetActor(foundTargetActor);
		SetIsTargeting(true);
		UpdateRotationMode();
	}
}

void UTargetingComponent::DisableLockOn()
{
	SetIsTargeting(false);
	SetTargetActor(nullptr);
	UpdateRotationMode();
}

void UTargetingComponent::ToggleLockOn()
{
	if (GetIsTargeting())
	{
		DisableLockOn();
	}
	else
	{
		EnableLockOn();
	}
}

// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsTargeting)
	{
		UpdateTargetingControlRotation();
	}
}

void UTargetingComponent::SetIsTargeting(bool enableTargeting)
{
	IsTargeting = enableTargeting;
}

bool UTargetingComponent::GetIsTargeting() const
{
	return IsTargeting;
}

bool UTargetingComponent::FindTarget(AActor*& foundTarget)
{
	FVector start = GetOwner()->GetActorLocation();
	FVector end = FollowCamera->GetForwardVector() * TargetingDistance + GetOwner()->GetActorLocation();
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Push(GetOwner());
	FHitResult outHit;

	bool isHit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), start, end, TargetingRadius, TargetObjectTypes, false, actorsToIgnore, EDrawDebugTrace::ForDuration, outHit, false);
	if (isHit && outHit.GetActor())
	{
		foundTarget = outHit.GetActor();
		return true;
	}

	return false;
}

void UTargetingComponent::SetTargetActor(AActor* newTargetActor)
{
	TargetActor = newTargetActor;
}

AActor* UTargetingComponent::GetTargetActor() const
{
	return TargetActor;
}

void UTargetingComponent::UpdateTargetingControlRotation()
{
	if (IsValid(OwnerCharacter) && IsValid(TargetActor))
	{
		if (CanTargetActor(TargetActor))
		{
			const FRotator currRotation = Cast<AActor>(OwnerController)->GetActorRotation();
			const FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), TargetActor->GetActorLocation() - FVector(0.0f, 0.0f, 100.0f));
			const FRotator newRotation = FMath::RInterpTo(currRotation, lookAtRotation, UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), TargetRotationInterpSpeed);

			FRotator rotation;
			rotation.Roll = currRotation.Roll;
			rotation.Pitch = newRotation.Pitch;
			rotation.Yaw = newRotation.Yaw;
			OwnerController->SetControlRotation(rotation);
		}
		else
		{
			DisableLockOn();
		}
	}
}

void UTargetingComponent::SetRotationMode(ERotationMode newRotationMode)
{
	CurrentRotationMode = newRotationMode;

	switch (CurrentRotationMode)
	{
	case ERotationMode::OrientToCamera:
	{
		OwnerCharacter->bUseControllerRotationYaw = false;
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	break;
	case ERotationMode::OrientToMovement:
	{
		OwnerCharacter->bUseControllerRotationYaw = false;
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	break;
	default:
		break;
	}
}

ERotationMode UTargetingComponent::GetRotationMode() const
{
	return CurrentRotationMode;
}

bool UTargetingComponent::CanTargetActor(AActor* inTargetActor)
{
	if (IsValid(inTargetActor))
	{
		return GetOwner()->GetDistanceTo(inTargetActor) > TargetingDistance;
	}

	return false;
}

void UTargetingComponent::UpdateRotationMode()
{
	if (!IsValid(OwnerCombatComponent))
	{
		OwnerCombatComponent = Cast<UCombatComponent>(OwnerCharacter->GetComponentByClass(UCombatComponent::StaticClass()));
	}
	
	EMovementSpeedMode speedMode = EMovementSpeedMode::Sprinting; //khy todoa

	if (speedMode != EMovementSpeedMode::Sprinting
		&& OwnerCombatComponent->IsCombatEnabled()
		&& GetIsTargeting())
	{
		SetRotationMode(ERotationMode::OrientToCamera);
	}
	else
	{
		SetRotationMode(DefaultRotationMode);
	}
}
