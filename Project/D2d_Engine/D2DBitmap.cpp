#include "pch.h"

D2DBitmap::D2DBitmap()
{
	HRESULT hr = S_OK;


	if (SUCCEEDED(hr))
	{
		// Create WIC factory.
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&mpWicFactory)
		);
	}
}

D2DBitmap::~D2DBitmap()
{


}


HRESULT D2DBitmap::LoadSpriteSheet(PCWSTR uri, ID2D1Bitmap** ppBitmap)
{
	//MSDN에 있는 예제 그냥 다 그냥 걍 가져옴..

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;


	//pIWICFactory가 따로 있어야한다.
	HRESULT hr = mpWicFactory->CreateDecoderFromFilename(
		uri,/*경로*/
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED)
		hr = mpWicFactory->CreateFormatConverter(&pConverter);

	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = D2dCore::GetInstance()->GetRenderTarget()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void D2DBitmap::DrawImage(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect)
{
	D2dCore::GetInstance()->GetRenderTarget()->DrawBitmap(
		bitmap,
		worldRect,
		1.0, // 불투명도? 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		NULL);
}

void D2DBitmap::DrawSprite(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect)
{
	D2dCore::GetInstance()->GetRenderTarget()->DrawBitmap(
		bitmap,
		worldRect,
		1.0, // 불투명도? 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect);
}

void D2DBitmap::DrawSpriteByAlpha(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect, float alpha)
{
	D2dCore::GetInstance()->GetRenderTarget()->DrawBitmap(
		bitmap,
		worldRect,
		alpha, // 불투명도? 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect);
}

void D2DBitmap::DrawImageByPivot(ID2D1Bitmap* bitmap, Vector2 pos, int width, int height)
{
	D2dCore::GetInstance()->GetRenderTarget()->DrawBitmap(
		bitmap,
		D2D1::RectF(pos.x-(width/2),pos.y-(height/2),pos.x+(width/2),pos.y+(height/2)),
		1.0, // 불투명도? 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		NULL);
}
