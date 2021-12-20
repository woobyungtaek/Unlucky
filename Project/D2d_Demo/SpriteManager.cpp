#include "pch.h"

//�̹����� �ε� �մϴ�.
void SpriteManager::LoadImageFile(PCWSTR uri)
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

//��Ʈ�� (sprite sheet)�� �ε� �մϴ�.
ID2D1Bitmap* SpriteManager::GetSpriteByPath(PCWSTR path)
{
	return mBitmapMap[path];

}
/*
vector<SpriteInfo> SpriteManager::GetAnimtaionData(PCWSTR uri, int motion, int maxfrm, int width, int height, POINT pivot)
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
*/
SpriteInfo SpriteManager::GetAniData(int frm, PCWSTR uri, int motion,  int width, int height, POINT pivot)
{
		//LoadImageFile(uri);

		SpriteInfo instInfo;

		instInfo.FileName = uri;
		instInfo.Motion = motion;
		instInfo.Frame = frm;

		D2D1_RECT_F srcRect;
		srcRect.left = frm * width;
		srcRect.top = motion * height;
		srcRect.right = (frm + 1) * width;
		srcRect.bottom = (motion + 1) * height;
		instInfo.SrcRect = srcRect;

		instInfo.Pivot.x = pivot.x;
		instInfo.Pivot.y = pivot.y;

		return instInfo;
}
