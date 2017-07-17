#include "stdafx.h"
#include "direct2DManager.h"


direct2DManager::direct2DManager(){}


direct2DManager::~direct2DManager(){}


HRESULT direct2DManager::init()
{
	_direct2DFactory = NULL;
	_renderTarget = NULL;
	_defaultBrush = NULL;
	_defaultTextFormat = NULL;
	_customTextFormat = NULL;
	_writeFactory = NULL;
	//pBitmapRenderTarget = nullptr;
	//pBackBuffer = nullptr;


	HRESULT hResult = E_FAIL;
	
	//---------------------------------------------------------------------------
	//	D2D Factory ����
	//---------------------------------------------------------------------------
	hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_direct2DFactory);

	assert(hResult == S_OK && "CreateFactory is not created");


	//---------------------------------------------------------------------------
	//	Hwnd Render Target ����
	//---------------------------------------------------------------------------
	hResult = _direct2DFactory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)),
		&_renderTarget);


	assert(hResult == S_OK && "CreateRanderTarget is not created");

	//---------------------------------------------------------------------------
	//	Bitmap Render Target ����
	//---------------------------------------------------------------------------

	//hr = pRenderTarget->CreateCompatibleRenderTarget(
	//	SizeF(BACKBUFFERSIZEX, BACKBUFFERSIZEY),
	//	&pBitmapRenderTarget);
	//assert(hr == S_OK);

	//---------------------------------------------------------------------------
	//	IDWriteFactory ����
	//---------------------------------------------------------------------------
	hResult = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,										// ���μ��� �������Ÿ��
		__uuidof(_writeFactory),										// COM ���� ����
		reinterpret_cast<IUnknown **>(&_writeFactory)
	);					// ��ȯ��

	assert(hResult == S_OK && "CreateFactory is not created");


	// �귯�� ����
	_defaultBrush = createBrush(RGB(0, 0, 0));

	//	�⺻ �ؽ�Ʈ ���� ����
	_writeFactory->CreateTextFormat
	(
		L"�������",										//��Ʈ �̸�
		NULL,											//��Ʈ �÷��� ( �Ⱦ��� NULL)
		DWRITE_FONT_WEIGHT_REGULAR,						//��Ʈ ����
		DWRITE_FONT_STYLE_NORMAL,						//��Ʈ ��Ÿ��
		DWRITE_FONT_STRETCH_NORMAL,						//��Ʈ��ġ, �ٵ� � ���̵� ���� ���̸� ��������.
		17.0f,											//��Ʈ ������
		L"",											//�̱��� en-us, �ѱ��� ko-KR �Ϻ��� ja-JP, ������ en-uk
		&_defaultTextFormat								//����� ������ ������
	);

	// COM ���̺귯�� �ʱ�ȭ -> ȣ������ ������ CoCreateInstance�� ����� ������� ����
	CoInitialize(NULL);
	
	return S_OK;
}
void direct2DManager::release()
{
	SAFE_RELEASE_CAPITAL(_defaultBrush);
	SAFE_RELEASE_CAPITAL(_defaultTextFormat);
	SAFE_RELEASE_CAPITAL(_writeFactory);
	SAFE_RELEASE_CAPITAL(_renderTarget);
	SAFE_RELEASE_CAPITAL(_direct2DFactory);
	SAFE_RELEASE_CAPITAL(_customTextFormat);
}


void direct2DManager::beginDraw()
{
	_renderTarget->BeginDraw();
	_renderTarget->Clear(ColorF(ColorF::Aqua));
}

void direct2DManager::endDraw()
{
	_renderTarget->EndDraw();
}

ID2D1SolidColorBrush* direct2DManager::createBrush(COLORREF rgb, float opacity)
{
	HRESULT hResult;
	ID2D1SolidColorBrush* brush;
	brush = NULL;

	hResult = _renderTarget->CreateSolidColorBrush(ColorF(rgb, opacity), &brush);

	return brush;
}


void direct2DManager::DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	_renderTarget->DrawTextA(string, lstrlenW(string), _defaultTextFormat, RectF(x1, y1, x2, y2), brush);
	
	
}

void direct2DManager::DrawTextD2D(ID2D1SolidColorBrush* brush, LPCWSTR fontName, float fontSize, LPCWSTR string, float startX, float startY, float endX, float endY)
{
	float x1 = startX;
	float y1 = startY;
	float x2 = endX;
	float y2 = endY;

	//	TextFormat ����
	_writeFactory->CreateTextFormat(fontName, NULL, DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize, L"", &_customTextFormat);


	_renderTarget->DrawTextA(string, lstrlenW(string), _customTextFormat, RectF(x1, y1, x2, y2), brush);

	SAFE_RELEASE_CAPITAL(_customTextFormat);
}