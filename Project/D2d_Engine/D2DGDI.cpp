#include "pch.h"


D2DGDI::D2DGDI() : mpBrush(nullptr)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		D2dCore::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &mpBrush);
	}
}

D2DGDI::~D2DGDI()
{
	SafeRelease(&mpBrush);
}

void D2DGDI::SetBrushColor(COLORREF color)
{
	SafeRelease(&mpBrush);
	D2dCore::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color), &mpBrush);
}

void D2DGDI::DrawLine1(int x1, int y1, int x2, int y2, int size, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->DrawLine(
				D2D1::Point2F(x1, y1),
				D2D1::Point2F(x2, y2),
				mpBrush,
				size);
		}

	}
}

void D2DGDI::DrawFillRect(int left, int top, int right, int bottom, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{

		//mpRenderTarget->CreateSolidColorBrush((D2D1::ColorF(color)), &mpBrush);

		SetBrushColor(color);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->FillRectangle(D2D1::RectF(left, top, right, bottom), mpBrush);
		}


	}
}

void D2DGDI::DrawRect(int left, int top, int right, int bottom, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		SetBrushColor(color);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->DrawRectangle(D2D1::RectF(left, top, right, bottom), mpBrush);
		}
	}
}

void D2DGDI::DrawRectByRect(D2D1_RECT_F worldRect, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		SetBrushColor(color);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->DrawRectangle(worldRect, mpBrush);
		}
	}
}

void D2DGDI::DrawTwotoneRect(int left, int top, int right, int bottom, COLORREF outcolor, COLORREF incolor)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		SetBrushColor(outcolor);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->DrawRectangle(D2D1::RectF(left, top, right, bottom), mpBrush);
		}

		SetBrushColor(incolor);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->FillRectangle(D2D1::RectF(left, top, right, bottom - 1), mpBrush);
		}
	}
}

void D2DGDI::DrawFillEilpse(int posx, int posy, int radius, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		SetBrushColor(color);

		if (mpBrush != nullptr)
		{
			D2dCore::GetInstance()->GetRenderTarget()->FillEllipse(D2D1::Ellipse(D2D1::Point2F(posx, posy), radius, radius), mpBrush);
		}

	}
}

void D2DGDI::DrawEilpse(int posx, int posy, int radius, COLORREF color)
{
	if (SUCCEEDED(D2dCore::GetInstance()->GetHresult()))
	{
		SetBrushColor(color);

		if (mpBrush != nullptr)
		{
	D2dCore::GetInstance()->GetRenderTarget()->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(posx, posy), radius, radius),mpBrush);
		}

	}
}
