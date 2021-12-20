#include "pch.h"
#include "BattleObject.h"

void BattleObject::DestroyWeaponByIndex(int index)
{
	// ���� ���� ���⸦ ��Ͽ��� ����
	vector<Weapon*>::iterator iter = pWeaponVec.begin();
	iter += index;
	pWeaponVec.erase(iter);
}

void BattleObject::UseWeaponSkill(BattleObject* target)
{
	wcout << L"---------------��ų ���-------------" << endl;
	Weapon* selectWeapon = pWeaponVec[SelectWeaponIndex];
	if (selectWeapon->SkillFunc != nullptr)
	{
		selectWeapon->SkillFunc(this, target);
	}
	wcout << L"-------------------------------------" << endl;
}

void BattleObject::LootWeapon(Weapon* weapon)
{
	pWeaponVec.push_back(weapon);
}

void BattleObject::RecoveryHP(int value)
{
	HP += value;
	if (HP > MaxHP)
	{
		HP = MaxHP;
	}
	wcout << L" ü���� [" << HP << " / "<< MaxHP<< L"] �� �Ǿ���." << endl;
}

void BattleObject::ResetDefenceValues()
{
	IsCounter = false;
	IsBlock = false;
}

void BattleObject::ResetAttackValues()
{
	IsDrain = false;
	AdditionalPowerRate = 0;
	AdditionalBrokenRate = 0;
	IncreaseHPValue = 0;
}
