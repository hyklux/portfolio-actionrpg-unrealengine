# portfolio-actionrpg-unrealengine
Action RPG portfolio using Unreal Engine


## Introduction
Youtube Link : https://youtu.be/NV9-pcHnVTc


This is an Action RPG portfolio made with Unreal Engine.


I implemented the basic combat gameplay for a third person character.


![action_rpg_intro1](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/57112d9e-b57c-46c2-8777-f4e111e0c3e8)


## Implementations
:heavy_check_mark: **Character**


:heavy_check_mark: **Weapon**


:heavy_check_mark: **Combat**


## Character
- **BP_CombatPlayerCharacter** is the blueprint class for playable character.


![action_rpg_cha1](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/34b37d30-24f1-4e79-a943-e354ddb192ba)
- Character animation logic is implemented on animation blueprint class.

  
![action_rpg_cha2](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/300c4c73-5d6b-43f5-b6ba-22fdd0054820)
- Combat functions of the player character are implemented by individual components. 
- **BP_CombatPlayerCharacter** has five components. These will be explained in more detail below.
	- TargetingComponent
 	- CombatComponent
  	- EquipmentComponent
  	- StatsComponent
  	- StateManageComponent


## Weapon


### BaseWeapon
- All weapon classes are implemented by inheriting the **BaseWeapon** class.


![arpg2](https://user-images.githubusercontent.com/96270683/229282134-d7296db9-df8c-488e-be62-71448fbb9a6c.PNG)
- BaseWeapon defines **animation montages** to be player when using the weapon and** attack values** to be applied when attacking the enemies in combat.
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


![action_rpg_weapon1](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/db37f958-0a48-47df-a4f4-f0206371ef76)
- Animation montages are designated according to attack types such as LightAttack and HeavyAttack and etc.


![action_rpg_weapon2](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/69fa41d4-7e26-4d49-8676-3922beb46b30)
- Attack values(Damage, ActionStatCost, ActionDamageMultiplier) could be set in the weapon blueprint class.


![action_rpg_weapon3](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/0d7c8623-7491-4627-b78e-f528652fe890)
- Weapon actors are mounted on SkeletonMesh's designated sockets.


![action_rpg_weapon4](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/034814fc-675d-47a3-9cb8-2b0cd73846f3)
- When a weapon is equipped, CombatPlayerCharacter class becomes the owner of the weapon class and loads animation montages and attack values necessary for combat.
- CombatPlayerCharacter's CombatComponent keeps the reference to the equipped weapon and changes the combat state.
``` c++
void UCombatComponent::SetMainWeapon(ABaseWeapon* newWeapon)
{
	if (IsValid(MainWeapon))
	{
		MainWeapon->OnUnequipped();
		MainWeapon->Destroy();
	}

	MainWeapon = newWeapon;
}

void UCombatComponent::SetCombatEnabled(bool enableCombat)
{
	bCombatEnabled = enableCombat;
}
```
- The videos show the animation montages applied to the player character after equipping a weapon.


![arpg1_min](https://user-images.githubusercontent.com/96270683/229287431-f8f93287-0787-4d95-9975-3cbcb6a4b0e3.gif)


![arpg2_min](https://user-images.githubusercontent.com/96270683/229287735-5707c1a1-cecc-4d7f-ab5d-b1fe8dfdfa3d.gif)


- CombatPlayerCharacter's StateMangeComponent keeps track of the current character state whenever these animation montages are played so that before executing a certain command we can that it is possible to execute the command or not. 
``` c++
void UStateManageComponent::SetState(FGameplayTag newState)
{
	if (CurrentState != newState)
	{
		CurrentState = newState;
	}
}

FGameplayTag UStateManageComponent::GetCurrentState() const
{
	return CurrentState;
}

bool UStateManageComponent::IsCurrentStateEqualToAny(FGameplayTagContainer& statesToCheck)
{
	return statesToCheck.HasTagExact(CurrentState);
}

void UStateManageComponent::SetAction(FGameplayTag newAction)
{
	if (CurrentAction != newAction)
	{
		CurrentAction = newAction;
	}
}

FGameplayTag UStateManageComponent::GetCurrentAction() const
{
	return CurrentAction;
}

bool UStateManageComponent::IsCurrentActionEqualToAny(FGameplayTagContainer& actionsToCheck)
{
	return actionsToCheck.HasTagExact(CurrentAction);
}
```
## Combat


### 1. Targeting the enemy
- TargetComponent handles enemy targeting.
- When 'TARGET' command is pressed, TargetComponent scans for enemies within the specified TargetingDistance.
``` c++
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
```

![arpg9](https://user-images.githubusercontent.com/96270683/229327024-e8d47812-08f8-457a-b8f0-9ed42eb54961.PNG)
- If there is an enemy, it becomes LockOn and the LockOn UI is displayed on the enemy.
- While LockOn, the player and camera will continue to look at the locked enemy.


![arpg3_min](https://user-images.githubusercontent.com/96270683/229327013-a5b54d28-1c8e-411e-81ae-71a08eac819d.gif)


### 2. Attacking the enemy


- When attacking animation montage is player, the weapon's Collision is activated to collect information on the actors detected by the collision to process damage. It is implemented by the AnimNofiy function(AN_CollsionTrace) on a montage.

  
![action_rpg_attack1](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/e1171090-8f62-4399-8325-66f8f29091f5)
- Once the weapon's collision is activated, it creates a trace object from the weapon's 'Weapon Start' socket to 'Weapon End' so it can detect any hits made to the weapon's blade.
  
  
![arpg13](https://github.com/hyklux/portfolio-actionrpg-unrealengine/assets/96270683/ba183ffd-af31-49de-898b-c788b18a7332)
- CollisionComponent::CollisionTrace() scans for enemies to be damaged except the player character itself.


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
}
```
![arpg4_min](https://user-images.githubusercontent.com/96270683/229327623-ba78ca5d-3431-46ae-a530-d1e0644c7fb8.gif)

## Components
- Detailed functions of characters or weapons are implemented by individual components.
- CombatCharacter has TargetingComponent, CombatComponent, StatsCompnent, and StateManageComponent.
- BaseWeapon has CollisionComponent.

![arpg7](https://user-images.githubusercontent.com/96270683/229289945-b18177f6-bca6-4330-abac-d1adbe02e8a7.PNG)
![arpg8](https://user-images.githubusercontent.com/96270683/229289955-ef543a0c-e869-4256-a936-82ac905c7f6e.PNG)



### TargetingComponent
- Pressing 'TARGET' command and determine if an enemy is within the specified TargetingDistance.
- 

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
