#pragma once
/*
* 우병택 2021.01.31

	엔진 Core
	> 엔진 생성, 초기화
	> 이벤트 함수들

*/
using namespace std;
template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class Vector2;

class D2dCore : public Singleton<D2dCore>
{

private:
	HWND mHwnd;								//윈도우 핸들
	ID2D1Factory1* mpDirect2dFactory;		//D2d Factory
	ID2D1HwndRenderTarget* mpRenderTarget;	//D2d RenderTarget
	HRESULT mMainHresult;					
	/*
	ID2D1DeviceContext* mD2DeviceContext;		// MK2. RenderTarget대신 사용할 DC. 사실 상속한 것이다.
	D3D_FEATURE_LEVEL mfeatureLevel;			// 어디까지 기능을 지원하는가? Cached renderer properties.
	ID2D1Device* mpD2DDevice1;					// D2D디바이스
	IDXGISwapChain1* mpSwapChain;
	ID2D1Bitmap1* mpD2DTargetBitmap;
	float mdpi;
	*/
public:
	//생성 소멸자
	 D2dCore();
	 ~D2dCore();
public:
	//Getter
	HWND					GetHwnd()			{ return mHwnd; }
	HRESULT					GetHresult() 		{ return mMainHresult; }
	ID2D1HwndRenderTarget*	GetRenderTarget()	{ return mpRenderTarget; }
	//ID2D1DeviceContext*		GetDeviceContext()	{ return mD2DeviceContext; }
	//ID2D1Bitmap1*			GetBitmap()			{ return mpD2DTargetBitmap; }
	
	//초기화
	void Initialize(HWND hwnd);
	HRESULT CreateGraphicsResources();

	//이벤트 함수
	void BeginRender();
	void EndRender();
};


