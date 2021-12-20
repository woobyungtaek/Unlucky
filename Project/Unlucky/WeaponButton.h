#pragma once
class WeaponButton : public Button
{
public:
	WeaponButton();
	~WeaponButton();
	
private:
	Weapon* mpWeapon;

public:
	//가상 함수 재정의	
	virtual void Draw() override;

	void SetWeapon(Weapon* weapon);
	Weapon* GetWeapon();
};