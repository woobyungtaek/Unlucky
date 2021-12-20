#pragma once
/*
* �캴�� 2021.01.31

	���� Core
	> ���� ����, �ʱ�ȭ
	> �̺�Ʈ �Լ���

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
	HWND mHwnd;								//������ �ڵ�
	ID2D1Factory1* mpDirect2dFactory;		//D2d Factory
	ID2D1HwndRenderTarget* mpRenderTarget;	//D2d RenderTarget
	HRESULT mMainHresult;					
	/*
	ID2D1DeviceContext* mD2DeviceContext;		// MK2. RenderTarget��� ����� DC. ��� ����� ���̴�.
	D3D_FEATURE_LEVEL mfeatureLevel;			// ������ ����� �����ϴ°�? Cached renderer properties.
	ID2D1Device* mpD2DDevice1;					// D2D����̽�
	IDXGISwapChain1* mpSwapChain;
	ID2D1Bitmap1* mpD2DTargetBitmap;
	float mdpi;
	*/
public:
	//���� �Ҹ���
	 D2dCore();
	 ~D2dCore();
public:
	//Getter
	HWND					GetHwnd()			{ return mHwnd; }
	HRESULT					GetHresult() 		{ return mMainHresult; }
	ID2D1HwndRenderTarget*	GetRenderTarget()	{ return mpRenderTarget; }
	//ID2D1DeviceContext*		GetDeviceContext()	{ return mD2DeviceContext; }
	//ID2D1Bitmap1*			GetBitmap()			{ return mpD2DTargetBitmap; }
	
	//�ʱ�ȭ
	void Initialize(HWND hwnd);
	HRESULT CreateGraphicsResources();

	//�̺�Ʈ �Լ�
	void BeginRender();
	void EndRender();
};


