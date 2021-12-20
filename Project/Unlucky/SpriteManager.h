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

	// 1Ű : ���� �̸� / 2Ű : ��� �̸� / 3 : sprite Datas
	map<CString, map<CString, vector<Sprite>>> mSpriteDataMap;

public:

	bool LoadImageFile(CString uri);
	void LoadSpriteData(CString uri);

	Sprite* GetAniData(int frm, CString uri, int width, int height);

	void LoadImagefromData();

	ID2D1Bitmap* GetSpriteByPath(CString path);

	//������ �ε�
};

