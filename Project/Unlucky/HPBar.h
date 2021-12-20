#pragma once
class HPBar : public GameObject
{
public:
	HPBar(Vector2 pos);
	~HPBar();

private:
	Weapon* mWeapon;

	BattleObject* mBattleObject;

public:
	void SetBattleObject(BattleObject* battleObject);

	virtual void Start() override;
	virtual void Draw() override;
	virtual void Update() override;
};

