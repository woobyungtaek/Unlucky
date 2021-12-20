#pragma once

class D2DWrite : public Singleton<D2DWrite>
{
private:

	IDWriteFactory* mpDWriteFactory;		//DwriteFactory
	IDWriteTextFormat* mpTextFormat;		//TextFormat
	IDWriteTextLayout* mpTextLayout;		//TextLayout
	ID2D1SolidColorBrush* mpTextBrush;		//Text Brush

	PCWSTR mpFontName;
	int mTextSize;

public:
	D2DWrite();
	~D2DWrite();

public:
	//폰트 색을 설정
	void SetBrushColor(COLORREF color);
	//폰트를 설정
	void SetTextFont(PCWSTR fontname);
	//폰트 크기를 설정
	void SetTextSize(int size);

	ID2D1SolidColorBrush* GetBrush() { return mpTextBrush; }
	// 화면에 문자를 출력
	 bool WriteText(int x, int y, const char* pch, ...);
	 bool WriteTextByRect(D2D1_RECT_F rect, const char* pch, ...);

	 bool WriteTextLayout(Vector2 pos, Vector2 size, const wchar_t* pch, ...);
};



