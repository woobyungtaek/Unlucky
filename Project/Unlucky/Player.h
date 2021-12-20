#pragma once
class Weapon;
class WeaponListUI;

class Player : public BattleObject
{
public:
	Player();
	~Player();

private:

public:
	int CurrentStage;
	int StagePos;

	int CurrentEnemy;

	int UnLuckStack;
	int WeaponBoxCount;

	// UI 관련들 필요
	EPlayerAction CurrentAction;

	WeaponListUI* CurrentListUI;

public:
	void ResetPlayer();
	void DropWeaponBylndex(int index);

	void IncreaseUnluckyStack(int count);
};

