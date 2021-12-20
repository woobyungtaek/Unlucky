#include "pch.h"

EnemyParty::EnemyParty()
{
}

EnemyParty::~EnemyParty()
{
}

void EnemyParty::AddEnemyByEnemyData(Enemy* enemy)
{
	mpParty.push_back(enemy->Copy());
}

int EnemyParty::GetEnemyCount()
{
	return mpParty.size();
}

Enemy* EnemyParty::GetEnemyByIndex(int index)
{
	return mpParty[index];
}

void EnemyParty::EraseEnemyInPartyByIndex(int index)
{
	vector<Enemy*>::iterator iter = mpParty.begin();
	iter += index;
	mpParty.erase(iter);
}
