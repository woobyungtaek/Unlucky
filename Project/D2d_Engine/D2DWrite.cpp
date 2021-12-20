#include "pch.h"


D2DWrite::D2DWrite()
	:mTextSize(50), mpFontName(L"굴림")
{
	HRESULT hr = S_OK;


	static const PCWSTR msc_fontName = mpFontName;
	static const FLOAT msc_fontSize = mTextSize;

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite factory.
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(mpDWriteFactory),
			reinterpret_cast<IUnknown**>(&mpDWriteFactory)
		);
	}

	if (SUCCEEDED(hr))
	{

		// Create a DirectWrite text format object.
		hr = mpDWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"", //locale
			&mpTextFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}


	SetBrushColor(RGB(255, 0, 255));
}

D2DWrite::~D2DWrite()
{

}

void D2DWrite::SetBrushColor(COLORREF color)
{
	D2dCore::GetInstance()->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(color), &mpTextBrush);
}

void D2DWrite::SetTextFont(PCWSTR fontname)
{
	mpFontName = fontname;
	HRESULT hr = S_OK;

	SafeRelease(&mpTextFormat);

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mpDWriteFactory->CreateTextFormat(
			mpFontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			mTextSize,
			L"", //locale
			&mpTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}
}

void D2DWrite::SetTextSize(int size)
{
	mTextSize = size;
	HRESULT hr = S_OK;

	SafeRelease(&mpTextFormat);

	if (SUCCEEDED(hr))
	{
		// Create a DirectWrite text format object.
		hr = mpDWriteFactory->CreateTextFormat(
			mpFontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			mTextSize,
			L"", //locale
			&mpTextFormat
		);
	}

	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		mpTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		mpTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	}
}

bool D2DWrite::WriteText(int x, int y, const char* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	 buffer = new char[len];

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer,  strlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		D2dCore::GetInstance()->GetRenderTarget()->DrawText(unicodestr, wcslen(unicodestr), mpTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
			mpTextBrush);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

bool D2DWrite::WriteTextByRect(D2D1_RECT_F rect, const char* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		D2dCore::GetInstance()->GetRenderTarget()->DrawText(unicodestr, wcslen(unicodestr), mpTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			rect,
			mpTextBrush);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;

	return true;
}

bool D2DWrite::WriteTextLayout(Vector2 pos, Vector2 size, const wchar_t* pch, ...)
{
	
	HRESULT hr = S_OK;

	// 포맷 스트링 관련 버퍼, 가변인자 처리
	wchar_t* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscwprintf(pch, ap) + 1;
	buffer = new wchar_t[len];

	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);


	int nLen = lstrlenW(pch);
	//int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
	float width = size.x;
	float height = size.y;

	int posX = pos.x - width / 2;
	int posY = pos.y - height / 2;

	if (SUCCEEDED(hr))
	{
		//RECT rect;
		//GetClientRect(D2dCore::GetInstance()->GetHwnd(), &rect);
		

		hr = mpDWriteFactory->CreateTextLayout(
			pch,      // The string to be laid out and formatted.
			nLen,  // The length of the string.
			mpTextFormat,  // The text format to apply to the string (contains font information, etc).
			width,         // The width of the layout box.
			height,        // The height of the layout box.
			&mpTextLayout  // The IDWriteTextLayout interface pointer.
		);
		mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	//::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		//mpTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		// 폰트별 차지하는 영역 계산 필요
		D2dCore::GetInstance()->GetRenderTarget()->DrawTextLayout
		(
			D2D1::Point2F(posX, posY + (height/2) - ((float)mTextSize / 2.0)),
			mpTextLayout,
			mpTextBrush,
			D2D1_DRAW_TEXT_OPTIONS_NONE
		);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
	
	return true;
	
}