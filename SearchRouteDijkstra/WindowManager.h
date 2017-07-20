#pragma once
#include "Common.h"

#define WINDOW	WindowManager::Instance()

extern HINSTANCE g_hInst;

struct Window
{
	HWND handle;
	int x, y;
	int width, height;

	Window(HWND hWnd, int x, int y, int width, int height)
	{
		this->handle = hWnd;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}
};

class WindowManager : public Singleton<WindowManager>
{
	map<int, Window*> m_windows;

public:
	Event<HDC> onPaint;
	Event<TCHAR> onChar;

	void RegisterData(TCHAR* dataName, UINT style, COLORREF bgColor)
	{
		WNDCLASS* pWndClass = new WNDCLASS;
		pWndClass->cbClsExtra = 0;		// Ư�� ������ ���� ���� ����
		pWndClass->cbWndExtra = 0;		// Ư�� ������ ���� ���� ����
		pWndClass->hbrBackground = CreateSolidBrush(bgColor);	// ��׶��� �귯�� ����
		pWndClass->hCursor = LoadCursor(NULL, IDC_ARROW);		// Ŀ�� ����
		pWndClass->hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ����
		pWndClass->hInstance = g_hInst;						// �ν��Ͻ� ����
		pWndClass->lpfnWndProc = WndProc;						// �޽��� ó�� �Լ� ����
		pWndClass->lpszClassName = dataName;					// ������ �̸� ����
		pWndClass->lpszMenuName = NULL;						// �޴� ���� (�޴��� ���� ������� NULL)
		pWndClass->style = style;			// �������� ���μ��� ũ�Ⱑ ���ҽÿ� �ٽ� �׸���.

		RegisterClass(pWndClass);
	}

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			WINDOW->onPaint.Execute(hdc);

			EndPaint(hWnd, &ps);
		}
		break;

		case WM_CHAR:
		{
			WINDOW->onChar.Execute(wParam);
		}
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

		return 0;
	}

	Window* Get(int windowID)
	{
		if (m_windows.find(windowID) != m_windows.end())
		{
			return m_windows[windowID];
		}
		return NULL;
	}

	HWND GetHandle(int windowID)
	{
		Window* pWindow = Get(windowID);
		if (pWindow != NULL)
		{
			return pWindow->handle;
		}
		return NULL;
	}

	void Create(int windowID, TCHAR* dataName, TCHAR* title, int x, int y, int width, int height)
	{
		DWORD style = WS_CAPTION | WS_SYSMENU;
		HWND hWnd = CreateWindow(dataName, title, style, x, y, width, height, NULL, NULL, g_hInst, NULL);
		ShowWindow(hWnd, SW_SHOW);

		RECT rc = { 0, 0, width, height };
		AdjustWindowRect(&rc, style, false);
		MoveWindow(hWnd, x, y, rc.right - rc.left, rc.bottom - rc.top, true);

		m_windows[windowID] = new Window(hWnd, x, y, width, height);
	}

	void CreateButton(int buttonID, HWND hParent, TCHAR* text, int x, int y, int width, int height)
	{
		HWND hButton = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			x, y, width, height, hParent, (HMENU)buttonID, g_hInst, NULL);
		m_windows[buttonID] = new Window(hButton, x, y, width, height);
	}

	void CreateCheckBox(int buttonID, HWND hParent, TCHAR* text, int x, int y, int width, int height)
	{
		HWND hButton = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			x, y, width, height, hParent, (HMENU)buttonID, g_hInst, NULL);
		m_windows[buttonID] = new Window(hButton, x, y, width, height);
	}

	void CreateAutoCheckBox(int buttonID, HWND hParent, TCHAR* text, int x, int y, int width, int height)
	{
		HWND hButton = CreateWindow(TEXT("button"), text, WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			x, y, width, height, hParent, (HMENU)buttonID, g_hInst, NULL);
		m_windows[buttonID] = new Window(hButton, x, y, width, height);
	}

	void CreateRadioButton(int buttonID, HWND hParent, TCHAR* text, int x, int y, int width, int height, bool group = false)
	{
		DWORD style = (group) ? WS_GROUP | WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON : WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON;
		HWND hButton = CreateWindow(TEXT("button"), text, style,
			x, y, width, height, hParent, (HMENU)buttonID, g_hInst, NULL);
		m_windows[buttonID] = new Window(hButton, x, y, width, height);
	}

	void CreateAutoRadioButton(int buttonID, HWND hParent, TCHAR* text, int x, int y, int width, int height, bool group = false)
	{
		DWORD style = (group) ? WS_GROUP | WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON : WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON;
		HWND hButton = CreateWindow(TEXT("button"), text, style,
			x, y, width, height, hParent, (HMENU)buttonID, g_hInst, NULL);
		m_windows[buttonID] = new Window(hButton, x, y, width, height);
	}

	LRESULT Send(int windowID, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Window* pWindow = Get(windowID);
		if (pWindow != NULL)
		{
			return SendMessage(pWindow->handle, msg, wParam, lParam);
		}
		return -1;
	}

	void Destroy(int windowID)
	{
		Window* pWindow = Get(windowID);
		if (pWindow != NULL)
		{
			m_windows.erase(windowID);
			delete pWindow;
		}
	}
};

