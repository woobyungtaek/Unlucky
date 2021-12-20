#pragma once
class ResultPopUp : public GameObject
{
public:
	ResultPopUp(Vector2 pos);
	~ResultPopUp();

private:
	vector<Weapon*> mWeaponVec;
	POINT mScreenSize;
	vector<Button*> mButtonList;

public:
	void SetWeapon(Weapon* weapon);
	void ReseWeaponVec();

	void Init(POINT screenSize);
	virtual void Start() override;
	virtual void Draw() override;
	virtual void Update() override;

	// ���⺸�� Ƽ�� ��ư
	static void OnClickedWeaponButton();
	static void OnMouseWeaponButton();
	static void DefaultWeaponButton();

	// ���â â���� ��ư
	static void OnClickedCloseButton();
	static void OnMouseCloseButton();
	static void DefaultButton();
};

