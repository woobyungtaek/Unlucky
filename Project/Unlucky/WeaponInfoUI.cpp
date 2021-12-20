#include "pch.h"

WeaponInfoUI::WeaponInfoUI()
{
}

WeaponInfoUI::~WeaponInfoUI()
{
}

void WeaponInfoUI::SetWeapon(Weapon* weapon)
{
	if (weapon == nullptr)
	{
		IsActive = false;
		return;
	}

	mWeapon = weapon;
	IsActive = true;
}

void WeaponInfoUI::Start()
{
	if (!IsActive) { return; }
}

void WeaponInfoUI::Draw()
{
	if (!IsActive) { return; }

	Vector2 size;
	Vector2 pivot;

	// ���⼳��UI���
	ID2D1Bitmap* pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_information_window_0.png"));
	DrawImageByPivot(pBitmap, Vector2(GetPosition().x, GetPosition().y), pBitmap->GetSize().width, pBitmap->GetSize().height);

	// �����̸�
	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_name_box_0.png"));
	pivot = Vector2(GetPosition().x - 234, GetPosition().y - 50);
	size = Vector2(pBitmap->GetSize().width, pBitmap->GetSize().height);
	DrawImageByPivot(pBitmap, pivot, size.x, size.y);
	
	WriteTextLayout(pivot, size, 15, RGB(255, 255, 255), mWeapon->Name);

	// ���� �ı� ������
	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_destory_damage_0.png"));
	pivot = Vector2(GetPosition().x - 234, GetPosition().y + 27);
	size = Vector2(pBitmap->GetSize().width, pBitmap->GetSize().height);
	DrawImageByPivot(pBitmap, pivot, size.x, size.y);

	wchar_t str[256];

	swprintf_s(str, _T("�ı�Ȯ�� : %d��"), ((int)mWeapon->BrokenRate));

	WriteTextLayout(pivot, size, 15, RGB(255, 255, 255), str);

	pivot = Vector2(GetPosition().x - 234, GetPosition().y + 87);
	size = Vector2(pBitmap->GetSize().width, pBitmap->GetSize().height);
	DrawImageByPivot(pBitmap, pivot, size.x, size.y);

	//wchar_t str[256];
	swprintf_s(str, _T("������ : %d"), (int)mWeapon->AttackPow);

	//wprintf_s(str,"%d",(int)mWeapon->AttackPow);
	WriteTextLayout(pivot, size, 15, RGB(255, 255, 255), str);


	// ���������
	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_information.png"));
	pivot = Vector2(GetPosition().x + 122, GetPosition().y - 50);
	size = Vector2(pBitmap->GetSize().width, pBitmap->GetSize().height);
	DrawImageByPivot(pBitmap, pivot, size.x, size.y);
	WriteTextLayout(pivot, size, 15, RGB(255, 255, 255), mWeapon->Desc);


	// ���� ��ų����
	//pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\trun_0.png"));
	pBitmap = SpriteManager::GetInstance()->GetSpriteByPath(_T("..\\Data\\UI\\weapon_skill_infomation_0.png"));
	pivot = Vector2(GetPosition().x + 122, GetPosition().y + 65);
	size = Vector2(pBitmap->GetSize().width, pBitmap->GetSize().height);
	DrawImageByPivot(pBitmap, pivot, size.x, size.y);
	WriteTextLayout(pivot, size, 15, RGB(255, 255, 255), mWeapon->SkillDesc);
}

void WeaponInfoUI::Update()
{
	if (!IsActive) { return; }
}
