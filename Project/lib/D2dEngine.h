#pragma once

namespace D2dEngine
{
	/// Core
	void Initialize(HWND hwnd);

	void BeginRender();

	void EndRender();
	//윈도우 사이즈 변경시 
	void ReSize(D2D1_SIZE_U resize);

	///	Write
	bool WriteText(int x, int y, int size, COLORREF color, const char* pch, ...);

	bool WriteText(int x, int y, const char* pch, ...);
	
	bool WriteText(D2D1_RECT_F worldRect, int size, COLORREF color, const char* pch, ...);

	bool WriteTextLayout(Vector2 pos, Vector2 size, int _size, COLORREF color, const wchar_t* pch, ...);
	void SetTextColor(COLORREF color);
	//폰트를 설정
	void SetTextFont(PCWSTR fontname);
	//폰트 크기를 설정
	void SetTextSize(int size);

	///	GDI
	void DrawLine(int x1, int y1, int x2, int y2, int size, COLORREF color);

	void DrawRect(int left, int top, int right, int bottom, COLORREF color);

    void DrawRect(D2D1_RECT_F worldRect, COLORREF color);

	void DrawEilpse(int posx, int posy, int radius, COLORREF color);

	/// Input
	bool InputKey(int vk);

	bool InputKeyDown(int vk);

	bool InputKeyUp(int vk);

	void KeyUpdate();
	void MouseUpdate();
	POINT GetMousePosCT();
	POINT GetMousePosSC();

	///	Bitmap
	void  LoadIamge(PCWSTR uri, ID2D1Bitmap** ppBitmap);

	bool  LoadIamgeResult(PCWSTR uri, ID2D1Bitmap** ppBitmap);

	void DrawImage(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect);

	void DrawSprite(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect);

	void DrawSpriteByAlpha(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect, float alpha);

	void DrawImageByPivot(ID2D1Bitmap* bitmap, Vector2 pos, int width, int height);

	/// Time
	//프레임 설정
	void SetFPS(float fps);
	//프레임 체크
	bool FPSCheck();
}