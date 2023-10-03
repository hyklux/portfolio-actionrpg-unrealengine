# portfolio-actionrpg-unrealengine
Action RPG portfolio using Unreal Engine


Youtube Link : https://youtu.be/NV9-pcHnVTc


## Introduction
This is an Action RPG portfolio made with Unreal Engine.


I implemented the basic combat gameplay for a third person character.


![arpg1](https://user-images.githubusercontent.com/96270683/229277573-60205ff8-0400-4b84-bd82-76ed9fd2e4a8.PNG)


## Implementations
:heavy_check_mark: Character


:heavy_check_mark: Weapon


:heavy_check_mark: Combat


## Character
- CombatCharacter is the class for playable character.


![arpg6](https://user-images.githubusercontent.com/96270683/229285673-18cd72fc-40f0-4fd0-bb80-af2790987e77.PNG)
- Weapon Actors are mounted on SkeletonMesh's designated sockets.
- When a weapon is equipped, the CombatCharacter class becomes the owner of the Weapon class and loads information necessary for combat.
- The video below is the character's combat motion applied after equipping the weapon.


![arpg1_min](https://user-images.githubusercontent.com/96270683/229287431-f8f93287-0787-4d95-9975-3cbcb6a4b0e3.gif)


![arpg2_min](https://user-images.githubusercontent.com/96270683/229287735-5707c1a1-cecc-4d7f-ab5d-b1fe8dfdfa3d.gif)




## Weapon


### BaseWeapon
- All weapon classes are implemented by inheriting the BaseWeapon class.


![arpg2](https://user-images.githubusercontent.com/96270683/229282134-d7296db9-df8c-488e-be62-71448fbb9a6c.PNG)
- BaseWeapon defines animation data according to the weapon's attack type and attack data to be applied during battle.
``` c++
public:
	UPROPERTY()
	FName HandSocketName;
	UPROPERTY()
	ECombatType CombatType;
	UPROPERTY()
	UCombatComponent* CombatComponent;

	//Animation montage based on attack types
	UPROPERTY()
	TArray<UAnimMontage*> LightAttackMontages;
	UPROPERTY()
	TArray<UAnimMontage*> HeavyAttackMontages;
	UPROPERTY()
	TArray<UAnimMontage*> ChargeAttackMontages;
	UPROPERTY()
	TArray<UAnimMontage*> FallingAttackMontages;
	UPROPERTY()
	TArray<UAnimMontage*> SprintAttackMontages;
	UPROPERTY()
	TArray<UAnimMontage*> DodgeMontages;
	UPROPERTY()
	UAnimMontage* EnterCombatMontage;
	UPROPERTY()
	UAnimMontage* ExitCombatMontage;

	//Combat data
	UPROPERTY()
	float Damage;
	UPROPERTY()
	TMap<FGameplayTag, float> ActionStatCost;
	UPROPERTY()
	TMap<FGameplayTag, float> ActionDamageMultiplier;
```


### BP_ToughSword
- This is what the actual weapon class BP_ToughSword looks like.


![arpg3](https://user-images.githubusercontent.com/96270683/229283520-82812ffa-82f7-475b-a2fc-6da94f31b70d.PNG)
- Designate animations according to attack types such as LightAttack and HeavyAttack.


![arpg4](https://user-images.githubusercontent.com/96270683/229283564-6cfd2535-ee5a-4e45-801f-43823f85aae4.PNG)
- Set attack data such as Damage and ActionStatCost.


![arpg5](https://user-images.githubusercontent.com/96270683/229283590-fae7b03a-241f-4813-9f4e-0b8dacaf30d5.PNG)

## Character
- You define your playable character in the CombatCharacter class.


![arpg6](https://user-images.githubusercontent.com/96270683/229285673-18cd72fc-40f0-4fd0-bb80-af2790987e77.PNG)
- Weapon Actors are mounted on SkeletonMesh's designated sockets.
- When a weapon is equipped, the CombatCharacter class becomes the owner of the Weapon class and loads information necessary for combat.
- The video below is the character's combat motion applied after equipping the weapon.


![arpg1_min](https://user-images.githubusercontent.com/96270683/229287431-f8f93287-0787-4d95-9975-3cbcb6a4b0e3.gif)


![arpg2_min](https://user-images.githubusercontent.com/96270683/229287735-5707c1a1-cecc-4d7f-ab5d-b1fe8dfdfa3d.gif)




## Components
- Detailed functions of characters or weapons are implemented by individual components.
- CombatCharacter has TargetingComponent, CombatComponent, StatsCompnent, and StateManageComponent.
- BaseWeapon has CollisionComponent.

![arpg7](https://user-images.githubusercontent.com/96270683/229289945-b18177f6-bca6-4330-abac-d1adbe02e8a7.PNG)
![arpg8](https://user-images.githubusercontent.com/96270683/229289955-ef543a0c-e869-4256-a936-82ac905c7f6e.PNG)



### TargetingComponent
- Pressing 'TARGET' command and determine if an enemy is within the specified TargetingDistance.


![arpg9](https://user-images.githubusercontent.com/96270683/229327024-e8d47812-08f8-457a-b8f0-9ed42eb54961.PNG)
- If there is an enemy, it becomes LockOn and the LockOn UI is displayed on the enemy.
- While LockOn, the player and camera will continue to look at the locked enemy.


![arpg3_min](https://user-images.githubusercontent.com/96270683/229327013-a5b54d28-1c8e-411e-81ae-71a08eac819d.gif)
### CombatComponent
- CombatComponent is a component that references the equipped Weapon object, and is also responsible for functions that must be executed when the weapon is equipped or unequipped.


### StateManageComponent
- It has information about what state the character is in and what action it is performing.
- State and Action utilize GameplayTag provided by Unreal Engine.
- When other components perform dedicated functions, these State and Action values ​​are referred to.

![arpg10](https://user-images.githubusercontent.com/96270683/229327248-65516091-8150-4491-bb70-18d280fe6877.PNG)
### StatsComponent
- StatComponent manages the character's stats(HP and Stamina).
- Stat information is ​​updated on the UI at the top left of the screen.


![arpg11](https://user-images.githubusercontent.com/96270683/229327315-0a86f2db-6346-46fd-bd4a-e2af03b41b56.PNG)
### CollisionComponent
- CollisionComponent detects collisions and handles hits.


![arpg4_min](https://user-images.githubusercontent.com/96270683/229327623-ba78ca5d-3431-46ae-a530-d1e0644c7fb8.gif)
- When attacking, the weapon's Collision is activated to collect information on the actors detected by the collision to process damage. It is implemented by the AnimNofiy function(AN_CollsionTrace) on a montage.

  
![arpg11](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/5c953057-bb16-4e6e-a315-c356b1d652d3)
- When the weapon's collision is activated, it creates a trace object from the weapon's 'Weapon Start' socket to 'Weapon End' so it can detect any hits made to the weapon's blade.

  
![arpg13](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/ba183ffd-af31-49de-898b-c788b18a7332)
``` c++
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
}.
```  
