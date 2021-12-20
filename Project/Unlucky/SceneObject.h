#pragma once

class Button;

class SceneObject
{
public:
	SceneObject();
	~SceneObject();

public:
	//���� ���� ǥ��
	static ESceneType NextScene;

	vector<Button*> mButtonList;
	static POINT mScreenSize;

public:
	virtual void Init(POINT screenSize) = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
};