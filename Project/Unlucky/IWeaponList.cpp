#include "pch.h"
class Player;

int IWeaponList::GetScrollNum()
{
	return mScrollNum;
}

Player* IWeaponList::GetPlayer()
{
	return mpPlayer;
}

void IWeaponList::SelectWeaponByButton(int slotIndex)
{
}

Weapon* IWeaponList::GetWeaponByButton(int slotIndex)
{
	return nullptr;
}


bool IWeaponList::ChangeScrollNum(int value)
{
	if (value < 0)
	{
		if (mScrollNum <= 0) { return false; }
	}
	else if (value > 0)
	{
		int weaponCount = mpPlayer->pWeaponVec.size();
		if (weaponCount <= 6) { return false; }
		if (mScrollNum > weaponCount - 6 - 1) { return false; }
	}

	mScrollNum += value;
	wcout << L"현재 표시 범위 : " << mScrollNum << L" ~ " << mScrollNum + 5 << endl;
	return true;
}