#include "pch.h"
#include "BattleManager.h"

BattleScene::BattleScene()
{
	for (int index = 0; index < 3; index++)
	{
		mButtonList.push_back(new Button());
	}

	//WeaponListUI 생성
	mWeaponListUI = new WeaponListUI(BattleManager().GetInstance(), 6);
}

BattleScene::~BattleScene()
{
}
void BattleScene::Init(POINT screenSize)
{
	mScreenSize = screenSize;

	mWeaponListUI->Init(BattleManager::GetInstance()->GetPlayer(), Vector2(mScreenSize.x - 740, mScreenSize.y -90), mScreenSize);
	BattleManager::GetInstance()->GetPlayer()->CurrentListUI = mWeaponListUI;
	BattleManager::GetInstance()->ResultUI->Init(mScreenSize);

	// 턴종료버튼
	mButtonList.push_back(new Button());
	mButtonList[0]->Init(140, 60, Vector2(mScreenSize.x - 140, mScreenSize.y - 90));
	mButtonList[0]->SetImgName(_T("..\\Data\\UI\\game_finish_0.png"));
	mButtonList[0]->SetTextObject(new TextObject(_T("턴 종료"),26,RGB(255,255,255))); 
	mButtonList[0]->MouseClickEvent = &OnClickedTurnEndButton;
	mButtonList[0]->MouseOnEvent = &OnMouseTurnEndButton;
	mButtonList[0]->DefaultEvent = &DefaultTurnEndButton;

	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->IsActive = true;
	}

	NextScene = ESceneType::BattleUpdate;
}

void BattleScene::Draw()
{
	// 배틀 배경
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\battle_scene.png")), D2D1::RectF(0, 0, mScreenSize.x, mScreenSize.y));
	
	BattleManager::GetInstance()->mPlayerImage->Draw();
	BattleManager::GetInstance()->mEnemySubImage->Draw();
	BattleManager::GetInstance()->mEnemyWeaponImage->Draw();
	BattleManager::GetInstance()->mEnemyImage->Draw();


	// UI들 순서대로 그리기
	// 현재턴 박스
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\trun_0.png")),
		D2D1::RectF(0, 0, mScreenSize.x * (300.f / mScreenSize.x), mScreenSize.y * (100.f / mScreenSize.y)));


	// 무기 리스트박스
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\the_bottom_bar_0.png")),
		D2D1::RectF(mScreenSize.x * 0.45, mScreenSize.y * 0.867, mScreenSize.x, (mScreenSize.y * 0.867) + 192));
	mWeaponListUI->Draw();

	BattleManager::GetInstance()->PlayerHPBar->Draw();
	BattleManager::GetInstance()->EnemyHPBar->Draw();
	BattleManager::GetInstance()->UnluckyStackBar->Draw();

	// 실험용 그림 띄우기
	//BattleManager::GetInstance()->GameResult->Draw();

	// 실험용 결과배경창 그리기
	BattleManager::GetInstance()->ResultUI->Draw();

	SetTextFont(L"국립박물관문화재단클래식 Medium");

	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Draw();
	}
}

void BattleScene::Update()
{
	NextScene = ESceneType::BattleUpdate;

	BattleManager::GetInstance()->mPlayerImage->Update();
	BattleManager::GetInstance()->mEnemySubImage->SetPosition(BattleManager::GetInstance()->mEnemyImage->GetPosition());
	BattleManager::GetInstance()->mEnemySubImage->Update();
	BattleManager::GetInstance()->mEnemyImage->Update();

	mWeaponListUI->Update();
	BattleManager::GetInstance()->ResultUI->Update();
	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Update();
	}

	// 배틀매니저 업데이트
	if (BattleManager::GetInstance()->Update())
	{
		EBattleResult result = BattleManager::GetInstance()->GetBattleResult();

		switch (result)
		{
		case EBattleResult::BattleWin:
			//전투 승리 로비로
			NextScene = ESceneType::LobbyStart;
			break;
		case EBattleResult::GameOver_HP:
			//체력 닳아서 죽음
			NextScene = ESceneType::TitleStart;
			break;
		case EBattleResult::GameOver_WEAPON:
			//무기 없어서 죽음
			NextScene = ESceneType::TitleStart;
			break;
		case EBattleResult::PlayerWin:
			//미믹이 모두 이김
			NextScene = ESceneType::TitleStart;
			break;
		default:
			break;
		}
	}
}



void BattleScene::OnClickedTurnEndButton()
{
	wcout << L"턴종료버튼임다~" << endl;
	BattleManager::GetInstance()->PlayerTurnEnd();
}
void BattleScene::OnMouseTurnEndButton()
{
	WriteText(1790, 900, 20, RGB(255, 0, 255), "턴종료버튼");

}
void BattleScene::DefaultTurnEndButton()
{
}
