// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionComponent.h"

// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
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
			if (!AlreadyHitActors.Contains(hit.GetActor()))
			{
				AlreadyHitActors.Push(hit.GetActor());
			}
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

