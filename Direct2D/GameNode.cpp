#include "stdafx.h"
#include "GameNode.h"


GameNode::GameNode()
{
}


GameNode::~GameNode()
{
}

HRESULT GameNode::Init(void)
{
	_managerInit = false;
	
	return S_OK;
}

HRESULT GameNode::Init(bool managerInit)
{
	_managerInit = managerInit;

	g_SpeedRatio = 1.0f;

	if (_managerInit)
	{
		D2DMANAGER->Init();
		KEYMANAGER->Init();
		IMAGEMANAGER->Init();
		TIMEMANAGER->Init();
		SOUNDMANAGER->Init();
		SCENEMANAGER->Init();
		TXTDATA->Init();
		//DATABASE->Init();
		CAMERA->Init();
	}

	
	return S_OK;
}

void GameNode::Release(void)
{
	if (_managerInit)
	{
		KEYMANAGER->ReleaseSingleton();
		IMAGEMANAGER->Release();
		IMAGEMANAGER->ReleaseSingleton();
		TIMEMANAGER->Release();
		TIMEMANAGER->ReleaseSingleton();
		SOUNDMANAGER->Release();
		SOUNDMANAGER->ReleaseSingleton();
		SCENEMANAGER->Release();
		SCENEMANAGER->ReleaseSingleton();
		CAMERA->Release();
		CAMERA->ReleaseSingleton();
		TXTDATA->ReleaseSingleton();
		//DATABASE->ReleaseSingleton();
		D2DMANAGER->Release();
		D2DMANAGER->ReleaseSingleton();
	}

}


void GameNode::Update(void)
{
	
}

void GameNode::Render(void)
{

}


LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	
	switch (iMessage)
	{
		/*
		case WM_NCPAINT:
		{
			RECT rect, wr;
			LONG right, bottom;

			HBRUSH hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);

			hdc = GetDCEx(hWnd, (HRGN)wParam, DCX_WINDOW | DCX_INTERSECTRGN);
			GetWindowRect(hWnd, &wr);
			right = wr.right - wr.left;
			bottom = wr.bottom - wr.top;

			SetRect(&rect, 0, 0, right, bottom);

			FillRect(hdc, &rect, hBrush);
			ReleaseDC(hWnd, hdc);
		}
		break;
		*/
		
		case WM_MOUSEMOVE:
			g_ptMouse.x = static_cast<float>(LOWORD(lParam) + CAMERA->posX);
			g_ptMouse.y = static_cast<float>(HIWORD(lParam) + CAMERA->posY);
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
