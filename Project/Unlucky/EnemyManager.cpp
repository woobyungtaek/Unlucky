#include "pch.h"

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/reader.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/encodedstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"

#include "BTJsonManager.h"

using namespace rapidjson;

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::LoadEnemyData()
{
	WeaponManager* wmInstance = WeaponManager::GetInstance();

	GenericDocument<JSON_UTF16> doc;
	BTJsonManager::GetInstance()->LoadDataByFileName("..\\Data\\Json\\EnemyData.Json", doc);

	mEnemyCount = doc[_T("EnemyCount")].GetInt();
	for (int index = 0; index < mEnemyCount; index++)
	{
		wchar_t enemyStr[MAX_PATH];
		swprintf_s(enemyStr, _T("Enemy_%d"), index);

		Enemy* inst = new Enemy();

		inst->Grade				= (EEnemyGrade)doc[enemyStr][_T("Grade")].GetInt();
		inst->HP				= doc[enemyStr][_T("HP")].GetInt();
		inst->MaxHP				= inst->HP;
		inst->Name				= doc[enemyStr][_T("Name")].GetString();
		inst->FileName			= doc[enemyStr][_T("FileName")].GetString();
		inst->BlessWeaponIndex	= doc[enemyStr][_T("BlessWeapon")].GetInt();

		GenericValue<JSON_UTF16>::ConstValueIterator iter;
		GenericValue<JSON_UTF16>& weaponArr = doc[enemyStr][_T("PossibleWeapon")].GetArray();
		iter = weaponArr.Begin();

		//웨폰 뽑기 가능 리스트
		for (iter = weaponArr.Begin(); iter != weaponArr.End(); ++iter)
		{
			int weaponIndex = iter->GetInt();
			inst->WeaponIndexVec.push_back(weaponIndex);
			inst->pWeaponVec.push_back(wmInstance->GetWeaponCopyByIndex(weaponIndex));
		}

		// 사용 할 스킬 목록
		GenericValue<JSON_UTF16>& skillArr = doc[enemyStr][_T("SkillIndex")].GetArray();
		iter = skillArr.Begin();
		for (iter = skillArr.Begin(); iter != skillArr.End(); ++iter)
		{
			inst->SkillIndexVec.push_back(iter->GetInt());
		} 

		// 페이즈 전환 기준  HP 목록
		GenericValue<JSON_UTF16>& phaseHPArr = doc[enemyStr][_T("HPStandard")].GetArray();
		iter = phaseHPArr.Begin();
		for (iter = phaseHPArr.Begin(); iter != phaseHPArr.End(); ++iter)
		{
			inst->PhaseHPVec.push_back(iter->GetFloat());
		}
		SkillBook::SetPhaseSkillAtEnemy(inst);


		// 패턴 리스트
		GenericValue<JSON_UTF16>& patternArr = doc[enemyStr][_T("Pattern")].GetArray();
		iter = patternArr.Begin();
		for (iter = patternArr.Begin(); iter != patternArr.End(); ++iter)
		{
			vector<int> temp;
			const GenericValue<JSON_UTF16>& patternArr2 = iter->GetArray();

			GenericValue<JSON_UTF16>::ConstValueIterator iter2;
			for (iter2 = patternArr2.Begin(); iter2 != patternArr2.End(); ++iter2)
			{
				temp.push_back(iter2->GetInt());
			}
			inst->PatternVec.push_back(temp);
		}

		mEnemyData.push_back(inst);
	}
}

void EnemyManager::LoadPartyData()
{
}

EnemyParty* EnemyManager::GetEnemyPartyByIndex(int index)
{
	EnemyParty* inst = new EnemyParty();
	inst->AddEnemyByEnemyData(mEnemyData[index]);
	return inst;
}

