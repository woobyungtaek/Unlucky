#pragma once
class WeaponInfoUI : public GameObject
{
public:
	WeaponInfoUI();
	~WeaponInfoUI();

private:
	Weapon* mWeapon;

public:
	void SetWeapon(Weapon* weapon);

	virtual void Start() override;
	virtual void Draw() override;
	virtual void Update() override;
};

