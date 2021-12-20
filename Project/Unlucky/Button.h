#pragma once

typedef void (*ButtonEvent) (void);
typedef void (*Event_int) (int);

class Button : public GameObject
{
protected:

	int mWidth;
	int mHeight;
	POINT mMousePos;
	CString ButtonImgName;

	D2D1::ColorF mColor;
	bool Debug;
	TextObject* mButtonText;

public:
	Button();
	Button(int width, int height, Vector2 pos);
	Button(int width, int height);
	~Button();

	ButtonEvent DefaultEvent;
	ButtonEvent MouseOnEvent;
	ButtonEvent MouseClickEvent;

public:
	//가상 함수 재정의	
	virtual void Draw() override;// 그려주는거
	virtual void Start() override;
	virtual void Update() override;

	// 색 사용
	void SetColor(D2D1::ColorF  color);

	// 사각 영역 가져오기
	D2D1_RECT_F GetRect();

	// 마우스 좌표 체크
	bool OnMousePointerUpdate(POINT mousepos);

	// 마우스 클릭 됬는지
	bool OnButtonClicked();

	// 가로너비 얻어오기
	int GetWidth();
	// 세로길이 얻어오기
	int GetHeight();

	// 가로길이 사용
	void SetWidth(int width);
	// 세로길이 사용
	void SetHeight(int height);

	void SetTextObject(TextObject* text);
	TextObject* GetTextObject();

	// 가로 세로 중점 초기화
	void Init(int width, int height, Vector2 pos);

	// 버튼이미지이름 사용
	void SetImgName(CString name);
};

