#include "pch.h"

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/reader.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/encodedstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"
#include "BTJsonManager.h"

#include "Weapon.h"
#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
}

WeaponManager::~WeaponManager()
{
}

int WeaponManager::GetAllWeaponCount()
{
	return mWeaponCount;
}
vector<int> WeaponManager::GetrandomfixSet()
{
	int rndIdx = rand() %  mFixedSetVec.size();
	return mFixedSetVec[rndIdx];
}

void WeaponManager::LoadWeaponData()
{
	rapidjson::GenericDocument < rapidjson::UTF16<>> doc;
	BTJsonManager::GetInstance()->LoadDataByFileName("..\\Data\\Json\\WeaponData.Json", doc);


	//초기 무기 셋 설정
	mFixedSetVec.clear();
	rapidjson::GenericValue<JSON_UTF16>::ConstValueIterator iter;
	rapidjson::GenericValue<JSON_UTF16>::ConstValueIterator iter2;
	rapidjson::GenericValue<JSON_UTF16>& fixWeaponArr = doc[_T("FixedWeaponSet")].GetArray();

	for (int index = 0; index < fixWeaponArr.Size(); index++)
	{
		vector<int> instVec;
		for (int weaponIdx = 0; weaponIdx < fixWeaponArr[index].Size(); weaponIdx++)
		{
			instVec.push_back(fixWeaponArr[index][weaponIdx].GetInt());
		}
		mFixedSetVec.push_back(instVec);
	}

	mWeaponCount = doc[_T("WeaponCount")].GetInt();
	for (int index = 0; index < mWeaponCount; index++)
	{
		wchar_t weaponStr[MAX_PATH];
		swprintf_s(weaponStr, _T("Weapon_%d"), index);

		Weapon* inst = new Weapon();

		inst->Name			= doc[weaponStr][_T("Name")].GetString();
		inst->AttackPow		= doc[weaponStr][_T("Power")].GetInt();
		inst->BrokenRate	= doc[weaponStr][_T("BrokenRate")].GetFloat();
		inst->GradeType		= (EWeaponGrade)doc[weaponStr][_T("Grade")].GetInt();
		inst->WeaponType	= (EWeaponType)doc[weaponStr][_T("Type")].GetInt();
		inst->SkillNum		= doc[weaponStr][_T("Skill" )].GetInt();
		inst->Desc			= doc[weaponStr][_T("Desc" )].GetString();

		if (doc[weaponStr].HasMember(_T("SkillDesc")))
		{
			inst->SkillDesc = doc[weaponStr][_T("SkillDesc")].GetString();
		}

		if (doc[weaponStr].HasMember(_T("FileName")))
		{
			inst->FileName = doc[weaponStr][_T("FileName")].GetString();
		}

		SkillBook::SetSkillAtWeapon(inst);

		mpWeaponData.push_back(inst);
	}
}

Weapon* WeaponManager::GetWeaponCopyByIndex(int index)
{
	if (index < 0 || index >= mWeaponCount) { return nullptr; }
	return mpWeaponData[index]->Copy();
}

Weapon* WeaponManager::GetRandomWeaponWithBless()
{
	Weapon* weapon = GetRandomWeapon();
	weapon->BlessCount = rand() % 3;
	return weapon;
}
Weapon* WeaponManager::GetRandomWeapon()
{
	int rndNum = rand() % mWeaponCount;
	Weapon* weapon = mpWeaponData[rndNum]->Copy();
	return weapon;
}

Weapon* WeaponManager::GetWeaponByName(CString name)
{
	for (int index = 0; index < mpWeaponData.size(); index++)
	{
		if (mpWeaponData[index]->Name == name)
		{			
			return mpWeaponData[index]->Copy();
		}
	}
	return nullptr;
}