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
	//��Ʈ ���� ����
	void SetBrushColor(COLORREF color);
	//��Ʈ�� ����
	void SetTextFont(PCWSTR fontname);
	//��Ʈ ũ�⸦ ����
	void SetTextSize(int size);

	ID2D1SolidColorBrush* GetBrush() { return mpTextBrush; }
	// ȭ�鿡 ���ڸ� ���
	 bool WriteText(int x, int y, const char* pch, ...);
	 bool WriteTextByRect(D2D1_RECT_F rect, const char* pch, ...);

	 bool WriteTextLayout(Vector2 pos, Vector2 size, const wchar_t* pch, ...);
};



