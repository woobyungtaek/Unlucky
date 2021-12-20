#pragma once
class Player;
class Enemy;
class ResultPopUp;


class BattleManager : public Singleton<BattleManager>,public IWeaponList
{
public:
	BattleManager();
	~BattleManager();

private:
	EBattleState mCurrentState;
	EBattleResult mBattleResult;

	EnemyParty* mpEnemyParty;
	bool mbExit;

	//ÀüÅõ¿ë
	EPlayerAction	playerAction;
	int				playerSelectWeaponIndex;
	Weapon*			playerSelectWeapon;

	Enemy*			currentEnemy;
	int				enemyCount;
	int				enemySelectWeaponIndex;
	Weapon*			enemySelectWeapon;
	EEnemyAction	enemyAction;

public:

	POINT screenSize;

	HPBar* PlayerHPBar;
	HPBar* EnemyHPBar;
	UnLuckyStackBar* UnluckyStackBar;
	ResultPopUp* ResultUI;

	ImageObject* mPlayerImage;
	ImageObject* mEnemyImage;
	ImageObject* mEnemySubImage;
	ImageObject* mEnemyWeaponImage;

	bool (BattleManager::* BattleFunction[(int)EBattleState::StateCount])(void);

public:
	void Init(Player* player);
	bool Update();

	bool Entry();
	bool StartUserTurn();
	bool UserTurn();
	bool StartSelectWeapon();
	bool SelectWeapon();
	bool EnemyTurn();
	bool StartBattle();

	bool UserBattleStart();
	bool UserBattleUpdate();

	bool EnemyBattleStart();
	bool EnemyBattleUpdate();

	bool Battle();
	bool Result();
	bool BattleEnd();

	EBattleResult GetBattleResult();

	virtual void    SelectWeaponByButton(int slotIndex);
	virtual Weapon* GetWeaponByButton(int slotIndex);

	BattleObject* GetEnemy();

	void PlayerTurnEnd();

	bool IsSuccess(float rate);
	void KillEnemyByIndex(int index);

	Weapon* GetPlayerWeaponByIndex(int index);

	void SetExitState(bool value);
};

