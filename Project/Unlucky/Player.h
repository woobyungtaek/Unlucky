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

	// UI ���õ� �ʿ�
	EPlayerAction CurrentAction;

	WeaponListUI* CurrentListUI;

public:
	void ResetPlayer();
	void DropWeaponBylndex(int index);

	void IncreaseUnluckyStack(int count);
};

