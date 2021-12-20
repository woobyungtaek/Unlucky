#pragma once
//2020.02.01
//������
// Bitmap Ŭ���� ����

class D2DBitmap :public Singleton<D2DBitmap>
{

private:
	IWICImagingFactory* mpWicFactory;	//ImageFactory
	//ID2D1Bitmap* mpBitmap;				//Bitmap

public:
	D2DBitmap();
	~D2DBitmap();

public:

	//��Ʈ���� �ε�
	 HRESULT LoadSpriteSheet(PCWSTR uri, ID2D1Bitmap** ppBitmap);
	 //�̹��� ���� ���
	 void DrawImage(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect);
	//��������Ʈ ���
	 void DrawSprite(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect);

	 void DrawSpriteByAlpha(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect, float alpha);

	 void DrawImageByPivot(ID2D1Bitmap* bitmap, Vector2 pos, int width, int height);
};


