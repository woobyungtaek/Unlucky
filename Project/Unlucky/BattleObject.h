#pragma once
using namespace std;

class BattleObject
{
public:
	// ü��
	int HP;
	int MaxHP;

	// ����� �ʱ�ȭ
	bool IsCounter;
	bool IsBlock;

	// �ڽ��� �� �ʱ�ȭ
	bool IsDrain;
	float AdditionalPowerRate;
	float AdditionalBrokenRate;
	float IncreaseHPValue;

	// ���� �κ��丮
	vector<Weapon*> pWeaponVec;
	
	// ���� ���� ����
	int SelectWeaponIndex;
	
	// ���� �� ��ų
	void (*NextSkillFunction)(BattleObject* pCaster, BattleObject* pTarget);

	void DestroyWeaponByIndex(int index);
	void UseWeaponSkill(BattleObject* target);

	void LootWeapon(Weapon* weapon);

	void RecoveryHP(int value);

	void ResetDefenceValues();
	void ResetAttackValues();
};
