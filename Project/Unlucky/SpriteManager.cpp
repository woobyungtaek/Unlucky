#include "pch.h"

#include "../rapidjson/include/rapidjson/document.h"
#include "../rapidjson/include/rapidjson/writer.h"
#include "../rapidjson/include/rapidjson/reader.h"
#include "../rapidjson/include/rapidjson/filereadstream.h"
#include "../rapidjson/include/rapidjson/encodedstream.h"
#include "../rapidjson/include/rapidjson/stringbuffer.h"

#include "BTJsonManager.h"

SpriteManager* SpriteManager::mInstance;

// 이미지 로드
bool SpriteManager::LoadImageFile(CString uri)
{
	//경로를 키값으로 사용하는 맵
	if(mBitmapMap.find(uri) != mBitmapMap.end())
	{
		return false;
	}


	ID2D1Bitmap* instBitmap;
	LoadIamge(uri, &instBitmap);
	if (instBitmap == nullptr)
	{
		return false;
	}

	mBitmapMap.emplace(uri, instBitmap);

	//엔진 함수를 이용해 비트맵을 로드 한다.
	LoadIamge(uri, &mBitmapMap[uri]);
	return true;
}

// 스프라이트 데이터 로드
void SpriteManager::LoadSpriteData(CString uri)
{
	//WChar to string 
	wstring ws(uri);
	string str(ws.begin(), ws.end());

	//JsonOpen
	rapidjson::GenericDocument<rapidjson::UTF16<>> openJsonDoc;
	bool bSuccess = BTJsonManager::GetInstance()->LoadDataByFileName(str, openJsonDoc);
	if (!bSuccess)
	{
		return;
	}

	int frameCount = openJsonDoc[_T("FrameCount")].GetInt();
	for (int index = 0; index < frameCount; index++)
	{
		Sprite inst;

		inst.FrameCount = frameCount;

		wchar_t str[MAX_PATH];
		swprintf_s(str, _T("SpriteInfo_%d"), index);

		inst.FileName = openJsonDoc[str][_T("FileName")].GetString();

		inst.Motion = openJsonDoc[str][_T("Motion")].GetString();

		inst.Frame = openJsonDoc[str][_T("Frame")].GetInt();

		inst.SrcRect.left = openJsonDoc[str][_T("SrcRect")][_T("left")].GetInt();
		inst.SrcRect.top = openJsonDoc[str][_T("SrcRect")][_T("top")].GetInt();
		inst.SrcRect.right = openJsonDoc[str][_T("SrcRect") ][_T("right")].GetInt();
		inst.SrcRect.bottom = openJsonDoc[str][_T("SrcRect")][_T("bottom")].GetInt();

		inst.Pivot.x = openJsonDoc[str][_T("Pivot")][_T("x")].GetInt();
		inst.Pivot.y = openJsonDoc[str][_T("Pivot")][_T("y")].GetInt();

		inst.Delay = openJsonDoc[str][_T("Delay")].GetInt();

		int collCount = openJsonDoc[str][_T("ColliderCount")].GetInt();
		for (int colIdx = 0; colIdx < collCount; colIdx++)
		{
			wchar_t colliderName[MAX_PATH];
			swprintf_s(colliderName, _T("Collider_%d"), colIdx);
			D2D1_RECT_F rect;
			rect.left = openJsonDoc[str][_T("Colliders")][colliderName][_T("left")].GetInt();
			rect.top = openJsonDoc[str][_T("Colliders")][colliderName][_T("top")].GetInt();
			rect.right = openJsonDoc[str][_T("Colliders")][colliderName][_T("right")].GetInt();
			rect.bottom = openJsonDoc[str][_T("Colliders")][colliderName][_T("bottom")].GetInt();
			//inst.ColliderVec.push_back(rect);
		}
		
		mSpriteDataMap[inst.FileName][inst.Motion].push_back(inst);
	}
}

Sprite* SpriteManager::GetAniData(int frm, CString uri, int width, int height)
{
	Sprite* instInfo = new Sprite();

	instInfo->FileName = uri;
	instInfo->width = width;
	instInfo->height = height;

	D2D1_RECT_F srcRect;
	srcRect.left = frm * width;
	srcRect.top =   0;
	srcRect.right = (frm + 1) * width;
	srcRect.bottom =   height;

	instInfo->SrcRect = srcRect;

	return instInfo;
}

