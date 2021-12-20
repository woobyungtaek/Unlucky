#pragma once
class EnemyManager : public Singleton<EnemyManager>
{
public:
	EnemyManager();
	~EnemyManager();

private:
	int mEnemyCount;
	vector<Enemy*> mEnemyData;

public:
	void LoadEnemyData();
	void LoadPartyData();

	EnemyParty* GetEnemyPartyByIndex(int Index);
};

