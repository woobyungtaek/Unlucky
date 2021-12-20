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


	// ��ư �̺�Ʈ �Լ�
	static void SelectStage(int index);

	// ���ʿ�������
	static void OnClickedLeftButton();
	static void OnMouseLeftButton();
	static void DefaultLeftButton();
	// �����������
	static void OnClickedMiddleButton();
	static void OnMouseMiddleButton();
	static void DefaultMiddleButton();
	// �����ʿ�������
	static void OnClickedRightButton();
	static void OnMouseRightButton();
	static void DefaultRightButton();
	// ���⺸�޹ڽ� ��ư
	static void OnClickedWeaponBoxButton();
	static void OnMouseWeaponBoxButton();
	static void DefaultWeaponBoxButton();
};

