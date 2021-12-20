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
	//���� �Լ� ������	
	virtual void Draw() override;// �׷��ִ°�
	virtual void Start() override;
	virtual void Update() override;

	// �� ���
	void SetColor(D2D1::ColorF  color);

	// �簢 ���� ��������
	D2D1_RECT_F GetRect();

	// ���콺 ��ǥ üũ
	bool OnMousePointerUpdate(POINT mousepos);

	// ���콺 Ŭ�� �����
	bool OnButtonClicked();

	// ���γʺ� ������
	int GetWidth();
	// ���α��� ������
	int GetHeight();

	// ���α��� ���
	void SetWidth(int width);
	// ���α��� ���
	void SetHeight(int height);

	void SetTextObject(TextObject* text);
	TextObject* GetTextObject();

	// ���� ���� ���� �ʱ�ȭ
	void Init(int width, int height, Vector2 pos);

	// ��ư�̹����̸� ���
	void SetImgName(CString name);
};

