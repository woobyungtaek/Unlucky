#include "pch.h"

WeaponButton::WeaponButton()
{
	mpWeapon = nullptr;

	ButtonImgName = _T("..\\Data\\UI\\weapon_image_0.png");
}

WeaponButton::~WeaponButton()
{
}

void WeaponButton::Draw()
{
	Button::Draw();
	if (!IsActive) { return; }
	D2D1_RECT_F rect = GetRect();
	DrawRect(rect.left, rect.top, rect.right, rect.bottom, D2D1::ColorF::Yellow);

	if (mpWeapon != nullptr)
	{
		//mWeapon의 그림을 불러와 그려야 한드아~!
		CString str;
		str.Format(L"..\\Data\\Weapon\\%s", mpWeapon->FileName);

		ID2D1Bitmap* pBitmap =
			SpriteManager::GetInstance()->GetSpriteByPath(str);

		if (pBitmap != nullptr)
		{
			DrawImage(pBitmap,
				D2D1::RectF(
					GetPosition().x - (pBitmap->GetSize().width * 0.075),
					GetPosition().y - (pBitmap->GetSize().height * 0.075),
					GetPosition().x + (pBitmap->GetSize().width * 0.075),
					GetPosition().y + (pBitmap->GetSize().height * 0.075)));
		}

	}
}

void WeaponButton::SetWeapon(Weapon* weapon)
{
	mpWeapon = weapon;
}

Weapon* WeaponButton::GetWeapon()
{
	return mpWeapon;
}
