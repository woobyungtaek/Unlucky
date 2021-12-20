// Unlucky.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "GameProcess.h" 
#include "Unlucky.h"

LRESULT CALLBACK MainMsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

const TCHAR* g_ClassName = _T("Unlucky");
const TCHAR* g_WindowName = _T("Unlucky");

POINT g_ScreenSize;

HINSTANCE ghInst;

//
int APIENTRY WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASSEX wc;

	ghInst = hInstance;
	g_ScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
	g_ScreenSize.y =GetSystemMetrics(SM_CYSCREEN);

	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, g_ScreenSize.x, 700, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	wcin.imbue(locale("korean"));
	wcout.imbue(locale("korean"));

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

	hWnd = CreateWindowExW(
		WS_EX_APPWINDOW,
		g_ClassName,
		g_WindowName,
		// WS_OVERLAPPEDWINDOW,
		WS_POPUP,
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

	GameProcess mainProcess;
	mainProcess.Init();

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
			if (FPSCheck() == true)
			{	

				if (InputKey(VK_ESCAPE))
				{
					PostQuitMessage(0);
				}
				KeyUpdate();
				MouseUpdate();
				BeginRender();

				mainProcess.Update();
				
				EndRender();
			}
	
		}
	}
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

		ReSize(resize);
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}