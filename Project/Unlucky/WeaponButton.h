#pragma once
class WeaponButton : public Button
{
public:
	WeaponButton();
	~WeaponButton();
	
private:
	Weapon* mpWeapon;

public:
	//���� �Լ� ������	
	virtual void Draw() override;

	void SetWeapon(Weapon* weapon);
	Weapon* GetWeapon();
};