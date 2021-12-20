#include "pch.h"
#include "CircleObject.h"

void CircleObject::SetRadius(int radius)
{
	mRadius = radius;
}

int CircleObject::GetRadius()
{
	return mRadius;
}

void CircleObject::Draw()
{
//	DrawEilpse((int)this->GetPos()->x, (int)this->GetPos()->y, mRadius, RGB(255, 0, 255));
}

void CircleObject::Draw(COLORREF color)
{
	//DrawEilpse((int)this->GetPos()->x, (int)this->GetPos()->y, mRadius, color);
}
