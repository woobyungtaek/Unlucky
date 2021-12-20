#include "pch.h"

#define UNLUCK_COUNT 4
#define FIRST_WEAPON_COUNT 3

Player::Player()	//  이건 왜 없다고 나오지?뭘까? 
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
	//	wcout << L"[System] [" << pWeaponVec[index]->Name << L"] 을(를) 획득하였습니다." << endl;
	//}
	//wcout << L"[System] 무기 상자 +3" << endl;
}


void Player::DropWeaponBylndex(int index)
{

}

void Player::IncreaseUnluckyStack(int count)
{
	UnLuckStack += count;
	wcout << L"[System] 불운 스택 증가 ( " << UnLuckStack << L" / "<< UNLUCK_COUNT<<L" )" << endl;

	while (UnLuckStack >= UNLUCK_COUNT)
	{
		UnLuckStack -= UNLUCK_COUNT;
		Weapon* weapon = WeaponManager::GetInstance()->GetRandomWeaponWithBless();
		LootWeapon(weapon);

		wcout << L"[System] 불운 스택 4개를 소모하여 ["<< (const wchar_t*)(weapon->Name) <<"]를 획득하였습니다." << endl;
		wcout << L"[System] 남은 불운 스택 ( " << UnLuckStack << L" / "<< UNLUCK_COUNT << L")" << endl;
	}
}

