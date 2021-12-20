#pragma once

//class D2dCore;

class D2DGDI : public Singleton<D2DGDI>
{
private:
	ID2D1SolidColorBrush* mpBrush;			//D2d Brush

public:
	D2DGDI();
	~D2DGDI();

public:
	void SetBrushColor(COLORREF color);
	ID2D1SolidColorBrush* GetBrush() { return mpBrush; }

	//Primitive 
	void	DrawLine1(int x1, int y1, int x2, int y2, int size, COLORREF color);

	void	DrawFillRect(int left, int top, int right, int bottom, COLORREF color);

	void	DrawRect(int left, int top, int right, int bottom, COLORREF color);
	void	DrawRectByRect(D2D1_RECT_F worldRect, COLORREF color);

	void	DrawTwotoneRect(int left, int top, int right, int bottom, COLORREF outcolor, COLORREF incolor);

	void	DrawFillEilpse(int posx, int posy, int radius, COLORREF color);
	void	DrawEilpse(int posx, int posy, int radius, COLORREF color);
};

