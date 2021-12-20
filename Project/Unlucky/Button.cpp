#include "pch.h"
//#include "Button.h"

Button::Button()
	: mWidth(0), mHeight(0), mColor(D2D1::ColorF::Red), Debug(false)
{
}

Button::Button(int width, int height, Vector2 pos)
	: mColor(D2D1::ColorF::Red)
{
	mWidth = width;
	mHeight = height;

	SetPosition(pos);
}

Button::Button(int width, int height)
	:mColor(D2D1::ColorF::Red)
{
	mWidth = width;
	mHeight = height;

	Vector2 pos(0, 0);

	SetPosition(pos);
}

Button::~Button()
{
}

void Button::Draw()
{
	if (!IsActive) { return; }                            
	D2D1_RECT_F rect = GetRect();

	if (Debug)
	{
		DrawRect(rect.left, rect.top, rect.right, rect.bottom, D2D1::ColorF::Yellow);
	}
	
	if (ButtonImgName != _T(""))
	{
		DrawImage(SpriteManager::GetInstance()->GetSpriteByPath(ButtonImgName), 
			D2D1::RectF(GetPosition().x -SpriteManager::GetInstance()->GetSpriteByPath(ButtonImgName)->GetSize().width/2,
				GetPosition().y - SpriteManager::GetInstance()->GetSpriteByPath(ButtonImgName)->GetSize().height / 2,
				GetPosition().x + SpriteManager::GetInstance()->GetSpriteByPath(ButtonImgName)->GetSize().width / 2,
				GetPosition().y + SpriteManager::GetInstance()->GetSpriteByPath(ButtonImgName)->GetSize().height / 2)
			);
	}

	if (mButtonText != nullptr)
	{
		if (!mButtonText->IsActive) { return; }
		mButtonText->SetRect(GetRect());
		mButtonText->Draw();
	}
}

void Button::Start()
{
}

void Button::Update()
{
	if (!IsActive) { return; }
	if (InputKeyDown(VK_F1))
	{
		if (Debug)
		{
			Debug = false;
		}
		else
		{
			Debug = true;
		}
		
	}
	bool bMouseOn = OnMousePointerUpdate(GetMousePosCT());

	if (bMouseOn)
	{
		if (MouseOnEvent != nullptr)
		{
			MouseOnEvent();
		}

		if (MouseClickEvent != nullptr)
		{
			if (InputKeyDown(VK_LBUTTON))
			{
				MouseClickEvent();
			}
		}
	}
	else
	{
		if (DefaultEvent != nullptr)
		{
			DefaultEvent();
		}
	}
}


void Button::SetColor(D2D1::ColorF color)
{
	mColor = color;
}

D2D1_RECT_F Button::GetRect()
{
	return D2D1::RectF(
		GetPosition().x - (mWidth / 2),
		GetPosition().y - (mHeight / 2),
		GetPosition().x + (mWidth / 2),
		GetPosition().y + (mHeight / 2));
}

bool Button::OnMousePointerUpdate(POINT mousepos)
{
	mMousePos = mousepos;
	D2D1_RECT_F rect = GetRect();

	if ((rect.left < mMousePos.x)
		&& (rect.right > mMousePos.x)
		&& (rect.top < mMousePos.y)
		&& (rect.bottom > mMousePos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Button::OnButtonClicked()
{
	return false;
}

int Button::GetWidth()
{
	return  mWidth;
}
int Button::GetHeight()
{
	return mHeight;
}

void Button::SetWidth(int width)
{
	mWidth = width;
}
void Button::SetHeight(int height)
{
	mHeight = height;
}

void Button::SetTextObject(TextObject* text)
{
	mButtonText = text;
	mButtonText->IsActive = true;
}
TextObject* Button::GetTextObject()
{
	return mButtonText;
}

void Button::Init(int width, int height, Vector2 pos)
{
	mWidth = width;
	mHeight = height;
	SetPosition(pos);
}

void Button::SetImgName(CString name)
{
	ButtonImgName = name;
}
