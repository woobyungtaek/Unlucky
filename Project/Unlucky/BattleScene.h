#pragma once
class ResultPopUp;

class BattleScene : public SceneObject, public Singleton<BattleScene>
{
public:
	BattleScene();
	~BattleScene();

private:
	WeaponListUI* mWeaponListUI;

public:
	virtual void Init(POINT screenSize) override;
	virtual void Draw() override;
	virtual void Update() override;

	// ��ư �̺�Ʈ �Լ�
	static void OnClickedTurnEndButton();
	static void OnMouseTurnEndButton();
	static void DefaultTurnEndButton();
};

