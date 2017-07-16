#pragma once

// D2D 사용을 위한 lib
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "WindowsCodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Comdlg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <cassert>
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <iostream>
#include <tchar.h>

// D2D Header Files
#include <d2d1_1.h>
#include <d2d1_1helper.h>
/*
<d2d1.h> 헤더파일 안에는 이하 언급한 헤더파일이 포함되있다.

*===============================================================================
* <d2d1helper.h>			(c++에서 유용한 함수, 클래스, 구조체 정의)
* <d2dbasetypes.h>		(점, 선 또는 사각형 같은 기본적인 그리기에 대한 정보)
* <d2derr.h>				(Direct2D API 에서 사용하는 에러코드에 대하여 정의)
*
* 윈도우 8이상이면
* d2d1.h -> d2d1_1h
* d2d1_helper.h -> d2d1_1helper.h 로 써도 된다. 윈도우 7미만이면 호환이 되지 않는다.
* 
*===============================================================================

<d2d1effects.h>			(이미지 효과와 관련된 것들, windows 8 이후 버전)
<d2d1effecthelpers.h>	(이미지 효과를 편리하게 사용하기 위한 함수, 구조체 등)


*/
#include <wincodec.h>
#include <dwrite.h>


// 기타 헤더 파일
#include "commonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "TimeManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "utils.h"
#include "collision.h"
#include "TxtData.h"
//#include "Database.h"
#include "D2DManager.h"
#include "Camera.h"


using namespace std;
using namespace LIMA_UTIL;
using namespace D2D1;


//==================================================
// - 2015. 10. 16 ## 디파인문 ## 
//==================================================

#define WINNAME (LPTSTR)(TEXT("Lima Team"))
#define WINSTARTX (1920-1600) *0.5//-1920 + (1920-1600) *0.5		
#define WINSTARTY 50			
#define WINSIZEX 1600
#define WINSIZEY 900
#define MAPSIZEX 2200
#define MAPSIZEY 1800 
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define SAFE_DELETE(p)			{if(p) { delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) { delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->Release(); (p) = nullptr;}}

#define RND RandomFunction::GetSingleton()
#define KEYMANAGER KeyManager::GetSingleton()
#define IMAGEMANAGER ImageManager::GetSingleton()
#define TIMEMANAGER TimeManager::GetSingleton()
#define SOUNDMANAGER SoundManager::GetSingleton()
#define SCENEMANAGER SceneManager::GetSingleton()
#define TXTDATA TxtData::GetSingleton()
//#define DATABASE Database::Getsingleton()
#define D2DMANAGER D2DManager::GetSingleton()
#define CAMERA Camera::GetSingleton()

//==============================================
// ## 2015.10.22 ## extern(전역) 선언
//==============================================

extern HINSTANCE g_hInstance;
extern HWND g_hWnd;
extern POINT g_ptMouse;
extern float g_SpeedRatio;