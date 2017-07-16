#include "stdafx.h"
#include "D2DManager.h"


D2DManager::D2DManager()
{
}


D2DManager::~D2DManager()
{
}


HRESULT D2DManager::Init()
{
	pD2DFactory = nullptr;
	pRenderTarget = nullptr;
	//pBitmapRenderTarget = nullptr;
	//pBackBuffer = nullptr;
	

	
	HRESULT hr = E_FAIL;

	//---------------------------------------------------------------------------
	//	D2D Factory 생성
	//---------------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	
	assert(hr == S_OK);


	//---------------------------------------------------------------------------
	//	Hwnd Render Target 생성
	//---------------------------------------------------------------------------
	hr = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(g_hWnd, SizeU(WINSIZEX, WINSIZEY)),
		&pRenderTarget);
	assert(hr == S_OK);

	//---------------------------------------------------------------------------
	//	Bitmap Render Target 생성
	//---------------------------------------------------------------------------

	//hr = pRenderTarget->CreateCompatibleRenderTarget(
	//	SizeF(BACKBUFFERSIZEX, BACKBUFFERSIZEY),
	//	&pBitmapRenderTarget);
	//assert(hr == S_OK);

	//---------------------------------------------------------------------------
	//	IDWriteFactory 생성
	//---------------------------------------------------------------------------
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pWriteFactory),
		reinterpret_cast<IUnknown **>(&pWriteFactory));
	assert(hr == S_OK && "hr is not founded");

	
	// 브러쉬 생성
	defaultBrush = CreateBrush(RGB(0, 0, 0));

	//	기본 텍스트 포맷 생성
	pWriteFactory->CreateTextFormat(L"맑은고딕", NULL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 17.0f, L"", &pDefaultTextFormat);

	// COM 라이브러리 초기화 -> 호출하지 않으면 CoCreateInstance가 제대로 수행되지 않음
	CoInitialize(NULL);


	return S_OK;
}

void D2DManager::Release()
{
	SAFE_RELEASE(defaultBrush);
	SAFE_RELEASE(pDefaultTextFormat);
	SAFE_RELEASE(pWriteFactory);
	SAFE_RELEASE(pRenderTarget);
	SAFE_RELEASE(pD2DFactory);
}

void D2DManager::Update()
{

}

void D2DManager::Render()
{
	

	



	
}

void D2DManager::BeginDraw()
{
	// hWndRenderTarget Begin
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(ColorF(ColorF::Aqua));
	
	// BitmapRenderTarget Begin
	//pBitmapRenderTarget->BeginDraw();
	//pBitmapRenderTarget->Clear(ColorF(ColorF::White));
	//pBitmapRenderTarget->GetBitmap(&pBackBuffer);

}

void D2DManager::EndDraw()
{
	// BitmapRenderTarget End
	//pBitmapRenderTarget->EndDraw();


	// hWndRenderTarget Draw (bitmap -> hWnd)
	//D2D1_RECT_F dxArea = RectF(0, 0, WINSIZEX, WINSIZEY);
	//D2D1_RECT_F dxArea2 = RectF(CAMERA->posX, CAMERA->posY,
	//	CAMERA->posX + WINSIZEX, CAMERA->posY + WINSIZEY);
	//pRenderTarget->DrawBitmap(pBackBuffer, dxArea, 1.0f,
	//	D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);


	// hWndRenderTarget End
	
	pRenderTarget->EndDraw();
}


ID2D1SolidColorBrush* D2DManager::CreateBrush(COLORREF rgb, float opacity)
{
	HRESULT hr;
	ID2D1SolidColorBrush* brush;
	brush = nullptr;

	hr = pRenderTarget->CreateSolidColorBrush(ColorF(rgb, opacity), &brush);

	return brush;
}




/*
===================================================================
			Draw, Fill Method (Line, Rectangle, Ellipse)
- 카메라 이동 보정 & 범위에 들어가는 내용만 렌더
===================================================================
*/

void D2DManager::DrawLine(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;
	
	
	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;
	

	pRenderTarget->DrawLine(Point2F(x1, y1), Point2F(x2, y2), brush, strokeWidth);
}

void D2DManager::DrawRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;


	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	pRenderTarget->DrawRectangle(RectF(x1, y1, x2, y2), brush, strokeWidth);

}

void D2DManager::DrawEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY, float strokeWidth)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;
	float width = endX - startX;
	float height = endY - startY;


	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = x1 + width * 0.5;
	ellipse.point.y = y1 + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;

	pRenderTarget->DrawEllipse(&ellipse, brush, strokeWidth);
}

void D2DManager::FillRectangle(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;

	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	pRenderTarget->FillRectangle(RectF(x1, y1, x2, y2), brush);
}
void D2DManager::FillEllipse(ID2D1SolidColorBrush* brush, float startX, float startY, float endX, float endY)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;
	float width = endX - startX;
	float height = endY - startY;

	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	D2D1_ELLIPSE ellipse;
	ellipse.point.x = x1 + width * 0.5;
	ellipse.point.y = y1 + height * 0.5;
	ellipse.radiusX = width * 0.5;
	ellipse.radiusY = height * 0.5;

	pRenderTarget->FillEllipse(&ellipse, brush);

	
}








void D2DManager::DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;

	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	
	pRenderTarget->DrawTextA(string, lstrlenW(string), pDefaultTextFormat, RectF(x1, y1, x2, y2), brush);
}

void D2DManager::DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX - CAMERA->posX;
	float y1 = startY - CAMERA->posY;
	float x2 = endX - CAMERA->posX;
	float y2 = endY - CAMERA->posY;

	if (x1 < 0 && x2 < 0) return;
	if (y1 < 0 && y2 < 0) return;
	if (x1 > WINSIZEX && x2 > WINSIZEX) return;
	if (y1 > WINSIZEY && y2 > WINSIZEY) return;

	//	TextFormat 생성
	pWriteFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &pCustomTextFormat);


	pRenderTarget->DrawTextA(string, lstrlenW(string), pCustomTextFormat, RectF(x1, y1, x2, y2), brush);

	SAFE_RELEASE(pCustomTextFormat);
}