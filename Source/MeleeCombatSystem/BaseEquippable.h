// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagInterface.h"
#include "GameplayTagContainer.h"
#include "BaseEquippable.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class MELEECOMBATSYSTEM_API ABaseEquippable : public AActor, public IGameplayTagInterface
{
	GENERATED_BODY()
	
public:	
	ABaseEquippable();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* ItemSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ItemStaticMesh;

	FGameplayTagContainer OwnedGameplayTags;

	UPROPERTY(EditAnywhere)
		FName AttachSocketName;

	UPROPERTY(VisibleAnywhere)
		bool IsEquipped = false;
	
public:
	virtual void Tick(float DeltaTime) override;

	virtual FGameplayTagContainer GetOwnedGameplayTags() override;
	virtual bool HasMatchingGameplayTag(FGameplayTag inTagToCheck) override;

	UPrimitiveComponent* GetItemMesh();
	void AttachActor(FName socketName);
	virtual void OnEquipped();
	virtual void OnUnequipped();
	void SetIsEquipped(bool isEquipped);
	bool GetIsEquipped() const;

protected:
	virtual void BeginPlay() override;

};
