#pragma once
class Weapon;

class WeaponManager :public Singleton< WeaponManager>
{
public:
	WeaponManager();
	~WeaponManager();

private:
	int mWeaponCount;
	vector<vector<int>> mFixedSetVec;
	vector<Weapon*> mpWeaponData;
	
public:
	int  GetAllWeaponCount();
	vector<int> GetrandomfixSet();
	void LoadWeaponData();

	Weapon* GetWeaponCopyByIndex(int index);
	Weapon* GetRandomWeaponWithBless();
	Weapon* GetRandomWeapon();
	Weapon* GetWeaponByName(CString name);
};

