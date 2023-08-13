// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEquippable.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"

ABaseEquippable::ABaseEquippable()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMesh->SetupAttachment(DefaultSceneRoot);

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(DefaultSceneRoot);
}

void ABaseEquippable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FGameplayTagContainer ABaseEquippable::GetOwnedGameplayTags()
{
	return FGameplayTagContainer();
}

bool ABaseEquippable::HasMatchingGameplayTag(FGameplayTag inTagToCheck)
{
	return true;
}

UPrimitiveComponent* ABaseEquippable::GetItemMesh()
{
	return IsValid(ItemStaticMesh) ? ItemStaticMesh : Cast<UStaticMeshComponent>(ItemSkeletalMesh);
}

void ABaseEquippable::AttachActor(FName socketName)
{
	K2_AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(), socketName, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
}

void ABaseEquippable::OnEquipped()
{
	IsEquipped = true;
	AttachActor(AttachSocketName);
}

void ABaseEquippable::OnUnequipped()
{
	if (IsEquipped)
	{
		IsEquipped = false;
	}
}

void ABaseEquippable::SetIsEquipped(bool isEquipped)
{
	IsEquipped = isEquipped;
}

bool ABaseEquippable::GetIsEquipped() const
{
	return IsEquipped;
}

