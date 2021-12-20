#include "pch.h"
class BattleManger;

ResultPopUp::ResultPopUp(Vector2 pos)
{
	for (int index = 0; index < 2; index++)
	{
		mButtonList.push_back(new Button());
	}
}

ResultPopUp::~ResultPopUp()
{

}
void ResultPopUp::SetWeapon(Weapon* weapon)
{
	if (weapon == nullptr)
	{
		return;
	}
	mWeaponVec.push_back(weapon);
}

void ResultPopUp::ReseWeaponVec()
{
	mWeaponVec.clear();
}


void ResultPopUp::Init(POINT screenSize)
{
	mScreenSize = screenSize;
	SetPosition(Vector2(mScreenSize.x / 2, mScreenSize.y / 2));

	// BattleManager::GetInstance()->ResultUI
	// 무기보급권 버튼
	mButtonList[0]->Init(545, 130, Vector2(GetPosition().x, GetPosition().y + 315));
	mButtonList[0]->SetImgName(_T("..\\Data\\UI\\weapon_ticket_0.png"));
	mButtonList[0]->MouseClickEvent = &OnClickedWeaponButton;
	mButtonList[0]->MouseOnEvent = &OnMouseWeaponButton;
	mButtonList[0]->DefaultEvent = &DefaultWeaponButton;

	// 창종료 버튼
	mButtonList[1]->Init(55, 55, Vector2(GetPosition().x + 800, GetPosition().y - 350));
	mButtonList[1]->SetImgName(_T("..\\Data\\UI\\game_close_0.png"));
	mButtonList[1]->MouseClickEvent = &OnClickedCloseButton;
	mButtonList[1]->MouseOnEvent = &OnMouseCloseButton;
	mButtonList[1]->DefaultEvent = &DefaultButton;


	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->IsActive = true;
	}
}

void ResultPopUp::Start()
{
}

void ResultPopUp::Draw()
{
	int ResultBoxMax = 5;
	int num = -2;

	if (!IsActive) { return; }

	ID2D1Bitmap* pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\result_0.png"));
	int a = GetPosition().x;
	int b = GetPosition().y;
	DrawImageByPivot(pBitmap, Vector2(GetPosition().x, GetPosition().y), pBitmap->GetSize().width, pBitmap->GetSize().height);

	vector<Vector2> slotPosVec;

	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_image_1.png"));
	for (int index = 0; index < ResultBoxMax; index++)
	{
		Vector2 pos = Vector2(GetPosition().x - (325 * num), GetPosition().y - 35);
		slotPosVec.push_back(pos);

		DrawImageByPivot(pBitmap, pos, pBitmap->GetSize().width, pBitmap->GetSize().height);
		num++;
	}

	for (int index = 0; index < mWeaponVec.size(); index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Weapon\\%s"), mWeaponVec[index]->FileName);
		ID2D1Bitmap* pWeaponBitmap = SpriteManager::GetInstance()->GetSpriteByPath(str);
		DrawImageByPivot(pWeaponBitmap, slotPosVec[4 - index], pWeaponBitmap->GetSize().width * 0.25, pWeaponBitmap->GetSize().height * 0.25);

	}

	//  스테이지 클리어 글씨창
	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\stage_clear_0.png"));
	DrawImageByPivot(pBitmap, Vector2(GetPosition().x, GetPosition().y - 340), pBitmap->GetSize().width, pBitmap->GetSize().height);

	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Draw();
	}
}

void ResultPopUp::Update()
{
	if (!IsActive) { return; }

	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Update();

	}

}

void ResultPopUp::OnClickedWeaponButton()
{
	wcout << L"무기보급권 버튼임다" << endl;
	BattleManager::GetInstance()->SetExitState(true);
}

void ResultPopUp::OnMouseWeaponButton()
{
}

void ResultPopUp::DefaultWeaponButton()
{
}

void ResultPopUp::OnClickedCloseButton()
{
	wcout << L"종료 버튼임다" << endl;
	BattleManager::GetInstance()->SetExitState(true);
}

void ResultPopUp::OnMouseCloseButton()
{
}

void ResultPopUp::DefaultButton()
{
}
