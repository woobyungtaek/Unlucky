#pragma once
using namespace std;

class BattleObject
{
public:
	// 체력
	int HP;
	int MaxHP;

	// 상대턴 초기화
	bool IsCounter;
	bool IsBlock;

	// 자신의 턴 초기화
	bool IsDrain;
	float AdditionalPowerRate;
	float AdditionalBrokenRate;
	float IncreaseHPValue;

	// 무기 인벤토리
	vector<Weapon*> pWeaponVec;
	
	// 현재 선택 무기
	int SelectWeaponIndex;
	
	// 다음 턴 스킬
	void (*NextSkillFunction)(BattleObject* pCaster, BattleObject* pTarget);

	void DestroyWeaponByIndex(int index);
	void UseWeaponSkill(BattleObject* target);

	void LootWeapon(Weapon* weapon);

	void RecoveryHP(int value);

	void ResetDefenceValues();
	void ResetAttackValues();
};