void SpriteManager::LoadImagefromData()
{
	// 캐릭터 불러오기
	LoadImageFile(_T("..\\Data\\Mimic_Final.png"));
	LoadImageFile(_T("..\\Data\\Monster\\Boss_0.png"));
	//LoadImageFile(_T("..\\Data\\Monster\\Boss_test_0.png"));
	LoadImageFile(_T("..\\Data\\Monster\\hero_man_test_0.png"));
	LoadImageFile(_T("..\\Data\\Monster\\hero_man_test_1.png"));
	LoadImageFile(_T("..\\Data\\Monster\\hero_woman_cape_0.png"));
	LoadImageFile(_T("..\\Data\\Monster\\hero_woman_cape_x_0.png"));
	LoadImageFile(_T("..\\Data\\Monster\\hero_woman_test_1.png"));
	LoadImageFile(_T("..\\Data\\Monster\\nomal_man_test_0.png"));
	LoadImageFile(_T("..\\Data\\Monster\\nomal_woman_test_0.png"));

	// 배경 씬 불러오기
	LoadImageFile(_T("..\\Data\\SelectScene.png")); 
	LoadImageFile(_T("..\\Data\\SelectDoor.png"));
	LoadImageFile(_T("..\\Data\\battle_scene.png"));
	LoadImageFile(_T("..\\Data\\TreasureBox_T2.png"));

	// UI 이미지 불러오기
	LoadImageFile(_T("..\\Data\\UI\\result_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_image_1.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_ticket_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\stage_clear_0.png"));

	LoadImageFile(_T("..\\Data\\UI\\trun_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\hp_gauge_bar_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\badluck_gauge_01.png"));
	LoadImageFile(_T("..\\Data\\UI\\the_bottom_bar_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_image_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\arrow_01.png"));
	LoadImageFile(_T("..\\Data\\UI\\arrow_02.png"));
	LoadImageFile(_T("..\\Data\\UI\\game_finish_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_supply_button_00.png"));

	// 무기 정보 패널
	LoadImageFile(_T("..\\Data\\UI\\weapon_information_window_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_name_box_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_information.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_destory_damage_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\weapon_skill_infomation_0.png"));
	LoadImageFile(_T("..\\Data\\UI\\game_close_0.png"));

	
	// 타이를 씬 불러오기
	LoadImageFile(_T("..\\Data\\title_background.png"));
	LoadImageFile(_T("..\\Data\\title_ani.png"));
	LoadImageFile(_T("..\\Data\\title.png"));
	LoadImageFile(_T("..\\Data\\title_start.png"));
	LoadImageFile(_T("..\\Data\\title_exit.png"));

	//가챠 씬 불러오기
	LoadImageFile(_T("..\\Data\\TreasureBox_Base.png"));
	LoadImageFile(_T("..\\Data\\TreasureBox_Normal.png"));
	LoadImageFile(_T("..\\Data\\TreasureBox_Rare.png"));
	LoadImageFile(_T("..\\Data\\TreasureBox_Epic.png"));

	//이펙트 불러오기
	LoadImageFile(_T("..\\Data\\Effect\\Effect_WeaponBreak.png"));
	LoadImageFile(_T("..\\Data\\Effect\\Effect_Sword.png"));
	LoadImageFile(_T("..\\Data\\Effect\\Effect_Spear.png"));
	LoadImageFile(_T("..\\Data\\Effect\\Effect_Hammer.png"));	
	LoadImageFile(_T("..\\Data\\Effect\\Effect_Boss_Skill.png"));
	LoadImageFile(_T("..\\Data\\Effect\\Effect_UnluckySupplyWeapon.png"));

	// Dagger 6개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\Dagger_%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}
	// Hammer 6개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\Hammer_%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}

	// Shield 3개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\Shield_%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}

	// Spear 8개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\Spear_%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}

	// Sword 12개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\Sword_%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}

	// opening 19개 불러오기
	for (int index = 0; index < 100; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Opening\\%d.png"), index);
		if (!LoadImageFile(str)) { break; }
	}

}

//비트맵 (sprite sheet) 
ID2D1Bitmap* SpriteManager::GetSpriteByPath(CString path)
{
	return mBitmapMap[path];
}