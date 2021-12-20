#include "pch.h"
#include "LobbyScene.h"

//POINT LobbyScene::mScreenSize;

LobbyScene::LobbyScene()
{
	for (int index = 0; index < 13; index++)
	{
		mButtonList.push_back(new Button());
	}

	//WeaponListUI ����
	mWeaponListUI = new WeaponListUI(StageManager::GetInstance(), 6);

}

LobbyScene::~LobbyScene()
{
	delete Stage_Select_Bgm;
}

// 00�� : ù��° ���
// 01�� : �ι�° ���
// 02�� : ����° ���
// 03�� : ���⺸�޹ڽ�
// 04�� : ���ʽ�ũ�ѹ�ư
// 05�� : �����ʽ�ũ�ѹ�ư

void LobbyScene::Init(POINT screenSize)
{
	// ��ư ������ �����ڿ��� > ���⼱ ���� �ٲ��ش�.
	mScreenSize = screenSize;
	StageManager::GetInstance()->mPlayerHPBar->SetPosition(Vector2(mScreenSize.x * 0.1, mScreenSize.y * 0.87));
	StageManager::GetInstance()->mUnluckyStackBar->SetPosition(Vector2(mScreenSize.x * 0.1, mScreenSize.y * 0.93));
	mWeaponListUI->Init(StageManager::GetInstance()->GetPlayer(), Vector2(mScreenSize.x * 0.7, mScreenSize.y * 0.925), screenSize);
	StageManager::GetInstance()->GetPlayer()->CurrentListUI = mWeaponListUI;

	mButtonList[0]->Init(350, 660, Vector2(mScreenSize.x * 0.17, mScreenSize.y * 0.42));
	mButtonList[0]->MouseClickEvent = &OnClickedLeftButton;
	mButtonList[0]->MouseOnEvent = &OnMouseLeftButton;
	mButtonList[0]->DefaultEvent = &DefaultLeftButton;


	mButtonList[1]->Init(350, 660, Vector2(mScreenSize.x * 0.50, mScreenSize.y * 0.42));
	mButtonList[1]->MouseClickEvent = &OnClickedMiddleButton;
	mButtonList[1]->MouseOnEvent = &OnMouseMiddleButton;
	mButtonList[1]->DefaultEvent = &DefaultMiddleButton;


	mButtonList[2]->Init(350, 660, Vector2(mScreenSize.x * 0.835, mScreenSize.y * 0.42));
	mButtonList[2]->MouseClickEvent = &OnClickedRightButton;
	mButtonList[2]->MouseOnEvent = &OnMouseRightButton;
	mButtonList[2]->DefaultEvent = &DefaultRightButton;


	mButtonList[3]->Init(100, 100, Vector2(mScreenSize.x * 0.37, mScreenSize.y * 0.925));
	mButtonList[3]->SetImgName(_T("..\\Data\\UI\\weapon_supply_button_00.png"));
	mButtonList[3]->MouseClickEvent = &OnClickedWeaponBoxButton;
	mButtonList[3]->MouseOnEvent = &OnMouseWeaponBoxButton;
	mButtonList[3]->DefaultEvent = &DefaultWeaponBoxButton;

	for (unsigned int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->IsActive = true;
	}

	for (int index = 0; index < 3; index++)
	{
		int nodeState = StageManager::GetInstance()->GetNodeNumberByPos(index);
		if (nodeState < 0)
		{
			mButtonList[index]->IsActive = false;
		}
	}
	if (Stage_Select_Bgm == nullptr)
	{
		Stage_Select_Bgm = new SoundManager("..\\Data\\Sounds\\Stage_Select_Bgm.wav", true);
		Stage_Select_Bgm->play();
	}
	else
	{
		Stage_Select_Bgm->resume();
	}
	NextScene = ESceneType::LobbyUpdate;
}
void LobbyScene::Draw()
{
	//����̹��� �׸���
	//����̹��� �׸���
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\SelectScene.png")), D2D1::RectF(0, 0, mScreenSize.x, mScreenSize.y));

	if (StageManager::GetInstance()->GetNodeNumberByPos(0) != -1)
	{
		DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\SelectDoor.png")), D2D1::RectF(0, 0, mScreenSize.x * 0.33, mScreenSize.y));
	}
	if (StageManager::GetInstance()->GetNodeNumberByPos(1) != -1)
	{
		DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\SelectDoor.png")), D2D1::RectF(0 + mScreenSize.x * 0.33, 0, +mScreenSize.x * 0.66, mScreenSize.y));
	}
	if (StageManager::GetInstance()->GetNodeNumberByPos(2) != -1)
	{
		DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\SelectDoor.png")), D2D1::RectF(0 + mScreenSize.x * 0.66, 0, +mScreenSize.x, mScreenSize.y));
	}

	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\the_bottom_bar_0.png")),
		D2D1::RectF(0, mScreenSize.y - 230, mScreenSize.x, mScreenSize.y));

	StageManager::GetInstance()->mPlayerHPBar->Draw();
	StageManager::GetInstance()->mUnluckyStackBar->Draw();

	for (unsigned int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Draw();
	}

	mWeaponListUI->Draw();

}
void LobbyScene::Update()
{
	NextScene = ESceneType::LobbyUpdate;
	Stage_Select_Bgm->Update();
	mWeaponListUI->RefreshUI();
	mWeaponListUI->Update();

	for (unsigned int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Update();
	}
}

