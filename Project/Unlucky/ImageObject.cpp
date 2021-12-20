#include "pch.h"

ImageObject::ImageObject()
{
	IsActive = true;
	SetScale(Vector3(1,1,1));
}

ImageObject::~ImageObject()
{
}

void ImageObject::SetImageName(CString name)
{
	mImageName = name;
	mBitMap = SpriteManager::GetInstance()->GetSpriteByPath(mImageName);
}

void ImageObject::Draw()
{
	if (!IsActive) { return; }
	if (mBitMap == nullptr) { return; }

	Vector2 pos = Vector2(GetPosition().x, GetPosition().y);

	//Scale값을 곱해서 출력 합니다.
	DrawImageByPivot(mBitMap, pos, mBitMap->GetSize().width * GetScale().x, mBitMap->GetSize().height* GetScale().y);
}

void ImageObject::Start()
{
}

void ImageObject::Update()
{
}
