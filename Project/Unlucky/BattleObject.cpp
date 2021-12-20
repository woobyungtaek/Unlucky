#include "pch.h"
#include "BattleObject.h"

void BattleObject::DestroyWeaponByIndex(int index)
{
	// 현재 착용 무기를 목록에서 제거
	vector<Weapon*>::iterator iter = pWeaponVec.begin();
	iter += index;
	pWeaponVec.erase(iter);
}

void BattleObject::UseWeaponSkill(BattleObject* target)
{
	wcout << L"---------------스킬 사용-------------" << endl;
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
	wcout << L" 체력이 [" << HP << " / "<< MaxHP<< L"] 가 되었다." << endl;
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
