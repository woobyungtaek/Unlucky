// pch.h: �̸� �����ϵ� ��� �����Դϴ�.
// �Ʒ� ������ ������ �� ���� �����ϵǾ�����, ���� ���忡 ���� ���� ������ ����մϴ�.
// �ڵ� ������ �� ���� �ڵ� �˻� ����� �����Ͽ� IntelliSense ���ɿ��� ������ ��Ĩ�ϴ�.
// �׷��� ���⿡ ������ ������ ���� �� ������Ʈ�Ǵ� ��� ��� �ٽ� �����ϵ˴ϴ�.
// ���⿡ ���� ������Ʈ�� ������ �߰����� ������. �׷��� ������ ���ϵ˴ϴ�.

#ifndef PCH_H
#define PCH_H

// ���⿡ �̸� �������Ϸ��� ��� �߰�

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
