#pragma once
class ImageObject :  public GameObject
{

public:
	ImageObject();
	~ImageObject();

private:
	CString mImageName;
	ID2D1Bitmap* mBitMap;

public:
	void SetImageName(CString name);

	virtual void Draw()override;
	virtual void Start() override;
	virtual void Update() override;
};

