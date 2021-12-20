#pragma once
class StageManager : public Singleton<StageManager>,public IWeaponList
{
public:
	StageManager();
	~StageManager();

private:
	vector<vector<int>> mEnemyNodeVec;

public:
	HPBar* mPlayerHPBar;
	UnLuckyStackBar* mUnluckyStackBar;

public:
	Player* GetPlayer();

	virtual Weapon* GetWeaponByButton(int slotIndex);

	void LoadEnemyNodeData();
	void Init(Player* player);
	bool OpenWeaponBox();
	int GetNodeNumberByPos(int buttonPos);
	void SetCurrentEnemy(int buttonPos);

};

