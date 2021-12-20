#include "pch.h"


void Input::KeyUpdate()
{
	for (int index = 0; index < 255; index++)
	{
		mKeyStateArr[index].prev = mKeyStateArr[index].current;
		mKeyStateArr[index].current = HIWORD(GetAsyncKeyState(index));
	}
}

// Ȯ�� �ϰ� ���� Ű�� ������ �ִ°�
bool Input::InputKey(int vk)
{
	return mKeyStateArr[vk].current;
}

// Ű�� ���� ���� Ȯ���ϰ� ������
bool Input::InputKeyDown(int vk)
{
	return !mKeyStateArr[vk].prev && mKeyStateArr[vk].current;
}

// Ű�� �ö� ���� Ȯ���ϰ� ������ 
bool Input::InputKeyUp(int vk)
{
	return mKeyStateArr[vk].prev && !mKeyStateArr[vk].current;
}

POINT Input::GetMousePosCT()
{
	MousePosClient = MousePosScreen;
	ScreenToClient(D2dCore::GetInstance()->GetHwnd(), &MousePosClient);
	return MousePosClient;
}

POINT Input::GetMousePosSC()
{
	return MousePosScreen;
}

void Input::MouseUpdate()
{
	GetCursorPos(&MousePosScreen);
}