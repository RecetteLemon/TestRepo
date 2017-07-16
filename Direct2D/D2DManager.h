#pragma once
#include "SingletonBase.h"

class D2DManager : public SingletonBase<D2DManager>
{
public:
	ID2D1Factory*				pD2DFactory;
	ID2D1HwndRenderTarget*		pRenderTarget;
	//ID2D1BitmapRenderTarget*	pBitmapRenderTarget;
	//ID2D1Bitmap*				pBackBuffer;
	IDWriteFactory*				pWriteFactory;
	IDWriteTextFormat*			pDefaultTextFormat;		//�⺻ �ؽ�Ʈ ����
	IDWriteTextFormat*			pCustomTextFormat;		//Ŀ���� �ؽ�Ʈ ����
	ID2D1SolidColorBrush*		defaultBrush;			//�⺻ ������ �귯��

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();
	void BeginDraw();
	void EndDraw();
	ID2D1SolidColorBrush* CreateBrush(COLORREF rgb, float opacity = 1.0f);
	


	/*
	===================================================================
				Draw, Fill Method (Line, Rectangle, Ellipse)
	- ī�޶� �̵� ���� & ������ ���� ���븸 ����
	===================================================================
	*/
	
	void DrawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void FillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);
	void FillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);


	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);

	//����� ���ڿ�, ���ڿ��� �׸� Rect�� Left, Top, Right, Bottom, �׸� �귯��, ��Ʈ��, ��Ʈ ũ��
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);

	D2DManager();
	~D2DManager();
};

