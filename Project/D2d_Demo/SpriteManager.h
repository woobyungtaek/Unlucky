#pragma once
struct SpriteInfo;

class SpriteManager :public Singleton<SpriteManager>
{
private:
	//SpriteInfo도 공통으로 로드하고 경로나, 파일 이름을 키로 가져오기
	//객체가 그림을 얻을 수 있는 방법
	//2번 큰 스프라이트를 잘라내서 매니저가 가지고 있기
	//3번 오브젝트 별로 static하게 이미지를 가지고 있기

	//파일 경로 = 키
	//값 비트맵
	std::map<PCWSTR, ID2D1Bitmap*> mBitmapMap;

public:
	//map<PCWSTR, vector<SpriteInfo*>> mSpriteInfo;
	void LoadImageFile(PCWSTR uri);

	ID2D1Bitmap* GetSpriteByPath(PCWSTR path);

	//데이터 로드
	//void LoadAllSpriteDataByFile();
	//void LoadAllBitMapByFile();


	//vector<SpriteInfo> GetAnimtaionData(PCWSTR uri, int motion, int maxfrm, int width, int height, POINT pivot);
	SpriteInfo GetAniData(int frm, PCWSTR uri, int motion, int width, int height, POINT pivot);
};

