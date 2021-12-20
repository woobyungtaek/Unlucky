#include "pch.h"

HPBar::HPBar(Vector2 pos)
{
	SetPosition(pos);
}

HPBar::~HPBar()
{
}

void HPBar::SetBattleObject(BattleObject* battleObject)
{
	mBattleObject = battleObject;
}

void HPBar::Start()
{
	if (!IsActive) { return; }
}

void HPBar::Draw()
{
	if (!IsActive) { return; }

	D2D1_POINT_2F mScreenSize =  D2D1::Point2F(2560, 1440);

	//현재 배틀 오브젝트에 대한 것만 그려야 한다 1개만
	Vector3 pos = GetPosition();

	// 아래 체력바 그리기
	DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\hp_gauge_bar_0.png")),
		D2D1::RectF(
			pos.x, 
			pos.y,
			pos.x + (mScreenSize.x * 410.f / mScreenSize.x),
			pos.y + (mScreenSize.y * 60.f / mScreenSize.y)),
		D2D1::RectF(410, 0, 820, 60));

	float hp = 50;
	if (mBattleObject != nullptr)
	{
		hp = 360 - (310 * ((float)mBattleObject->HP / (float)mBattleObject->MaxHP));
	}

	// 위 체력바 그리기
	DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\hp_gauge_bar_0.png")),
		D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + (mScreenSize.x * (410.f) / mScreenSize.x) - hp,
			pos.y + (mScreenSize.y * 60.f / mScreenSize.y)),
		D2D1::RectF(0, 0,  410  - hp, 60));
}

void HPBar::Update()
{
	if (!IsActive) { return; }
}
