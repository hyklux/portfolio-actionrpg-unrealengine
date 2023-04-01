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
	FName HandSocketName;
	ECombatType CombatType;
	UCombatComponent* CombatComponent;

	//공격 유형에 따른 애니메이션 몽타주
	TArray<UAnimMontage*> LightAttackMontages;
	TArray<UAnimMontage*> HeavyAttackMontages;
	TArray<UAnimMontage*> ChargeAttackMontages;
	TArray<UAnimMontage*> FallingAttackMontages;
	TArray<UAnimMontage*> SprintAttackMontages;
	TArray<UAnimMontage*> DodgeMontages;
	UAnimMontage* EnterCombatMontage;
	UAnimMontage* ExitCombatMontage;

	//전투 관련 데이터
	float Damage;
	TMap<FGameplayTag, float> ActionStatCost;
	TMap<FGameplayTag, float> ActionDamageMultiplier;
```


### BP_ToughSword
- 실제 무기 클래스인 BP_ToughSword의 모습입니다.
- (BP_ToughSword의) 스샷
- LightAttack, HeavyAttack 등 공격 유형에 따른 애니메이션을 지정합니다.
- (BP_ToughSword의) 애니메이션 스샷
- Damage 공격 데이터를 설정합니다.
- (BP_ToughSword의) 애니메이션 스샷

## Character


## Components


### TargetingComponent


### CombatComponent


### StatsComponent


### StateManageComponent
