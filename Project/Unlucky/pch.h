// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#endif

#if _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.


#include <iostream>
#include <ctime>
#include <windows.h>
#include <stdio.h>
//#include< wchar.h >
#include <functional>
#include <atlstr.h>
#include <string>
#include <tchar.h>
#include <vector>
#include <map>
#include <d2d1.h>
#include <assert.h>

#include <d2d1helper.h> //ColorF

#include "Enums.h"

#include "Singleton.h"

#include "D2DDefine.h"
#include "D2dEngine.h"

#include "CustomArgs.h"
#include "Weapon.h"


#include "BattleObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SkillBook.h"
#include "EnemyParty.h"


#include "TextObject.h"
#include "ImageObject.h"
#include "HPBar.h"
#include "UnLuckyStackBar.h"
#include "Button.h"
#include "WeaponButton.h"
#include "WeaponInfoUI.h"
#include "WeaponListUI.h"
#include "IWeaponList.h"


#include "SceneObject.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "BattleScene.h"
#include "GotchaScene.h"
#include "LoadingScene.h"

#include "BattleManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "StageManager.h"
#include "WeaponManager.h"
#include "EnemyManager.h"

#include "ResultPopUp.h"

#pragma comment(lib, "d2d1")

using namespace std;
using namespace D2dEngine;

#endif //PCH_H
