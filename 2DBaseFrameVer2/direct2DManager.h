#pragma once
#include "singletonBase.h"


class direct2DManager : public singletonBase<direct2DManager>
{
public:

	ID2D1Factory*				_direct2DFactory;		//���丮�� �����ؾ� �׸����� ������ �� �� �ִ�.
	ID2D1HwndRenderTarget*		_renderTarget;			//�����쿡 �׸��� ���� HwndRender���ٰ� Ÿ���� ��´�
	IDWriteFactory*				_writeFactory;			//�ؽ�Ʈ�� ���� ���� ���丮 ����
	IDWriteTextFormat*			_defaultTextFormat;		//�⺻ �ؽ�Ʈ ����
	IDWriteTextFormat*			_customTextFormat;		//Ŀ���� �ؽ�Ʈ ����
	ID2D1SolidColorBrush*		_defaultBrush;			//�⺻ ������ �귯��

	ID2D1DCRenderTarget*		_hdcRenderTarget;


	HRESULT init();
	void release();
	void beginDraw();									//���� ������ ó���� �־��ش�.
	void endDraw();										//���� ������ ���߿� �־��ش�.
	ID2D1SolidColorBrush* createBrush(COLORREF rgb, float opacity = 1.0f);


	void DrawTextD2D
	(
		ID2D1SolidColorBrush* brush,								// ���ڻ�
		LPCWSTR string,												// ���ڿ�
		float startX, float startY, float endX, float endY			// �ؽ�Ʈ ��Ʈ�ڽ�
	);

	
	void DrawTextD2D
	(
		ID2D1SolidColorBrush* brush,								// ���ڻ�
		LPCWSTR fontName,											// ��Ʈ�̸�
		float fontSize, LPCWSTR string,								// ��Ʈ ũ��, ���ڿ�
		float startX, float startY, float endX, float endY			// �ؽ�Ʈ ��Ʈ�ڽ�
	);

	direct2DManager();
	~direct2DManager();
};

