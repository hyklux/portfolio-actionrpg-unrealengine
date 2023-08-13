// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEquippable.h"
#include "GameFramework/Character.h"

// Sets default values
ABasicEquippable::ABasicEquippable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
}

// Called when the game starts or when spawned
void ABasicEquippable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ABasicEquippable::GetItemMesh()
{
	return nullptr;
}

void ABasicEquippable::AttachActor(FName socketName)
{
	K2_AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), socketName, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
}

void ABasicEquippable::OnEquipped()
{
	IsEquipped = true;
	AttachActor(AttachSocketName);
}

void ABasicEquippable::OnUnequipped()
{
	if (IsEquipped)
	{
		IsEquipped = false;
	}
}

void ABasicEquippable::SetIsEquipped(bool isEquipped)
{
	IsEquipped = isEquipped;
}

bool ABasicEquippable::GetIsEquipped() const
{
	return IsEquipped;
}

