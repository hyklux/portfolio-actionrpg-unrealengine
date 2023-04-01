// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicEquippable.generated.h"

class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class MELEECOMBATSYSTEM_API ABasicEquippable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEquippable();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ItemSkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ItemStaticMesh;

	UPROPERTY(VisibleAnywhere)
	FName AttachSocketName;

	UPROPERTY(VisibleAnywhere)
	bool IsEquipped = false;

public:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPrimitiveComponent* GetItemMesh();
	void AttachActor(FName socketName);
	virtual void OnEquipped();
	virtual void OnUnequipped();
	void SetIsEquipped(bool isEquipped);
	bool GetIsEquipped() const;
};
