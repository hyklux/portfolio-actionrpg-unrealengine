// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TypeDefine.h"
#include "GameplayTagContainer.h"
#include "CollisionComponent.generated.h"

DECLARE_DELEGATE_OneParam(FDelegate_OnHit, FHitResult);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBATSYSTEM_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionComponent();

private:
	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> CollisionMeshComponent;
	
	UPROPERTY()
	bool IsCollisionEnabled = false;
	
	UPROPERTY()
	TArray<AActor*> AlreadyHitActors;
	
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY()
	FHitResult LastHit;
	
public:
	UPROPERTY()
	FName StartSocketName;

	UPROPERTY()
	FName EndSocketName;

	UPROPERTY()
	float TRaceRadius = 20.0f;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectTypes{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };

	UPROPERTY()
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::None;
	
	UPROPERTY()
	AActor* HitActor;

	UPROPERTY()
		FGameplayTagContainer GameplayTagsToIgnore;

	UPROPERTY()
	TArray<TSubclassOf<AActor>> ActorClassToIgnore;

		FDelegate_OnHit OnHitDelegate;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetAlreadyHitActors() const;
	
	UFUNCTION(BlueprintCallable)
	bool GetIsCollisionEnabled() const;
	
	UFUNCTION(BlueprintCallable)
	FHitResult GetLastHit() const;

	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetCollisionMeshComponent() const;
	
	UFUNCTION(BlueprintCallable)
	void AddActorToIgnore(AActor* inActor);

	UFUNCTION(BlueprintCallable)
	void RemoveActorToIgnore(AActor* actorToRemove);

	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetActorsToIgnore() const;

	UFUNCTION(BlueprintCallable)
	void CollisionTrace();

	UFUNCTION(BlueprintCallable)
	void SetCollisionMesh(UPrimitiveComponent* meshComponent);

	UFUNCTION(BlueprintCallable)
	void ClearHitActors();

	UFUNCTION(BlueprintCallable)
	void ActivateCollision();

	UFUNCTION(BlueprintCallable)
	void DeactivateCollision();

	UFUNCTION()
		bool CanHitActor(AActor* inActor);
}; 
