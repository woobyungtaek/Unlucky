#pragma once
class CircleObject: public GameObject
{
private:
	int mRadius;
public:
	CircleObject(int radius)
	:mRadius(radius)
	{

	};
	~CircleObject()
	{
	};

public:
	void SetRadius(int radius);
	int GetRadius();
	void Draw();
	void Draw(COLORREF color);
};

