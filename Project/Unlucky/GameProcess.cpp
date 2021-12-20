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

	//���� �� ����( �̱������� ����ֱ�? ) 
	mGameScene.emplace(L"TitleScene", TitleScene::GetInstance());// (L"TitleScene", new TitleScene());
	mGameScene.emplace(L"LobbyScene", LobbyScene::GetInstance());
	mGameScene.emplace(L"BattleScene", BattleScene::GetInstance());
	mGameScene.emplace(L"GotchaScene", GotchaScene::GetInstance());
	mGameScene.emplace(L"LoadingScene", LoadingScene::GetInstance());

	SoundManager::Init();

	//��� ���� �ε�( ���� �߿�! )
	SkillBook::CreateSkillArray();

	WeaponManager::GetInstance()->LoadWeaponData();
	EnemyManager::GetInstance()->LoadEnemyData();
	StageManager::GetInstance()->LoadEnemyNodeData();
	SpriteManager::GetInstance()->LoadImagefromData();
	//SoundManager::GetInstance()->LoadAllSoundFile();


}

void GameProcess::Update()
{
	//���� ���¿� ���� ���� �Լ��� ���� ���� �Ѵ�.
	(this->*SceneFunction[(int)mCurrentType])();
}

void GameProcess::TitleStart()
{
	//�۾�
	wcout << L"--------------------------------------------------" << endl;
	wcout << L"-                    Unlucky                     -" << endl;
	wcout << L"--------------------------------------------------" << endl;
	wcout << L"1. ���� ����   2. �ҷ�����(�̱���  3. ����(�̱���) " << endl;


	if (mpPlayer == nullptr)
	{
		mpPlayer = new Player();
	}
	mpPlayer->ResetPlayer();

	mGameScene[L"TitleScene"]->Init(g_ScreenSize);


	// ���� ����
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
		wcout << L"[System] ���� ���� �ҷ�����" << endl;
		// ���� �� �÷��̾� �����͸� mpPlayer�� �����Ѵ�.
		// mCurrentType = ESceneType::GameStart;

	}
	else if (InputKeyDown(VK_3))
	{
		wcout << L"[System] ���� ����" << endl;
	}

	//�ε�? ��ο� �̹����� ����� ���� ���� -> �ߵ�!
	//DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\battle_scene.png")), D2D1::RectF(0, 0, 1280, 720));
	//DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\Mimic.png")), D2D1::RectF(400, 0, 700, 300));
}

void GameProcess::BattleStart()
{
	//��Ʋ �� init�ϰ�...
	BattleManager::GetInstance()->Init(mpPlayer);

	mGameScene[L"BattleScene"]->Init(g_ScreenSize);
	mCurrentType = mGameScene[L"BattleScene"]->NextScene;
}

void GameProcess::BattleUpdate()
{
	//��Ʋ ���� ������Ʈ
	mGameScene[L"BattleScene"]->Update();
	mGameScene[L"BattleScene"]->Draw();

	mCurrentType = mGameScene[L"BattleScene"]->NextScene;
}

void GameProcess::LoadingStart()
{
	wcout << L"[Unlucky] �ε� ��ŸƮ! ���� :)" << endl;

	
	mGameScene[L"LoadingScene"]->Init(g_ScreenSize);
	//mCurrentType = mGameScene[L"LoadingScene"]->NextScene;
	mCurrentType = ESceneType::LoadingUpdate;
}

void GameProcess::LoadingUpdate()
{
	//wcout << L"[Unlucky] �ε� ������Ʈ ���� :)" << endl;
	mGameScene[L"LoadingScene"]->Update();
	mGameScene[L"LoadingScene"]->Draw();

	// �ε� ������Ʈ
	mCurrentType = mGameScene[L"LoadingScene"]->NextScene;
	//mCurrentType = ESceneType::LobbyStart;
}

void GameProcess::LobbyStart()
{
	wcout << L"[Unlucky] �κ� ��ŸƮ ���� :)" << endl;
	StageManager::GetInstance()->Init(mpPlayer);
	mGameScene[L"LobbyScene"]->Init(g_ScreenSize);

	mCurrentType = mGameScene[L"LobbyScene"]->NextScene;
}

void GameProcess::LobbyUpdate()
{
	//wcout << L"[Unlucky] �κ� ������Ʈ ���� :)" << endl;
	mGameScene[L"LobbyScene"]->Update();
	mGameScene[L"LobbyScene"]->Draw();

	mCurrentType = mGameScene[L"LobbyScene"]->NextScene;
}

void GameProcess::GotchaStart()
{
	wcout << L"[System] �̱� ����." << endl;
	mGameScene[L"GotchaScene"]->Init(g_ScreenSize);

	mCurrentType = ESceneType::GotcharUpdate;
}

void GameProcess::GotchaUpdate()
{
	wcout << L"[System] �̱� ��." << endl;
	mGameScene[L"GotchaScene"]->Update();
	mGameScene[L"GotchaScene"]->Draw();

	if (InputKeyDown(VK_LBUTTON))
	{
		mCurrentType = ESceneType::LobbyStart;
	}
}

