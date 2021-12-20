// AStar.cpp : 애플리케이션에 대한 진입점을 정의합니다.
#include "pch.h"
#include "BoxObject.h"
#include "CircleObject.h"


class SpriteInfo;

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

 const TCHAR* g_ClassName  = _T("ParkGumSa Game");
 const TCHAR* g_WindowName = _T("ParkGumSa Game");

POINT g_ScreenSize;

HINSTANCE ghInst;

vector<SpriteInfo> testSpriteInfoVec[5]; //테스트 용 모션 1개에 대한 spriteInfo data

int testFrame; //테스트용 현재 프레임

//
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;

	ghInst = hInstance;
	g_ScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
	g_ScreenSize.y = GetSystemMetrics(SM_CYSCREEN);

	//메인 윈도우 등록
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)MainMsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = ghInst;
	wc.hIcon = LoadIcon(ghInst, (LPCTSTR)IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, (LPCTSTR)IDI_APPLICATION);
	RegisterClassEx(&wc);

	hWnd = CreateWindowW(
		g_ClassName,
		_T("Main Window Title"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		g_ScreenSize.x, g_ScreenSize.y,
		GetDesktopWindow(),
		NULL,
		ghInst,
		NULL
	);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);


	Initialize(hWnd);

	//BoxObject* box = new BoxObject();
	//CircleObject* circle = new CircleObject(60);
	//CircleObject* c2 = new CircleObject(40);

	//GameObject* Zelda = new GameObject();

	int _x1 = 200;
	int _y1 = 200;

	int _x2 = 300;
	int _y2 = 300;

	bool bCCcheck = false;
	int CCcheckcount = 0;
	
	SoundManager::Init();
	SoundManager* sound = new SoundManager("..\\Data\\ParkGumSa.mp3",true);
	SoundManager* sound2 = new SoundManager("..\\Data\\ParkGumSa.mp3", true);
	SpriteManager::GetInstance()->LoadImageFile(_T("..\\Data\\LinkSprite.png"));
	SpriteManager::GetInstance()->LoadImageFile(_T("..\\Data\\back1.jpg"));
	SpriteManager::GetInstance()->LoadImageFile(_T("..\\Data\\back2.png"));
	/*
	for (int index = 0; index < 10; index++)
	{
		SpriteInfo instInfo;
		instInfo.FileName = _T("..\\Data\\LinkSprite.png");
		instInfo.Motion = 1;
		instInfo.Frame = index;

		D2D1_RECT_F srcRect;
		srcRect.left = index * 96;
		srcRect.top = 0+104*4;
		srcRect.right = (index + 1) * 96;
		srcRect.bottom = 104*5;
		instInfo.SrcRect = srcRect;

		instInfo.Pivot.x = 96 / 2;
		instInfo.Pivot.y = 104;

		testSpriteInfoVec.push_back(instInfo);
	}
	*/
	POINT p = { 0, 0 };

	for (int index = 0; index < 3; index++)
	{
		testSpriteInfoVec[0].push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\LinkSprite.png"), 0, 96, 104, p));
	}
	for (int index = 0; index < 10; index++)
	{
		testSpriteInfoVec[1].push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\LinkSprite.png"), 4, 96, 104, p));
	}
	for (int index = 0; index < 10; index++)
	{
		testSpriteInfoVec[2].push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\LinkSprite.png"), 5, 96, 104, p));
	}
	for (int index = 0; index < 10; index++)
	{
		testSpriteInfoVec[3].push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\LinkSprite.png"), 6, 96, 104, p));
	}
	for (int index = 0; index < 10; index++)
	{
		testSpriteInfoVec[4].push_back(SpriteManager::GetInstance()->GetAniData(index, _T("..\\Data\\LinkSprite.png"), 7, 96, 104, p));
	}
	//testSpriteInfoVec = SpriteManager::GetInstance()->GetAnimtaionData(_T("..\\Data\\LinkSprite.png"), 1, 10, 96, 104, p);

	int Aninum = 1;
	POINT point = { 100, 100 };

	sound->play();

	sound->volumeUp();
	SetFPS(60);
	int Anicount = 0;
	int AniWidth = 6;

	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) { break; }
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		}

	}


	delete sound;

	SoundManager::Release();

	UnregisterClass(g_ClassName, wc.hInstance);
	return 0;
}

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//사이즈 고정에 랜더타겟이 필요한데  위에서 전역으로 생성해서 따로 초기화가 필요하다
	Initialize(hwnd);

	switch (msg)
	{
	case WM_CLOSE:
	{
		int res = MessageBox(hwnd, _T("프로그램 종료"), _T("EXIT"), MB_YESNO | MB_ICONQUESTION);
		if (res == IDNO)
		{	
			return 0;
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		D2D1_SIZE_U resize;
		resize.height = HIWORD(lParam);
		resize.width = LOWORD(lParam);

		//D2dCore::GetInstance()->GetRenderTarget()->Resize(&resize);
		ReSize(resize);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}