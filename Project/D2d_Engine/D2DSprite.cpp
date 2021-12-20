#include "pch.h"

D2DSprite* D2DSprite::mInstance;

D2DSprite::D2DSprite()
{

}

D2DSprite::~D2DSprite()
{

}

void D2DSprite::LoadImageFile(PCWSTR uri)
{
	//��θ� Ű������ ����ϴ� ��
	ID2D1Bitmap* instBitmap = mBitmapMap[uri];
	if (instBitmap == nullptr)
	{
		//��Ʈ���� ���ٸ� ���� �߰��մϴ�.
		ID2D1Bitmap* bitMap;
		mBitmapMap.emplace(uri, bitMap);
	}

	//���� �Լ��� �̿��� ��Ʈ���� �ε� �Ѵ�.
	LoadIamge(uri, &mBitmapMap[uri]);
}

ID2D1Bitmap* D2DSprite::GetSpriteByPath(PCWSTR path)
{
	return mBitmapMap[path];
}

vector<SpriteInfo> D2DSprite::GetAnimtaionData(PCWSTR uri, int motion, int maxfrm, int width, int height, POINT pivot)
{

	LoadImageFile(uri);
	vector<SpriteInfo> Animation;

	for (int index = 0; index < maxfrm; index++)
	{
		SpriteInfo instInfo;

		instInfo.FileName = uri;
		instInfo.Motion = motion;
		instInfo.Frame = index;

		D2D1_RECT_F srcRect;
		srcRect.left = index * width;
		srcRect.top = 0 + (height * 4);
		srcRect.right = (index + 1) * width;
		srcRect.bottom = height + (height * motion);
		instInfo.SrcRect = srcRect;

		instInfo.Pivot.x = pivot.x;
		instInfo.Pivot.y = pivot.y;

		Animation.push_back(instInfo);
	}
	return Animation;
}

