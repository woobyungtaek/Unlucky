#pragma once

class D2DSprite
{
private:
	static D2DSprite* mInstance;

public:
	static D2DSprite* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new D2DSprite();
		}

		return mInstance;
	}
private:
	map<PCWSTR, ID2D1Bitmap*> mBitmapMap;
private:
	D2DSprite();
	~D2DSprite();
public:


	void LoadImageFile(PCWSTR uri);
	ID2D1Bitmap* GetSpriteByPath(PCWSTR path);

	vector<SpriteInfo> GetAnimtaionData(PCWSTR uri,int motion,int maxfrm,int width,int height, POINT pivot);
};

