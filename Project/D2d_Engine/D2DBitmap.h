#pragma once
//2020.02.01
//강주현
// Bitmap 클래스 생성

class D2DBitmap :public Singleton<D2DBitmap>
{

private:
	IWICImagingFactory* mpWicFactory;	//ImageFactory
	//ID2D1Bitmap* mpBitmap;				//Bitmap

public:
	D2DBitmap();
	~D2DBitmap();

public:

	//시트에서 로드
	 HRESULT LoadSpriteSheet(PCWSTR uri, ID2D1Bitmap** ppBitmap);
	 //이미지 한장 출력
	 void DrawImage(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect);
	//스프라이트 출력
	 void DrawSprite(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect);

	 void DrawSpriteByAlpha(ID2D1Bitmap* bitmap, D2D1_RECT_F worldRect, D2D1_RECT_F srcRect, float alpha);

	 void DrawImageByPivot(ID2D1Bitmap* bitmap, Vector2 pos, int width, int height);
};


