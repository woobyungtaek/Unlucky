#include "pch.h"
#include "BattleManager.h"

WeaponListUI* WeaponListUI::mInst;
Weapon* WeaponListUI::mCurrentWeapon;

WeaponListUI::WeaponListUI(IWeaponList* manager, int viewCount) : mViewCount(viewCount)
{
	mCurrentManager = manager;
	for (int index = 0; index < mViewCount; index++)
	{
		mWeaponButtonVec.push_back(new WeaponButton());
		mWeaponButtonVec[index]->IsActive = true;
	}
	for (int index = 0; index < 2; index++)
	{
		mButtonVec.push_back(new Button());
		mButtonVec[index]->IsActive = true;
	}

	if (mInfoPanel == nullptr)
	{
		mInfoPanel = new WeaponInfoUI();
	}
	D2D1_POINT_2F mScreenSize = D2D1::Point2F(2560, 1440);
	mScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
	mScreenSize.y = GetSystemMetrics(SM_CYSCREEN);
	mInfoPanel->SetPosition(Vector2(mScreenSize.x * 0.75, mScreenSize.y * 0.65));
}

WeaponListUI::~WeaponListUI()
{

}

void WeaponListUI::Init(Player* player,Vector2 pos ,POINT size)
{
	mInst = this;
	mpPlayer = player;

	SetPosition(pos);	

	for (int index = 0; index < mViewCount; index++)
	{
		mWeaponButtonVec[index]->Init(
			100, 100,
			Vector2(pos.x + (150 * (index - mViewCount/2)), pos.y));
	}

	mWeaponButtonVec[0]->MouseClickEvent =	&OnClickedWeaponButton_0;
	mWeaponButtonVec[0]->MouseOnEvent =		&OnMouseWeaponButton_0;

	mWeaponButtonVec[1]->MouseClickEvent =	&OnClickedWeaponButton_1;
	mWeaponButtonVec[1]->MouseOnEvent =		&OnMouseWeaponButton_1;

	mWeaponButtonVec[2]->MouseClickEvent =	&OnClickedWeaponButton_2;
	mWeaponButtonVec[2]->MouseOnEvent =		&OnMouseWeaponButton_2;

	mWeaponButtonVec[3]->MouseClickEvent =	&OnClickedWeaponButton_3;
	mWeaponButtonVec[3]->MouseOnEvent =		&OnMouseWeaponButton_3;

	mWeaponButtonVec[4]->MouseClickEvent =	&OnClickedWeaponButton_4;
	mWeaponButtonVec[4]->MouseOnEvent =		&OnMouseWeaponButton_4;

	mWeaponButtonVec[5]->MouseClickEvent =	&OnClickedWeaponButton_5;
	mWeaponButtonVec[5]->MouseOnEvent =		&OnMouseWeaponButton_5;

	 
	//滚瓢 10俺 -> 谅快胶农费, 公扁府胶飘
	mButtonVec[0]->Init(70, 70, Vector2(pos.x - (142 * (mViewCount / 2 + 1)), pos.y));
	mButtonVec[0]->SetImgName(_T("..\\Data\\UI\\arrow_01.png"));
	mButtonVec[0]->MouseClickEvent = &OnClickedLeftScrollButton;
	mButtonVec[0]->MouseOnEvent = &OnMouseLeftScrollButton;
	mButtonVec[0]->DefaultEvent = &DefaultLeftScrollButton;

	mButtonVec[1]->Init(70, 70, Vector2(pos.x + (142 * mViewCount / 2), pos.y));
	mButtonVec[1]->SetImgName(_T("..\\Data\\UI\\arrow_02.png"));
	mButtonVec[1]->MouseClickEvent = &OnClickedRightScrollButton;
	mButtonVec[1]->MouseOnEvent = &OnMouseRightScrollButton;
	mButtonVec[1]->DefaultEvent = &DefaultRightScrollButton;

	mInst->RefreshUI();
}

