#include "pch.h"

D2dCore::D2dCore() 
	: mHwnd(nullptr),mpDirect2dFactory(nullptr),mpRenderTarget(nullptr),mMainHresult(NULL)
	//,mD2DeviceContext(nullptr), mpD2DDevice1(nullptr),mpSwapChain(nullptr),mpD2DTargetBitmap(nullptr),mdpi(NULL)
{

}

D2dCore::~D2dCore()
{
	SafeRelease(&mpDirect2dFactory);
	SafeRelease(&mpRenderTarget);
}

void D2dCore::Initialize(HWND hwnd)
{
	//HRESULT _hResult = CoInitialize(NULL);

	mHwnd = hwnd;
	HRESULT hr = S_OK;

	 hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&mpDirect2dFactory
	);
	mMainHresult = CreateGraphicsResources();

	//타이머 초기화
	TimeController::GetInstance()->Initialize();

}

HRESULT D2dCore::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	
	if (mpRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(mHwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		hr = mpDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(mHwnd, size),
			&mpRenderTarget);


	}
	/*
	
	if (mD2DeviceContext == nullptr)
	{
		// This flag adds support for surfaces with a different color channel ordering than the API default.
		// You need it for compatibility with Direct2D.
		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

		// This array defines the set of DirectX hardware feature levels this app  supports.
		// The ordering is important and you should  preserve it.
		// Don't forget to declare your app's minimum required feature level in its
		// description.  All apps are assumed to support 9.1 unless otherwise stated.
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		// Create the DX11 API device object, and get a corresponding context.
		ID3D11Device* _D3D11Device;
		ID3D11DeviceContext* _D3D11DeviceContext;		// DirectX Core Objects. Required for 2D and 3D.

		D3D11CreateDevice(
			nullptr,                    // specify null to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			0,
			creationFlags,              // optionally set debug and Direct2D compatibility flags
			featureLevels,              // list of feature levels this app can support
			ARRAYSIZE(featureLevels),   // number of possible feature levels
			D3D11_SDK_VERSION,
			&_D3D11Device,              // returns the Direct3D device created
			&mfeatureLevel,            // returns feature level of device created
			&_D3D11DeviceContext		// returns the device immediate context
		);

		// Obtain the underlying DXGI device of the Direct3D11 device.
		IDXGIDevice* dxgiDevice;
		_D3D11Device->QueryInterface(&dxgiDevice);	/// ComPtr.As()

		// Obtain the Direct2D device for 2-D rendering.
		mpDirect2dFactory->CreateDevice(dxgiDevice, &mpD2DDevice1);

		// Get Direct2D device's corresponding device context object.
		hr = mpD2DDevice1->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
			&mD2DeviceContext);

		if (SUCCEEDED(hr))
		{
			// Create brushes.
// 			hr = m_D2DeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &m_pWhiteBrush);
// 			hr = m_D2DeviceContext->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 0.f), &m_pYellowBrush);
// 			hr = m_D2DeviceContext->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f), &m_pNowBrush);
		}

		// Allocate a descriptor.
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
		swapChainDesc.Width = 0;                           // 0 : use automatic sizing
		swapChainDesc.Height = 0;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; // this is the most common swapchain format
		swapChainDesc.Stereo = false;
		swapChainDesc.SampleDesc.Count = 1;                // don't use multi-sampling
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;                     // use double buffering to enable flip
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // all apps must use this SwapEffect
		swapChainDesc.Flags = 0;

		// Identify the physical adapter (GPU or card) this device is runs on.
		IDXGIAdapter* dxgiAdapter;
		dxgiDevice->GetAdapter(&dxgiAdapter);

		// Get the factory object that created the DXGI device.
		IDXGIFactory2* dxgiFactory;
		dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

		// Get the final swap chain for this window from the DXGI factory.
		DXGI_RATIONAL rate;
		rate.Denominator = 60;
		rate.Numerator = 1;

		DXGI_SWAP_CHAIN_FULLSCREEN_DESC swapChainDescFull;
		swapChainDescFull.RefreshRate = rate;
		swapChainDescFull.Scaling = DXGI_MODE_SCALING_STRETCHED;
		swapChainDescFull.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST;
		swapChainDescFull.Windowed = true;

		dxgiFactory->CreateSwapChainForHwnd(_D3D11Device,
			mHwnd,
			&swapChainDesc,
			&swapChainDescFull, // 전체화면 스왑체인 설정
			nullptr,
			&mpSwapChain);

		// Ensure that DXGI doesn't queue more than one frame at a time.
		///dxgiDevice->SetMaximumFrameLatency(1);

		// Get the backbuffer for this window which is be the final 3D render target.
		ID3D11Texture2D* _backBuffer;
		mpSwapChain->GetBuffer(0, IID_PPV_ARGS(&_backBuffer));

		// Now we set up the Direct2D render target bitmap linked to the swapchain. 
		// Whenever we render to this bitmap, it is directly rendered to the 
		// swap chain associated with the window.
		D2D1_BITMAP_PROPERTIES1 _bitmapProperties =
			D2D1::BitmapProperties1(
				D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
				D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
				mdpi,
				mdpi
			);

		// Direct2D needs the dxgi version of the backbuffer surface pointer.
		IDXGISurface* dxgiBackBuffer;
		mpSwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

		// Get a D2D surface from the DXGI back buffer to use as the D2D render target.
		mD2DeviceContext->CreateBitmapFromDxgiSurface(
			dxgiBackBuffer,
			&_bitmapProperties,
			&mpD2DTargetBitmap
		);

		// Now we can set the Direct2D render target.
		mD2DeviceContext->SetTarget(mpD2DTargetBitmap);


		// 테스트용 비트맵 로드
		//this->LoadTestImage();
	}
	*/
	return hr;
}

void D2dCore::BeginRender()
{

	//mMainHresult = CreateGraphicsResources();
	if (SUCCEEDED(mMainHresult))
	{
		mpRenderTarget->BeginDraw();

		mpRenderTarget->Clear();

	}
}

void D2dCore::EndRender()
{
	if (SUCCEEDED(mMainHresult))
	{
		mpRenderTarget->EndDraw();
	}
}


