#pragma once

class SoundManager;
class LobbyScene : public SceneObject, public Singleton<LobbyScene>
{
public:
	LobbyScene();
	~LobbyScene();

private:

	WeaponListUI* mWeaponListUI;
	SoundManager* Stage_Select_Bgm;

public:
	virtual void Init(POINT screenSize) override;
	virtual void Draw() override;
	virtual void Update() override;


	// 버튼 이벤트 함수
	static void SelectStage(int index);

	// 왼쪽영웅선택
	static void OnClickedLeftButton();
	static void OnMouseLeftButton();
	static void DefaultLeftButton();
	// 가운데영웅선택
	static void OnClickedMiddleButton();
	static void OnMouseMiddleButton();
	static void DefaultMiddleButton();
	// 오른쪽영웅선택
	static void OnClickedRightButton();
	static void OnMouseRightButton();
	static void DefaultRightButton();
	// 무기보급박스 버튼
	static void OnClickedWeaponBoxButton();
	static void OnMouseWeaponBoxButton();
	static void DefaultWeaponBoxButton();
};

