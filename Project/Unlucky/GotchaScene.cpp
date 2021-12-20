#include "pch.h"
#include "GotchaScene.h"

GotchaScene::GotchaScene()
	: Frame(NULL), ChcekFrm(NULL)
{
	for (int index = 0; index < 36; index++)
	{
		GotchaEffect.push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\TreasureBox_Base.png"), 350, 540));
	}
	for (int index = 0; index < 7; index++)
	{
		NomalEffect.push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\TreasureBox_Normal.png"), 350, 540));
	}
	for (int index = 0; index < 7; index++)
	{
		RareEffect.push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\TreasureBox_Rare.png"), 350, 540));
	}
	for (int index = 0; index < 7; index++)
	{
		EpicEffect.push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\TreasureBox_Epic.png"), 350, 540));
	}
}

GotchaScene::~GotchaScene()
{

}

void GotchaScene::Init(POINT screenSize)
{
	mScreenSize = screenSize;

	//FileName = CurrentWeapon->FileName;
	if (CurrentWeapon != nullptr)
	{
		FileName.Format(L"..\\Data\\Weapon\\%s", CurrentWeapon->FileName);

	WeaponImage =
		SpriteManager::GetInstance()->GetSpriteByPath(FileName);

	Grade = CurrentWeapon->GradeType;
	}
	Frame = 0;
	ChcekFrm = -1;
}

void GotchaScene::Draw()
{
	//ID2D1Bitmap* inst;

	//inst = SpriteManager::GetInstance()->GetSpriteByPath(GotchaEffect[Frame]->FileName);

	/*DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\battle_scene.png")),
		D2D1::RectF(0,
			0,
			mScreenSize.x,
			mScreenSize.y));
	*/
	/*DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(GotchaEffect[Frame]->FileName),
		D2D1::RectF(mScreenSize.x*0.26,
			mScreenSize.y*0.38,
			mScreenSize.x * 0.26+mScreenSize.x*0.5 ,
			mScreenSize.y * 0.38+mScreenSize.y*0.5 ),
		GotchaEffect[Frame]->SrcRect);
		*/
	if (Frame < 36)
	{
		DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(GotchaEffect[Frame]->FileName), 
			D2D1::RectF(mScreenSize.x * 0.35,
				mScreenSize.y * 0.1,
				mScreenSize.x * 0.35 + 700,
				mScreenSize.y * 0.1 + 1080),
			GotchaEffect[Frame]->SrcRect);
	}
	else
	{
		
		int _frame = Frame - 36;
		if (Grade == EWeaponGrade::Normal)
		{
			wcout << L"[System] Normal" << endl;
			DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(NomalEffect[_frame]->FileName),
				D2D1::RectF(mScreenSize.x * 0.375,
					mScreenSize.y * 0.1,
					mScreenSize.x * 0.375 + 700,
					mScreenSize.y * 0.1 + 1080),
				NomalEffect[_frame]->SrcRect);
		}
		if (Grade == EWeaponGrade::Rare)
		{
			wcout << L"[System] Rare" << endl;
			DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(RareEffect[_frame]->FileName),
				D2D1::RectF(mScreenSize.x * 0.375,
					mScreenSize.y * 0.1,
					mScreenSize.x * 0.375 + 700,
					mScreenSize.y * 0.1 + 1080),
				RareEffect[_frame]->SrcRect);
		}
		if (Grade == EWeaponGrade::Epic)
		{
			wcout << L"[System] Epic" << endl;
			DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(EpicEffect[_frame]->FileName),
				D2D1::RectF(mScreenSize.x * 0.375,
					mScreenSize.y * 0.1,
					mScreenSize.x * 0.375 + 700,
					mScreenSize.y * 0.1 + 1080),
				EpicEffect[_frame]->SrcRect);
		}
		if (Frame == 42)
		{
			DrawImageByPivot(WeaponImage, Vector2(mScreenSize.x / 2, mScreenSize.y / 2), WeaponImage->GetSize().width * 0.75, WeaponImage->GetSize().height * 0.6);
		}
		
		//DrawImage(WeaponImage, D2D1::RectF(0, 0, WeaponImage->GetSize().width, WeaponImage->GetSize().height));
	}
	
	
}

void GotchaScene::Update()
{ 
	if (Frame != 42)
	{
		ChcekFrm += 1;
		ChcekFrm %= 5;
		if (ChcekFrm == 0)
		{
			Frame += 1;
			Frame %= 43;
			wcout << L"[System] Frame =" << Frame << endl;
		}
	}	
}
