// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"
#include "GameplayTagInterface.h"
#include "Kismet/GameplayStatics.h"

UCollisionComponent::UCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsCollisionEnabled)
	{
		CollisionTrace();
	}
}

TArray<AActor*> UCollisionComponent::GetAlreadyHitActors() const
{
	return AlreadyHitActors;
}

bool UCollisionComponent::GetIsCollisionEnabled() const
{
	return IsCollisionEnabled;
}

FHitResult UCollisionComponent::GetLastHit() const
{
	return LastHit;
}

UPrimitiveComponent* UCollisionComponent::GetCollisionMeshComponent() const
{
	return CollisionMeshComponent;
}

void UCollisionComponent::AddActorToIgnore(AActor* inActor)
{
	ActorsToIgnore.Push(inActor);
}

void UCollisionComponent::RemoveActorToIgnore(AActor* actorToRemove)
{
	ActorsToIgnore.Remove(actorToRemove);
}

TArray<AActor*> UCollisionComponent::GetActorsToIgnore() const
{
	return ActorsToIgnore;
}

void UCollisionComponent::CollisionTrace()
{
	FVector start = CollisionMeshComponent->GetSocketLocation(StartSocketName);
	FVector end = CollisionMeshComponent->GetSocketLocation(EndSocketName);
	TArray<FHitResult> outHits;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, TRaceRadius, CollisionObjectTypes, false, ActorsToIgnore, DrawDebugType, outHits, false);
	if (isHit)
	{
		for (FHitResult hit : outHits)
		{
			LastHit = hit;
			AActor* hitActor = LastHit.GetHitObjectHandle().FetchActor();
			if (IsValid(hitActor) && CanHitActor(hitActor))
			{
				HitActor = hitActor;
			}

			if (!AlreadyHitActors.Contains(HitActor))
			{
				AlreadyHitActors.Push(HitActor);
			}

			OnHitDelegate.ExecuteIfBound(hit);
		}
	}
}

void UCollisionComponent::SetCollisionMesh(UPrimitiveComponent* meshComponent)
{
	CollisionMeshComponent = meshComponent;
}

void UCollisionComponent::ClearHitActors()
{
	AlreadyHitActors.Empty();
}

void UCollisionComponent::ActivateCollision()
{
	ClearHitActors();
	IsCollisionEnabled = true;
}

void UCollisionComponent::DeactivateCollision()
{
	IsCollisionEnabled = false;
}

bool UCollisionComponent::CanHitActor(AActor* inActor)
{
	IGameplayTagInterface* gameplayTagInterface = Cast<IGameplayTagInterface>(inActor);
	if (!gameplayTagInterface)
	{
		return false;
	}

	FGameplayTagContainer tagContainer = gameplayTagInterface->GetOwnedGameplayTags();

	bool isGameplaTagToIgnore = tagContainer.HasAnyExact(GameplayTagsToIgnore);
	bool isAlreadyHitActor = AlreadyHitActors.Contains(inActor);
	bool isActorClassToIgnore = ActorClassToIgnore.Contains(inActor->GetClass());

	return !isGameplaTagToIgnore && !isAlreadyHitActor && !isActorClassToIgnore;
}