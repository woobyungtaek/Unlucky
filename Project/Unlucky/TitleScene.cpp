#include "pch.h"

class GameProcess;
//class SoundManager;

//ESceneType TitleScene::NextScene;

TitleScene::TitleScene()
	: Frame(NULL), ChcekFrm(NULL), Alpha(NULL), AlphaTurn(TRUE)
{
	for (int index = 0; index < 3; index++)
	{
		mButtonList.push_back(new Button());
	}
	
}

TitleScene::~TitleScene()
{
	delete Openning_Bgm;
}

// 0번 : 게임 타이틀
// 1번 : 게임 시작
// 2번 : 게임 종료
void TitleScene::Init(POINT screensize)
{
	mScreenSize = screensize;

	mButtonList[0]->Init(800, 215, Vector2(mScreenSize.x / 2, mScreenSize.y * 0.28));
	mButtonList[0]->SetImgName(_T("..\\Data\\title.png"));
	mButtonList[0]->MouseClickEvent = &OnClickedTitleButton;
	mButtonList[0]->MouseOnEvent = &OnMouseTitleButton;
	mButtonList[0]->DefaultEvent = &DefaultTitleButton;

	mButtonList[1]->Init(200, 135, Vector2(mScreenSize.x / 2, mScreenSize.y * 0.55));
	mButtonList[1]->SetImgName(_T("..\\Data\\title_start.png"));
	mButtonList[1]->MouseClickEvent = &OnClickedGameStartButton;
	mButtonList[1]->MouseOnEvent = &OnMouseGameStartButton;
	mButtonList[1]->DefaultEvent = &DefaultGameStartButton;

	mButtonList[2]->Init(120, 135, Vector2(mScreenSize.x / 2, mScreenSize.y * 0.75));
	mButtonList[2]->SetImgName(_T("..\\Data\\title_exit.png"));
	mButtonList[2]->MouseClickEvent = &OnClickedExitButton;
	mButtonList[2]->MouseOnEvent = &OnMouseExitButton;
	mButtonList[2]->DefaultEvent = &DefaultExitButton;

	for (int index = 0; index < 4; index++)
	{
		TitleEffect.push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\title_ani.png"), 698, 866));
	}
	Frame = 0;
	ChcekFrm = 0;
	Alpha = 0.0f;
	AlphaTurn = true;
	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->IsActive = true;
	}

	Openning_Bgm = new SoundManager("..\\Data\\Sounds\\Openning_Bgm.mp3", true);
	Openning_Bgm->play();
	NextScene = ESceneType::TitleUpdate;
}

void TitleScene::Update()
{
	NextScene = ESceneType::TitleUpdate;
	Openning_Bgm->Update();

	if (Frame != 42)
	{
		ChcekFrm += 1;
		ChcekFrm %= 10;

		if (ChcekFrm == 0)
		{

			if (AlphaTurn)
			{
				Frame += 1;
				Frame %= 10;
				Alpha += 0.1f;
				if (Frame == 0)
				{
					//Alpha = 0.0f;
					AlphaTurn = false;
				}
			}
			else
			{
				Frame += 1;
				Frame %= 10;
				Alpha -= 0.1f;
				if (Frame == 0)
				{
					//Alpha = 0.0f;
					AlphaTurn = true;
				}
			}
				wcout << L"[System] Frame =" << Frame << endl;
			
		}

	}
	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Update();
	}
}

void TitleScene::Draw()
{
	// DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\hero_woman_test_01.png")), 
	// 	D2D1::RectF(0,0,1920,1080));
	//DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\Weapon\\Dagger_5.png")), D2D1::RectF(270, 200, 370, 400));
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\title_background.png")), D2D1::RectF(0, 0, mScreenSize.x, mScreenSize.y));
	char str[256];
	//sprintf_s(str, "%s", "%%");

	//WriteText(100, 100, str);

	SetTextFont(L"국립박물관문화재단클래식 Medium");
	for (int index = 0; index < mButtonList.size(); index++)
	{
		mButtonList[index]->Draw();
	}
	/*
	DrawSpriteByAlpha(SpriteManager::GetInstance()->GetSpriteByPath(TitleEffect[2]->FileName),
		D2D1::RectF(0,
			0,
			mScreenSize.x,
			mScreenSize.y),
		TitleEffect[2]->SrcRect,Alpha);
	*/
}


//버튼 이벤트들
void TitleScene::OnClickedTitleButton()
{
	wcout << "TitleButton Click" << endl;
}
void TitleScene::OnMouseTitleButton()
{

}
void TitleScene::DefaultTitleButton()
{
	
}

void TitleScene::OnClickedGameStartButton()
{
	wcout << "GameStartButton Click" << endl;
	TitleScene::GetInstance()->Openning_Bgm->pause();

	NextScene = ESceneType::LoadingStart;
	//NextScene = ESceneType::LobbyStart;
}
void TitleScene::OnMouseGameStartButton()
{
}
void TitleScene::DefaultGameStartButton()
{
}

void TitleScene::OnClickedExitButton()
{
	wcout << "ExitButton Click" << endl;
	PostQuitMessage(0);
}
void TitleScene::OnMouseExitButton()
{
}
void TitleScene::DefaultExitButton()
{
}
