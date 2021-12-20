#pragma once


class KeyState 
{
public:
	KeyState() : current(false), prev(false) {};
	~KeyState() {};

public:
	bool current;
	bool prev;
};

class Input :public Singleton<Input>
{

private:
	 KeyState mKeyStateArr[256];
	 POINT MousePosScreen;
	 POINT MousePosClient;

public:
	 void KeyUpdate();
	 bool InputKey(int vk);
	 bool InputKeyDown(int vk);
	 bool InputKeyUp(int vk);
	 POINT GetMousePosCT();
	 POINT GetMousePosSC();
	 void MouseUpdate();
};

