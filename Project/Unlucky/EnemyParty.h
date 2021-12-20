#pragma once
class EnemyParty
{
public:
	EnemyParty();
	~EnemyParty();


private:
	vector<Enemy*> mpParty;
	
public:
	void AddEnemyByEnemyData(Enemy* enemy);

	int	   GetEnemyCount();
	Enemy* GetEnemyByIndex(int index);

	void	EraseEnemyInPartyByIndex(int index);
};

