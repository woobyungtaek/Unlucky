#pragma once

class IWeaponList;
class WeaponInfoUI;

class WeaponListUI : public GameObject
{
public:
	WeaponListUI(IWeaponList* scene, int viewCount);
	~WeaponListUI(); 

private:
	static WeaponListUI* mInst;
	static Weapon* mCurrentWeapon;

	int mViewCount;

	Player* mpPlayer;
	IWeaponList* mCurrentManager;

	vector<WeaponButton*> mWeaponButtonVec;
	vector<Button*> mButtonVec;

	WeaponInfoUI* mInfoPanel;

public:
	void Init(Player* player, Vector2 pos,POINT size);

	virtual void Start()override;
	virtual void Draw()override;
	virtual void Update()override;

	void RefreshUI();

	// 왼쪽 무기스크롤버튼
	static void OnClickedLeftScrollButton();
	static void OnMouseLeftScrollButton();
	static void DefaultLeftScrollButton();

	// 오른쪽 무기스크롤 버튼
	static void OnClickedRightScrollButton();
	static void OnMouseRightScrollButton();
	static void DefaultRightScrollButton();

	static void OnClickedWeaponButton_0();
	static void OnMouseWeaponButton_0();

	static void OnClickedWeaponButton_1();
	static void OnMouseWeaponButton_1();

	static void OnClickedWeaponButton_2();
	static void OnMouseWeaponButton_2();

	static void OnClickedWeaponButton_3();
	static void OnMouseWeaponButton_3();

	static void OnClickedWeaponButton_4();
	static void OnMouseWeaponButton_4();

	static void OnClickedWeaponButton_5();
	static void OnMouseWeaponButton_5();

	static void OnClickedWeaponButton_6();
	static void OnMouseWeaponButton_6();
};
