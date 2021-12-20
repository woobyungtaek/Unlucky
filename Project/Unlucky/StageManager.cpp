#include "pch.h"
#include "Player.h"

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/reader.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/encodedstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"

#include "BTJsonManager.h"

#include "StageManager.h"

using namespace rapidjson;

StageManager::StageManager()
{
	if (mPlayerHPBar == nullptr)
	{
		mPlayerHPBar = new HPBar(Vector2(300, 300));
		mUnluckyStackBar = new UnLuckyStackBar(Vector2(300, 300));
	}
	mPlayerHPBar->IsActive = true;
	mUnluckyStackBar->IsActive = true;
}

StageManager::~StageManager()
{
}

Player* StageManager::GetPlayer()
{
	return mpPlayer;
}

void StageManager::LoadEnemyNodeData()
{
	mEnemyNodeVec.clear();

	GenericDocument<JSON_UTF16> doc;
	BTJsonManager::GetInstance()->LoadDataByFileName("..\\Data\\Json\\EnemyNodeData.Json", doc);

	GenericValue<JSON_UTF16>& enemyNodeArr = doc[L"EnemyNode"].GetArray();

	for (int index = 0; index < enemyNodeArr.Size(); index++)
	{
		vector<int> instVec;
		GenericValue<JSON_UTF16>& enemyArr = enemyNodeArr[index].GetArray();
		for (int enemyIdx = 0; enemyIdx < enemyArr.Size(); enemyIdx++)
		{
			instVec.push_back(enemyArr[enemyIdx].GetInt());
		}
		mEnemyNodeVec.push_back(instVec);
	}
}

void StageManager::Init(Player* player)
{
	mpPlayer = player;
	mPlayerHPBar->SetBattleObject(mpPlayer);
	mUnluckyStackBar->SetBattleObject(mpPlayer);

	int stage = mpPlayer->CurrentStage;
	mScrollNum = 0;

	//위치에 따른 선택지 다르게 할 때 사용
	int pos = mpPlayer->StagePos;

	for (int index = 0; index < 3; index++)
	{
		//wcout << mEnemyNodeVec[stage][index] << L" ";
	}
}

bool StageManager::OpenWeaponBox()
{
	GotchaScene::GetInstance()->CurrentWeapon = nullptr;

	if (mpPlayer->WeaponBoxCount <= 0)
	{
		wcout << L"[System] 무기 상자가 없습니다." << endl;
		return false;
	}

	mpPlayer->WeaponBoxCount -= 1;
	Weapon* weapon = WeaponManager::GetInstance()->GetRandomWeapon();
	GotchaScene::GetInstance()->CurrentWeapon = weapon;

	wcout << L"[System] 무기 상자에서 무기를 뽑습니다." << endl;
	weapon->PrintWeaponInfo();

	mpPlayer->LootWeapon(weapon);
	return true;
}

int StageManager::GetNodeNumberByPos(int buttonPos)
{
	int stage = mpPlayer->CurrentStage;

	//위치에 따른 선택지 다르게 할 때 사용
	int pos = mpPlayer->StagePos;

	return mEnemyNodeVec[stage][buttonPos];
}
void StageManager::SetCurrentEnemy(int buttonPos)
{
	mpPlayer->CurrentEnemy = buttonPos;
}


// 현재 플레이어의 무기를 받아온다.
Weapon* StageManager::GetWeaponByButton(int slotIndex)
{
	if (slotIndex + mScrollNum >= mpPlayer->pWeaponVec.size()) { return nullptr; }

	return mpPlayer->pWeaponVec[slotIndex + mScrollNum];
}
