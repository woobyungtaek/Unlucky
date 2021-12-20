#include "pch.h"

TextObject::TextObject()
{
	mStr = L"";
	mSize = 10;
	mColor = D2D1::ColorF::Black;
}

TextObject::TextObject(CString str, int size, COLORREF color)
	:mStr(str),mSize(size),mColor(color)
{
}

TextObject::~TextObject()
{
}

void TextObject::Init(CString str, int size, COLORREF color)
{
	mStr = str;
	mSize = size;
	mColor = color;
}

void TextObject::SetRect(D2D1_RECT_F rect)
{
	mRect = rect;
}

void TextObject::Draw()
{
	if (!IsActive) { return; }

	Vector2 size = Vector2(mRect.right - mRect.left, mRect.bottom - mRect.top);
	Vector2 pivot = Vector2(mRect.left, mRect.top) + size / 2;

	WriteTextLayout( 
		pivot,
		size,
		mSize, 
		mColor,
		(const wchar_t*)mStr);
}

void TextObject::Start()
{
}

void TextObject::Update()
{
}
