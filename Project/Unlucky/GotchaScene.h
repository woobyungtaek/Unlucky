#pragma once


class GotchaScene :public SceneObject, public Singleton<GotchaScene>
{
public:
	GotchaScene();
	~GotchaScene();

public:
	Weapon* CurrentWeapon;

private:
	vector<Sprite*> GotchaEffect;
	vector<Sprite*> NomalEffect;
	vector<Sprite*>	RareEffect;
	vector<Sprite*> EpicEffect;

	int Frame;
	int ChcekFrm;
	CString FileName;
	ID2D1Bitmap* WeaponImage;
	EWeaponGrade Grade;
public:
	virtual void Init(POINT screenSize) override;
	virtual void Draw() override;
	virtual void Update() override;

};

