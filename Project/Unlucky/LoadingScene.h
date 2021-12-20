#pragma once
class SoundManager;

class LoadingScene :public SceneObject, public Singleton<LoadingScene>
{
public:

	LoadingScene();
	~LoadingScene();
private:
	vector<Sprite*> Opening;

	SoundManager* Open_Book_SFX;

	int Frame;
	int ChcekFrm;
public:
	virtual void Init(POINT screenSize) override;
	virtual void Draw() override;
	virtual void Update() override;
};

