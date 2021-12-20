#pragma once
class UnLuckyStackBar : public GameObject
{
public : 
	UnLuckyStackBar(Vector2 pos);
	~UnLuckyStackBar();

private:
	Weapon* mWeapon;

	BattleObject* mBattleObject;
	Player* mPlayer;

public:
	void SetBattleObject(BattleObject* battleObject);

	virtual void Start() override;
	virtual void Draw() override;
	virtual void Update() override;
};

