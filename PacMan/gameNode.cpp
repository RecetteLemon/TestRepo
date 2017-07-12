#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SOUNDMANAGER->init();
		SCENEMANAGER->init();
		KEYANIMANAGER->init();
		TXTDATA->init();
		
		INIDATA->init();
	}

	return S_OK;
}

void gameNode::release(void)
{
	if (_managerInit)
	{
	
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		KEYANIMANAGER->releaseSingleton();
		TXTDATA->releaseSingleton();
		
		INIDATA->releaseSingleton();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(void)
{

}

void gameNode::setMap(void)
{

}

void gameNode::save(void)  
{

}

void gameNode::load(void)  
{

}



LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
		case WM_CREATE:
		break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);

			this->render();

			EndPaint(hWnd, &ps);
		break;
		//마우스 좌표를 읽어오는 함수
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>LOWORD(lParam);
			_ptMouse.y = static_cast<float>HIWORD(lParam);

			//마우스를 누르고 지형을 그릴때 갱신이 되게끔
			if (_leftButtonDown) this->setMap();
			
		break;
		case WM_LBUTTONDOWN:
			_leftButtonDown = true;
			this->setMap();
		break;
		case WM_LBUTTONUP:
			_leftButtonDown = false;
		break;
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case CTRL_SAVE:
					this->save();
				break;
				case CTRL_LOAD:
					this->load();
					InvalidateRect(hWnd, NULL, false);
				break;
				default:
					this->setCtrlSelect(LOWORD(wParam));
				break;
			}
		}
		break;
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					PostMessage(hWnd, WM_DESTROY, 0, 0);
				break;
			
			}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}