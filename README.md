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
- 아래 영상은 무기 장착 후 적용된 캐릭터 전투 모셥입니다.
![MeleeCombatSystem_-_언리얼_에디터_2023-04-01_20-20-14_AdobeExpress](https://user-images.githubusercontent.com/96270683/229285904-d9e3f224-b489-4c1a-a6f8-5722bf37152c.gif)

## Components


### TargetingComponent


### CombatComponent


### StatsComponent


### StateManageComponent