void LobbyScene::SelectStage(int index)
{
	int selectNum = StageManager::GetInstance()->GetNodeNumberByPos(index);
	StageManager::GetInstance()->SetCurrentEnemy(selectNum);
	if (selectNum < 0) { return; }
	LobbyScene::GetInstance()->Stage_Select_Bgm->pause();
	NextScene = ESceneType::BattleStart;
}

void LobbyScene::OnClickedLeftButton()
{
	// ���� ��ư ������ ������ = ��Ʋ �� �� �Ǿ� ��
	wcout << L" Left ��ư ����" << endl;	
	SelectStage(0);
}
void LobbyScene::OnMouseLeftButton()
{
	WriteText(mScreenSize.x * 0.15, mScreenSize.y * 0.49, 20, RGB(255, 0, 255), "���ʿ���");
}
void LobbyScene::DefaultLeftButton()
{

}

void LobbyScene::OnClickedMiddleButton()
{
	// ���� ��ư ������ ������ = ��Ʋ �� �� �Ǿ� ��
	wcout << L" Middle ��ư ����" << endl;
	SelectStage(1);
}
void LobbyScene::OnMouseMiddleButton()
{
	WriteText(mScreenSize.x * 0.49, mScreenSize.y * 0.49, 20, RGB(255, 0, 255), "�������");
}
void LobbyScene::DefaultMiddleButton()
{
}

void LobbyScene::OnClickedRightButton()
{
	// ���� ��ư ������ ������ = ��Ʋ �� �� �Ǿ� ��
	wcout << L" Right ��ư ����" << endl;
	SelectStage(2);
}
void LobbyScene::OnMouseRightButton()
{
	WriteText(mScreenSize.x * 0.8, mScreenSize.y * 0.49, 20, RGB(255, 0, 255), "�����ʿ���");
}
void LobbyScene::DefaultRightButton()
{
}

void LobbyScene::OnClickedWeaponBoxButton()
{
	// Ŭ�� �� ���� ���� �Ǿ�� ��
	if (StageManager::GetInstance()->OpenWeaponBox())
	{
		LobbyScene::GetInstance()->Stage_Select_Bgm->pause();
		NextScene = ESceneType::GotcharStart;
	}
}
void LobbyScene::OnMouseWeaponBoxButton()
{
	WriteText(mScreenSize.x * 0.34, mScreenSize.y * 0.93, 20, RGB(255, 0, 255), "���� ����");
}
void LobbyScene::DefaultWeaponBoxButton()
{
}