void WeaponListUI::Start()
{
}

void WeaponListUI::Draw()
{
	for (int index = 0; index < 2; index++)
	{
		mButtonVec[index]->Draw();
	}
	for (int index = 0; index < mViewCount; index++)
	{
		mWeaponButtonVec[index]->Draw();
	}
	mInfoPanel->Draw();
}

void WeaponListUI::Update()
{
	mInst->mInfoPanel->IsActive = false;
	for (int index = 0; index < 2; index++)
	{
		mButtonVec[index]->Update();
	}
	for (int index = 0; index < mViewCount; index++)
	{
		mWeaponButtonVec[index]->Update();
	}
	mInfoPanel->Update();
}

void WeaponListUI::RefreshUI()
{
	int start = -1;
	
	start = mCurrentManager->GetScrollNum();

	if (start < 0) { return; }

	for (int index = 0; index < mViewCount; index++)
	{
		WeaponButton* inst = mWeaponButtonVec[index];
		Weapon* instWeapon = nullptr;
		if (start < mCurrentManager->GetPlayer()->pWeaponVec.size())
		{
			instWeapon = mCurrentManager->GetPlayer()->pWeaponVec[start];
		}
		inst->SetWeapon(instWeapon);

		start++;
	}
}

void WeaponListUI::OnClickedLeftScrollButton()
{
	wcout << L"哭率 胶农费 充充" << endl;
	if (mInst->mCurrentManager->ChangeScrollNum(-1))
	{
		mInst->RefreshUI();
	}
}
void WeaponListUI::OnMouseLeftScrollButton()
{
	WriteText(760, 900, 20, RGB(255, 0, 255), "哭率胶农费");
}
void WeaponListUI::DefaultLeftScrollButton()
{
}

void WeaponListUI::OnClickedRightScrollButton()
{
	wcout << L"坷弗率 胶农费 橙橙" << endl;
	if (mInst->mCurrentManager->ChangeScrollNum(1))
	{
		mInst->RefreshUI();
	}
}
void WeaponListUI::OnMouseRightScrollButton()
{
	WriteText(1700, 900, 20, RGB(255, 0, 255), "坷弗率胶农费");
}
void WeaponListUI::DefaultRightScrollButton()
{
}

void WeaponListUI::OnClickedWeaponButton_0()
{
	mInst->mCurrentManager->SelectWeaponByButton(0);
}
void WeaponListUI::OnClickedWeaponButton_1()
{
	mInst->mCurrentManager->SelectWeaponByButton(1);
}
void WeaponListUI::OnClickedWeaponButton_2()
{
	mInst->mCurrentManager->SelectWeaponByButton(2);
}
void WeaponListUI::OnClickedWeaponButton_3()
{
	mInst->mCurrentManager->SelectWeaponByButton(3);
}
void WeaponListUI::OnClickedWeaponButton_4()
{
	mInst->mCurrentManager->SelectWeaponByButton(4);
}
void WeaponListUI::OnClickedWeaponButton_5()
{
	mInst->mCurrentManager->SelectWeaponByButton(5);
}
void WeaponListUI::OnClickedWeaponButton_6()
{
	mInst->mCurrentManager->SelectWeaponByButton(6);
}

void WeaponListUI::OnMouseWeaponButton_0()
{	
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(0));
}
void WeaponListUI::OnMouseWeaponButton_1()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(1));
}
void WeaponListUI::OnMouseWeaponButton_2()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(2));
}
void WeaponListUI::OnMouseWeaponButton_3()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(3));
}
void WeaponListUI::OnMouseWeaponButton_4()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(4));
}
void WeaponListUI::OnMouseWeaponButton_5()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(5));
}
void WeaponListUI::OnMouseWeaponButton_6()
{
	mInst->mInfoPanel->SetWeapon(mInst->mCurrentManager->GetWeaponByButton(6));
}
