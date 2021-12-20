#include "pch.h"


void Input::KeyUpdate()
{
	for (int index = 0; index < 255; index++)
	{
		mKeyStateArr[index].prev = mKeyStateArr[index].current;
		mKeyStateArr[index].current = HIWORD(GetAsyncKeyState(index));
	}
}

// 확인 하고 싶은 키가 눌려져 있는거
bool Input::InputKey(int vk)
{
	return mKeyStateArr[vk].current;
}

// 키가 눌린 것을 확인하고 싶을때
bool Input::InputKeyDown(int vk)
{
	return !mKeyStateArr[vk].prev && mKeyStateArr[vk].current;
}

// 키가 올라간 것을 확인하고 싶을때 
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