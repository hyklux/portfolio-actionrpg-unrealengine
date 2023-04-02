# portfolio-actionrpg-unrealengine
언리얼 엔진 Action RPG 포트폴리오


## 소개
언리얼 엔진으로 제작한 3인칭 액션 RPG 포트폴리오입니다.


3인칭 플레이어 캐릭터의 기본 전투 로직을 구현해 보았습니다.


![arpg1](https://user-images.githubusercontent.com/96270683/229277573-60205ff8-0400-4b84-bd82-76ed9fd2e4a8.PNG)


## 구성
:heavy_check_mark: Weapon


:heavy_check_mark: Character


:heavy_check_mark: Components


## Weapon


### BaseWeapon
- 모든 무기 클래스는 BaseWeapon 클래스를 상속하여 구현합니다.


![arpg2](https://user-images.githubusercontent.com/96270683/229282134-d7296db9-df8c-488e-be62-71448fbb9a6c.PNG)
- BaseWeapon은 무기의 공격 유형에 따른 애니메이션 데이터와 전투 시 적용될 공격 데이터가 정의됩니다.
``` c++
public:
	UPROPERTY()
	FName HandSocketName;
	UPROPERTY()
	ECombatType CombatType;
	UPROPERTY()
	UCombatComponent* CombatComponent;

	//공격 유형에 따른 애니메이션 몽타주
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

	//전투 관련 데이터
	UPROPERTY()
	float Damage;
	UPROPERTY()
	TMap<FGameplayTag, float> ActionStatCost;
	UPROPERTY()
	TMap<FGameplayTag, float> ActionDamageMultiplier;
```


### BP_ToughSword
- 실제 무기 클래스인 BP_ToughSword의 모습입니다.


![arpg3](https://user-images.githubusercontent.com/96270683/229283520-82812ffa-82f7-475b-a2fc-6da94f31b70d.PNG)
- LightAttack, HeavyAttack 등 공격 유형에 따른 애니메이션을 지정합니다.


![arpg4](https://user-images.githubusercontent.com/96270683/229283564-6cfd2535-ee5a-4e45-801f-43823f85aae4.PNG)
- Damage, ActionStatCost 등의 공격 데이터를 설정합니다.


![arpg5](https://user-images.githubusercontent.com/96270683/229283590-fae7b03a-241f-4813-9f4e-0b8dacaf30d5.PNG)

## Character
- CombatCharacter 클래스에서 플레이어블 캐릭터를 정의합니다.


![arpg6](https://user-images.githubusercontent.com/96270683/229285673-18cd72fc-40f0-4fd0-bb80-af2790987e77.PNG)
- 무기 액터는 SkeletonMesh의 지정 소켓에 장착됩니다.
- 무기 장착 시 CombatCharacter 클래스는 Weapon 클래스의 owner가 되어 전투에 필요한 정보를 불러오게 됩니다.
- 아래 영상은 무기 장착 후 적용된 캐릭터 전투 모션입니다.


![arpg1_min](https://user-images.githubusercontent.com/96270683/229287431-f8f93287-0787-4d95-9975-3cbcb6a4b0e3.gif)


![arpg2_min](https://user-images.githubusercontent.com/96270683/229287735-5707c1a1-cecc-4d7f-ab5d-b1fe8dfdfa3d.gif)




## Components
- 캐릭터나 무기의 세부 기능은 개별 Component에 의해서 구현됩니다.
- CombatCharacter는 TargetingComponent, CombatComponent, StatsCompnent, StateManageComponent를 가지고 있습니다.
- BaseWeapon은 CollisionComponent를 가지고 있습니다.


![arpg7](https://user-images.githubusercontent.com/96270683/229289945-b18177f6-bca6-4330-abac-d1adbe02e8a7.PNG)
![arpg8](https://user-images.githubusercontent.com/96270683/229289955-ef543a0c-e869-4256-a936-82ac905c7f6e.PNG)



### TargetingComponent
- 타겟팅 명령을 입력하며 지정한 TargetingDistance 안에 적이 있는지 판별합니다.


![arpg9](https://user-images.githubusercontent.com/96270683/229327024-e8d47812-08f8-457a-b8f0-9ed42eb54961.PNG)
- 적이 있으면 LockOn이 되고 적에게 LockOn UI가 표시됩니다.
- LockOn 중일 때는 플레이어와 카메라는 LockOn된 적을 계속 바라보도록 처리합니다.


![arpg3_min](https://user-images.githubusercontent.com/96270683/229327013-a5b54d28-1c8e-411e-81ae-71a08eac819d.gif)
### CombatComponent
- 장착한 Weapon 객체를 참조하는 컴포넌트로, 무기를 장착 및 탈착 시에 실행되어야 하는 기능도 담당합니다. 


### StateManageComponent
- 캐릭터가 어떤 상태(State)인지, 어떤 액션(Action)을 하고 있는지에 대한 정보를 갖고 있습니다.
- State와 Action은 언리얼 엔진에서 제공하는 GameplayTag를 활용합니다. 
- 다른 컴포넌트에서 전담 기능을 수행할 때 이 State와 Action값을 참조하게 됩니다.


![arpg10](https://user-images.githubusercontent.com/96270683/229327248-65516091-8150-4491-bb70-18d280fe6877.PNG)
### StatsComponent
- 캐릭터의 스탯(HP, 스태미나) 정보를 관리합니다.
- 스탵 정보는 화면 왼쪽 상단 UI에 그 값이 계속적으로 업데이트되도록 합니다.


![arpg11](https://user-images.githubusercontent.com/96270683/229327315-0a86f2db-6346-46fd-bd4a-e2af03b41b56.PNG)
### CollisionComponent
- 충돌을 감지하여 피격 및 타격에 대한 처리를 담당하는 컴포넌트입니다.
- 공격 시 무기의 Collision을 가동하여 충돌에 의해 감지된 액터들에 대한 정보를 수집해 Damage 처리를 수행합니다.


![arpg4_min](https://user-images.githubusercontent.com/96270683/229327623-ba78ca5d-3431-46ae-a530-d1e0644c7fb8.gif)
