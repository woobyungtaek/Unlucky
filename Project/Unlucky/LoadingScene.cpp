#include "pch.h"
#include "LoadingScene.h"

LoadingScene::LoadingScene()
	: Frame(NULL), ChcekFrm(NULL)
{
	for (int index = 0; index < 19; index++)
	{
		CString str;
		str.Format(_T("..\\Data\\Opening\\%d.png"), index);
		Opening.push_back(SpriteManager::GetInstance()->GetAniData(index, str, 1920, 1080));
	}
}

LoadingScene::~LoadingScene()
{
	delete Open_Book_SFX;
}

void LoadingScene::Init(POINT screenSize)
{
	mScreenSize = screenSize;
	Frame = 0;
	ChcekFrm = -1;
	Open_Book_SFX = new SoundManager("..\\Data\\Sounds\\Open_Book_SFX.mp3", false);
	NextScene = ESceneType::LoadingUpdate;
}

void LoadingScene::Draw()
{
	DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(Opening[Frame]->FileName),
		D2D1::RectF(0,
					0,
			mScreenSize.x,
			mScreenSize.y)
	);
}

void LoadingScene::Update()
{
	NextScene = ESceneType::LoadingUpdate;
	Open_Book_SFX->Update();
	if (InputKeyDown(VK_0))
	{
		NextScene = ESceneType::LobbyStart;
	}
	if (Frame != 20)
	{
		ChcekFrm += 1;
		ChcekFrm %= 10;
		if (ChcekFrm == 0)
		{
			if (Frame < 12)
			{
				Frame += 1;
				wcout << L"[System] Frame =" << Frame << endl;
			}
			else
			{	
				if (InputKey(VK_LBUTTON))
				{
					
					if (Frame == 18)
					{
						Open_Book_SFX->play();
						NextScene = ESceneType::LobbyStart;
						
					}
					else
					{
						Open_Book_SFX->play();
						Frame += 1;
						//Frame %= 15;
					}
					wcout << L"[System] Frame =" << Frame << endl;
				}
			}
		}
		
	}
	else
	{
		//NextScene = ESceneType::LobbyStart;
	}
	
}
