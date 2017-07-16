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
	IDWriteTextFormat*			pDefaultTextFormat;		//기본 텍스트 포맷
	IDWriteTextFormat*			pCustomTextFormat;		//커스텀 텍스트 포맷
	ID2D1SolidColorBrush*		defaultBrush;			//기본 검정색 브러쉬

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
	- 카메라 이동 보정 & 범위에 들어가는 내용만 렌더
	===================================================================
	*/
	
	void DrawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void DrawEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth = 1.0f);
	void FillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);
	void FillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY);


	//출력할 문자열, 문자열을 그릴 Rect의 Left, Top, Right, Bottom, 그릴 브러쉬
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY);

	//출력할 문자열, 문자열을 그릴 Rect의 Left, Top, Right, Bottom, 그릴 브러쉬, 폰트명, 폰트 크기
	void DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY);

	D2DManager();
	~D2DManager();
};

