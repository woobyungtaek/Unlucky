#pragma once


class GameProcess
{
public:
	GameProcess() : mCurrentType(ESceneType::TitleStart) {};
	~GameProcess() {};

public:
	void Init();
	void Update();

private:
	ESceneType mCurrentType;
	
	map<CString, SceneObject*> mGameScene;

	Player* mpPlayer;

private:
	void (GameProcess::*SceneFunction[(int)ESceneType::SceneCount])(void);

	void TitleStart();
	void TitleUpdate();
	void BattleStart();
	void BattleUpdate();
	void LoadingStart();
	void LoadingUpdate();
	void LobbyStart();
	void LobbyUpdate();
	void GotchaStart();
	void GotchaUpdate();

public:
	//외부 호출 함수

};