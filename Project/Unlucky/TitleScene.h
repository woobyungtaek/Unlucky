#pragma once

class SoundManager;

class TitleScene : public SceneObject, public Singleton<TitleScene>
{
public:
	TitleScene();
	~TitleScene();

private:
	vector<Sprite*> TitleEffect;

	SoundManager* Openning_Bgm;

	int Frame;
	int ChcekFrm;
	float Alpha;
	bool AlphaTurn;

public:
	virtual void Init(POINT screenSize) override;
	virtual void Draw() override;
	virtual void Update() override;

	//버튼 이벤트 함수
	static void OnClickedTitleButton();
	static void OnMouseTitleButton();
	static void DefaultTitleButton();

	static void OnClickedGameStartButton();
	static void OnMouseGameStartButton();
	static void DefaultGameStartButton();

	static void OnClickedExitButton();
	static void OnMouseExitButton();
	static void DefaultExitButton();
};

