#pragma once
class TextObject : public GameObject
{
public:
	TextObject();
	TextObject(CString str, int size, COLORREF color);
	~TextObject();

private:
	D2D1_RECT_F mRect;

	CString mStr;
	int mSize;
	COLORREF mColor;

public:
	void Init(CString str, int size, COLORREF color);
	void SetRect(D2D1_RECT_F rect);

	//가상 함수 재정의	
	virtual void Draw() override;
	virtual void Start() override;
	virtual void Update() override;
};

