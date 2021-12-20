#pragma once
class Sprite;

class SpriteManager
{
private:
	static SpriteManager* mInstance;

	SpriteManager() {}
public:
	static SpriteManager* GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SpriteManager();
		}
		return mInstance;
	}
private:
	map<CString, ID2D1Bitmap*> mBitmapMap;

	// 1키 : 파일 이름 / 2키 : 모션 이름 / 3 : sprite Datas
	map<CString, map<CString, vector<Sprite>>> mSpriteDataMap;

public:

	bool LoadImageFile(CString uri);
	void LoadSpriteData(CString uri);

	Sprite* GetAniData(int frm, CString uri, int width, int height);

	void LoadImagefromData();

	ID2D1Bitmap* GetSpriteByPath(CString path);

	//데이터 로드
};

