#include "pch.h"

#include "BattleManager.h"
#include "WeaponManager.h"

#include "GameProcess.h"


extern POINT g_ScreenSize;

void GameProcess::Init()
{
	SceneFunction[(int)ESceneType::TitleStart] = &GameProcess::TitleStart;
	SceneFunction[(int)ESceneType::TitleUpdate] = &GameProcess::TitleUpdate;
	SceneFunction[(int)ESceneType::LoadingStart] = &GameProcess::LoadingStart;
	SceneFunction[(int)ESceneType::LoadingUpdate] = &GameProcess::LoadingUpdate;
	SceneFunction[(int)ESceneType::LobbyStart] = &GameProcess::LobbyStart;
	SceneFunction[(int)ESceneType::LobbyUpdate] = &GameProcess::LobbyUpdate;
	SceneFunction[(int)ESceneType::BattleStart] = &GameProcess::BattleStart;
	SceneFunction[(int)ESceneType::BattleUpdate] = &GameProcess::BattleUpdate;
	SceneFunction[(int)ESceneType::GotcharStart] = &GameProcess::GotchaStart;
	SceneFunction[(int)ESceneType::GotcharUpdate] = &GameProcess::GotchaUpdate;

	srand((unsigned int)time(0));

	//게임 씬 생성( 싱글톤으로 집어넣기? ) 
	mGameScene.emplace(L"TitleScene", TitleScene::GetInstance());// (L"TitleScene", new TitleScene());
	mGameScene.emplace(L"LobbyScene", LobbyScene::GetInstance());
	mGameScene.emplace(L"BattleScene", BattleScene::GetInstance());
	mGameScene.emplace(L"GotchaScene", GotchaScene::GetInstance());
	mGameScene.emplace(L"LoadingScene", LoadingScene::GetInstance());

	SoundManager::Init();

	//모든 파일 로드( 순서 중요! )
	SkillBook::CreateSkillArray();

	WeaponManager::GetInstance()->LoadWeaponData();
	EnemyManager::GetInstance()->LoadEnemyData();
	StageManager::GetInstance()->LoadEnemyNodeData();
	SpriteManager::GetInstance()->LoadImagefromData();
	//SoundManager::GetInstance()->LoadAllSoundFile();


}

void GameProcess::Update()
{
	//현재 상태에 따라 씬의 함수를 직접 실행 한다.
	(this->*SceneFunction[(int)mCurrentType])();
}

void GameProcess::TitleStart()
{
	//작업
	wcout << L"--------------------------------------------------" << endl;
	wcout << L"-                    Unlucky                     -" << endl;
	wcout << L"--------------------------------------------------" << endl;
	wcout << L"1. 게임 시작   2. 불러오기(미구현  3. 종료(미구현) " << endl;


	if (mpPlayer == nullptr)
	{
		mpPlayer = new Player();
	}
	mpPlayer->ResetPlayer();

	mGameScene[L"TitleScene"]->Init(g_ScreenSize);


	// 상태 변경
	mCurrentType = mGameScene[L"TitleScene"]->NextScene;
}

void GameProcess::TitleUpdate()
{
	mGameScene[L"TitleScene"]->Update();
	mGameScene[L"TitleScene"]->Draw();

	mCurrentType = mGameScene[L"TitleScene"]->NextScene;

	if (InputKeyDown(VK_1))
	{
		mCurrentType = ESceneType::LoadingStart;
		//mCurrentType = ESceneType::LobbyStart;

	}
	else if (InputKeyDown(VK_2))
	{
		wcout << L"[System] 저장 게임 불러오기" << endl;
		// 저장 된 플레이어 데이터를 mpPlayer에 셋팅한다.
		// mCurrentType = ESceneType::GameStart;

	}
	else if (InputKeyDown(VK_3))
	{
		wcout << L"[System] 게임 종료" << endl;
	}

	//로드? 드로우 이미지가 제대로 동작 안함 -> 잘됨!
	//DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\battle_scene.png")), D2D1::RectF(0, 0, 1280, 720));
	//DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\Mimic.png")), D2D1::RectF(400, 0, 700, 300));
}

void GameProcess::BattleStart()
{
	//배틀 씬 init하고...
	BattleManager::GetInstance()->Init(mpPlayer);

	mGameScene[L"BattleScene"]->Init(g_ScreenSize);
	mCurrentType = mGameScene[L"BattleScene"]->NextScene;
}

void GameProcess::BattleUpdate()
{
	//배틀 씬이 업데이트
	mGameScene[L"BattleScene"]->Update();
	mGameScene[L"BattleScene"]->Draw();

	mCurrentType = mGameScene[L"BattleScene"]->NextScene;
}

void GameProcess::LoadingStart()
{
	wcout << L"[Unlucky] 로딩 스타트! 진입 :)" << endl;

	
	mGameScene[L"LoadingScene"]->Init(g_ScreenSize);
	//mCurrentType = mGameScene[L"LoadingScene"]->NextScene;
	mCurrentType = ESceneType::LoadingUpdate;
}

void GameProcess::LoadingUpdate()
{
	//wcout << L"[Unlucky] 로딩 업데이트 진입 :)" << endl;
	mGameScene[L"LoadingScene"]->Update();
	mGameScene[L"LoadingScene"]->Draw();

	// 로딩 업데이트
	mCurrentType = mGameScene[L"LoadingScene"]->NextScene;
	//mCurrentType = ESceneType::LobbyStart;
}

void GameProcess::LobbyStart()
{
	wcout << L"[Unlucky] 로비 스타트 진입 :)" << endl;
	StageManager::GetInstance()->Init(mpPlayer);
	mGameScene[L"LobbyScene"]->Init(g_ScreenSize);

	mCurrentType = mGameScene[L"LobbyScene"]->NextScene;
}

void GameProcess::LobbyUpdate()
{
	//wcout << L"[Unlucky] 로비 업데이트 진입 :)" << endl;
	mGameScene[L"LobbyScene"]->Update();
	mGameScene[L"LobbyScene"]->Draw();

	mCurrentType = mGameScene[L"LobbyScene"]->NextScene;
}

void GameProcess::GotchaStart()
{
	wcout << L"[System] 뽑기 시작." << endl;
	mGameScene[L"GotchaScene"]->Init(g_ScreenSize);

	mCurrentType = ESceneType::GotcharUpdate;
}

void GameProcess::GotchaUpdate()
{
	wcout << L"[System] 뽑기 중." << endl;
	mGameScene[L"GotchaScene"]->Update();
	mGameScene[L"GotchaScene"]->Draw();

	if (InputKeyDown(VK_LBUTTON))
	{
		mCurrentType = ESceneType::LobbyStart;
	}
}

