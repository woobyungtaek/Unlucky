#pragma once
class IWeaponList
{
protected:
	Player* mpPlayer;
	int mScrollNum;

public:
	int	 GetScrollNum();
	bool ChangeScrollNum(int value);
	Player* GetPlayer();

	virtual void SelectWeaponByButton(int slotIndex);
	virtual Weapon* GetWeaponByButton(int slotIndex);
};

