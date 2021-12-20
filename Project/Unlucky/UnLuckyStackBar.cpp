#include "pch.h"

UnLuckyStackBar::UnLuckyStackBar(Vector2 pos)
{
	SetPosition(pos);
}

UnLuckyStackBar::~UnLuckyStackBar()
{
}

void UnLuckyStackBar::SetBattleObject(BattleObject* battleObject)
{
	mBattleObject = battleObject;
	mPlayer = reinterpret_cast<Player*>(mBattleObject);
}

void UnLuckyStackBar::Start()
{
	if (!IsActive) { return; }
}

void UnLuckyStackBar::Draw()
{
	if (!IsActive) { return; }

	D2D1_POINT_2F mScreenSize = D2D1::Point2F(2560, 1440);
	mScreenSize.x = GetSystemMetrics(SM_CXSCREEN);
	mScreenSize.y = GetSystemMetrics(SM_CYSCREEN);

	//현재 배틀 오브젝트에 대한 것만 그려야 한다 1개만
	Vector3 pos = GetPosition();

	// 아래 체력바 그리기
	DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\badluck_gauge_01.png")),
		D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + (mScreenSize.x * (410.f) / mScreenSize.x),
			pos.y + (mScreenSize.y * 60.f / mScreenSize.y)),
		D2D1::RectF(0, 0, 410, 60));

	/// 불운스택 게이지 변화 몰라..무서워...수정해죠....
	float unluckystack = 50;
	if (mPlayer != nullptr)
	{
		unluckystack = 360 - (310 * ((float)mPlayer->UnLuckStack / 4));
	}

	// 위 체력바 그리기
	DrawSprite(SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\badluck_gauge_01.png")),
		D2D1::RectF(
			pos.x,
			pos.y,
			pos.x + (mScreenSize.x * 410.f / mScreenSize.x) - unluckystack,
			pos.y + (mScreenSize.y * 60.f / mScreenSize.y)),
		D2D1::RectF(410, 0, 820 - unluckystack, 60));

}

void UnLuckyStackBar::Update()
{
	if (!IsActive) { return; }
}
