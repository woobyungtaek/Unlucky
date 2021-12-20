#include "pch.h"

#define UNLUCK_COUNT 4
#define FIRST_WEAPON_COUNT 3

Player::Player()	//  �̰� �� ���ٰ� ������?����? 
{

}

Player::~Player()
{
}

void Player::ResetPlayer()
{
	for (unsigned int index = 0; index < BattleObject::pWeaponVec.size(); index++)
	{
		delete pWeaponVec[index];
	}
	pWeaponVec.clear();

	vector<int> rndFixedSet = WeaponManager::GetInstance()->GetrandomfixSet();
	int loopCount = rndFixedSet.size();
	for (int index = 0; index < loopCount; index++)
	{
		LootWeapon(WeaponManager::GetInstance()->GetWeaponCopyByIndex(rndFixedSet[index]));
	}

	HP					= 200;
	MaxHP				= 200;
	CurrentStage		= 0;
	StagePos			= 1;
	UnLuckStack			= 0;
	WeaponBoxCount		= 0;
	SelectWeaponIndex	= 0;
	WeaponBoxCount		= 3;

	//for (int index = 0; index < pWeaponVec.size(); index++)
	//{
	//	wcout << L"[System] [" << pWeaponVec[index]->Name << L"] ��(��) ȹ���Ͽ����ϴ�." << endl;
	//}
	//wcout << L"[System] ���� ���� +3" << endl;
}


void Player::DropWeaponBylndex(int index)
{

}

void Player::IncreaseUnluckyStack(int count)
{
	UnLuckStack += count;
	wcout << L"[System] �ҿ� ���� ���� ( " << UnLuckStack << L" / "<< UNLUCK_COUNT<<L" )" << endl;

	while (UnLuckStack >= UNLUCK_COUNT)
	{
		UnLuckStack -= UNLUCK_COUNT;
		Weapon* weapon = WeaponManager::GetInstance()->GetRandomWeaponWithBless();
		LootWeapon(weapon);

		wcout << L"[System] �ҿ� ���� 4���� �Ҹ��Ͽ� ["<< (const wchar_t*)(weapon->Name) <<"]�� ȹ���Ͽ����ϴ�." << endl;
		wcout << L"[System] ���� �ҿ� ���� ( " << UnLuckStack << L" / "<< UNLUCK_COUNT << L")" << endl;
	}
}

