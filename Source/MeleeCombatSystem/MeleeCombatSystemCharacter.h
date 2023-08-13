// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CombatComponent.h"
#include "MeleeCombatSystemCharacter.generated.h"

class UTargetingComponent;
class UStatsComponent;
class UStateManageComponent;
class UCombatComponent;
struct FGameplayTag;

UCLASS(config=Game)
class AMeleeCombatSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AMeleeCombatSystemCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
private:
	EMovementSpeedMode MovementSpeedMode = EMovementSpeedMode::Jogging;

public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//UTargetingComponent* TargetingComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//UStatsComponent* StatsComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//UStateManageComponent* StateManageComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//UCombatComponent* CombatComponent;

	float WalkingSpeed = 200.0f;
	float JoggingSpeed = 500.0f;
	float SprintingSpeed = 700.0f;

	float Health = 100.0f;
	FName PelvisBoneName = TEXT("Pelvis");
	bool IsHeavyAttack = false;
	float AttackHeldTime = 0.0f;
	float ChargeAttackTime = 0.0f;
	bool IsAttackCharge = false;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void SetMovementSpeedMode(EMovementSpeedMode newSpeedMode);
	EMovementSpeedMode GetCurrentSpeedMode() const;
	void PerformAttack(FGameplayTag gameplayTag, int AttackIndex, bool isRandomIndex);
	void PerformDodge(int MontageIndex, bool isRandomIndex);
	bool ResetChargeAttack();
	FGameplayTag GetDesiredAttackType();
	void SprintStaminaCost();
};

