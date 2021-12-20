#include "pch.h"


namespace D2dEngine
{
	void Initialize(HWND hwnd)
	{
		D2dCore::GetInstance()->Initialize(hwnd);
	}
	void BeginRender()
	{
		D2dCore::GetInstance()->BeginRender();
	}

	void EndRender()
	{
		D2dCore::GetInstance()->EndRender();
	}

	void ReSize(D2D1_SIZE_U resize)
	{
		D2dCore::GetInstance()->GetRenderTarget()->Resize(&resize);
	}

	bool WriteText(int x, int y, int size, COLORREF color, const char* pch, ...)
	{
		//char str[256];
		//sprintf_s(str, "%d", (int)pch);

		D2DWrite::GetInstance()->SetTextSize(size);
		D2DWrite::GetInstance()->SetBrushColor(color);
		return D2DWrite::GetInstance()->WriteText(x, y, pch);
	}

	bool WriteText(D2D1_RECT_F worldRect, int size, COLORREF color, const char* pch, ...)
	{
		//char str[256];
		//sprintf_s(str, "%d", (int)pch);

		D2DWrite::GetInstance()->SetTextSize(size);
		D2DWrite::GetInstance()->SetBrushColor(color);
		return D2DWrite::GetInstance()->WriteTextByRect(worldRect, pch);
	}

	bool WriteTextLayout(Vector2 pos, Vector2 size, int _size, COLORREF color, const wchar_t* pch, ...)
	{
		//wchar_t str[256];
		//wprintf_s(str, "%d", (int)pch);

		D2DWrite::GetInstance()->SetTextSize(_size);
		D2DWrite::GetInstance()->SetBrushColor(color);

		return D2DWrite::GetInstance()->WriteTextLayout(pos, size, pch);
	}

	bool WriteText(int x, int y, const char* pch, ...)
	{
		char str[256];
		sprintf_s(str, "%d", (int)pch);

		return D2DWrite::GetInstance()->WriteText(x, y, pch);
	}


	void SetTextColor(COLORREF color)
	{
		D2DWrite::GetInstance()->SetBrushColor(color);
	}

	void SetTextFont(PCWSTR fontname)
	{
		D2DWrite::GetInstance()->SetTextFont(fontname);
	}

	void SetTextSize(int size)
	{
		D2DWrite::GetInstance()->SetTextSize(size);
	}

	void DrawLine(int x1, int y1, int x2, int y2, int size, COLORREF color)
	{
		D2DGDI::GetInstance()->DrawLine1(x1, y1, x2, y2, size, color);
	}

	void DrawRect(int left, int top, int right, int bottom, COLORREF color)
	{
		D2DGDI::GetInstance()->DrawRect(left, top, right, bottom, color);
	}

	void DrawRect(D2D1_RECT_F worldRect, COLORREF color)
	{
		D2DGDI::GetInstance()->DrawRectByRect(worldRect, color);
	}

	void DrawEilpse(int posx, int posy, int radius, COLORREF color)
	{
		D2DGDI::GetInstance()->DrawEilpse(posx, posy , radius,  color);
	}

	bool InputKey(int vk)
	{
		return Input::GetInstance()->InputKey(vk);
	}

	bool InputKeyDown(int vk)
	{
		return Input::GetInstance()->InputKeyDown(vk);
	}

	bool InputKeyUp(int vk)
	{
		return Input::GetInstance()->InputKeyUp(vk);
	}

	void KeyUpdate()
	{
		Input::GetInstance()->KeyUpdate();
	}

	void MouseUpdate()
	{
		Input::GetInstance()->MouseUpdate();
	}

	POINT GetMousePosCT()
	{
		return Input::GetInstance()->GetMousePosCT();
	}

	POINT GetMousePosSC()
	{
		return Input::GetInstance()->GetMousePosSC();
	}

	bool LoadIamgeResult(PCWSTR uri, ID2D1Bitmap** ppBitmap)
	{		
		return SUCCEEDED(D2DBitmap::GetInstance()->LoadSpriteSheet(uri, ppBitmap));
	}
	void LoadIamge(PCWSTR uri, ID2D1Bitmap** ppBitmap)
	{
		D2DBitmap::GetInstance()->LoadSpriteSheet(uri, ppBitmap);
	}

	void DrawImage(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect)
	{
		D2DBitmap::GetInstance()->DrawImage(bitmap, worldRect);
	}

	void DrawSprite(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect)
	{
		D2DBitmap::GetInstance()->DrawSprite(bitmap, worldRect, srcRect);
	}

	void DrawSpriteByAlpha(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect, float alpha)
	{
		D2DBitmap::GetInstance()->DrawSpriteByAlpha(bitmap, worldRect, srcRect, alpha);
	}

	void DrawImageByPivot(ID2D1Bitmap* bitmap, Vector2 pos, int width, int height)
	{
		D2DBitmap::GetInstance()->DrawImageByPivot(bitmap, pos, width,height);
	}

	void SetFPS(float fps)
	{
		TimeController::GetInstance()->SetFPS(fps);
	}

	bool FPSCheck()
	{
		return TimeController::GetInstance()->FPSCheck();
	}

}