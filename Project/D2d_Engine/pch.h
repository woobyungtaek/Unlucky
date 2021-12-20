// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가

#include <stdio.h>
#include <cmath>
#include <string>
#include <cstdlib>
#include <vector>
#include <map>
#include <windowsx.h>
#include <windows.h>
#include <assert.h>

#include <d2d1.h>
#include <d2d1_1.h>
#include "d2d1helper.h"						// ColorF
#include <dwrite.h>							// writefactory
#include <wincodec.h>						// WIC

// #include <d3d11.h>		// D3D11
// #include <dxgi1_2.h>		// DXGI
// #include "d2d1effects_2.h"		// Effect

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")			// writefactory
#pragma comment(lib, "windowscodecs.lib")	// WIC

//  #pragma comment(lib, "d3d11.lib")			// D3D11
//  #pragma comment(lib, "dxguid.lib")			// DXGI

#include "Singleton.h";

#include "Input.h"

#include "TimeController.h"

#include "D2dCore.h"
#include "D2DDefine.h"
#include "D2DGDI.h"
#include "D2DBitmap.h"
#include "D2DWrite.h"

#include "D2dEngine.h"

using namespace D2dEngine;

#endif //PCH_H
