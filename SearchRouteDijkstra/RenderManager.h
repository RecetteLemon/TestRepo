#pragma once
#include "Common.h"
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>		// IWICImaging
#include <wincodecsdk.h>	// IWICImaging
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace D2D1;

#define RENDER RenderManager::Instance()

enum TEXT_ALIGN
{
	TEXT_ALIGN_LEFT = 0, TEXT_ALIGN_RIGHT = 1, TEXT_ALIGN_CENTER = 2,
};

class IGraphics
{
public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) {}
};

class GText : public IGraphics
{
	IDWriteTextFormat* m_pFormat;
	wstring m_text;
	Vector m_leftTop;
	Vector m_size;
	ColorF m_color;

public:
	GText(IDWriteTextFormat* pFormat, wstring text, Vector leftTop
		, Vector size, ColorF color) : m_color(color)
	{
		m_pFormat = pFormat;
		m_text = text;
		m_leftTop = leftTop;
		m_size = size;
	}

	~GText() { RELEASE_OBJECT(m_pFormat); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		D2D1_RECT_F rect = RectF(m_leftTop.x, m_leftTop.y, m_leftTop.x + m_size.x, m_leftTop.y + m_size.y);

		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);
		pRenderTarget->DrawTextW(m_text.c_str(), m_text.length(), m_pFormat, rect, pBrush);
		RELEASE_OBJECT(pBrush);
	}
};

class GLine : public IGraphics
{
	Vector m_start, m_end;
	ColorF m_color;
	float m_lineSize;

public:
	GLine(Vector start, Vector end, ColorF color, float lineSize) : m_color(color)
	{
		m_start = start;
		m_end = end;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F startPos = Point2F(m_start.x, m_start.y);
		D2D1_POINT_2F endPos = Point2F(m_end.x, m_end.y);
		pRenderTarget->DrawLine(startPos, endPos, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GRect : public IGraphics
{
	Vector m_center, m_size;
	ColorF m_color;
	float m_lineSize;

public:
	GRect(Vector center, Vector size, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_size = size;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		Vector leftTop = m_center - m_size * 0.5f;
		Vector rightBottom = m_center + m_size * 0.5f;
		D2D1_RECT_F rect = RectF(leftTop.x, leftTop.y, rightBottom.x, rightBottom.y);

		if (m_lineSize == 0) pRenderTarget->FillRectangle(rect, pBrush);
		else pRenderTarget->DrawRectangle(rect, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GCircle : public IGraphics
{
	Vector m_center;
	float m_radius;
	ColorF m_color;
	float m_lineSize;

public:
	GCircle(Vector center, float radius, ColorF color, float lineSize) : m_color(color)
	{
		m_center = center;
		m_radius = radius;
		m_lineSize = lineSize;
	}

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(m_color, &pBrush);

		D2D1_POINT_2F center = Point2F(m_center.x, m_center.y);
		D2D1_ELLIPSE ellipse = Ellipse(center, m_radius, m_radius);

		if (m_lineSize == 0) pRenderTarget->FillEllipse(ellipse, pBrush);
		else pRenderTarget->DrawEllipse(ellipse, pBrush, m_lineSize);

		RELEASE_OBJECT(pBrush);
	}
};

class GSprite : public IGraphics
{
	ID2D1Bitmap* m_pImage;
	Vector m_pos;
	Vector m_size;
	Vector m_anchor;
	Vector m_sourcePos;
	Vector m_sourceSize;
	float m_angle;
	float m_scale;
	float m_opacity;
	int m_dir;

public:
	GSprite(ID2D1Bitmap* pImage, Vector anchor = Vector(0.5f, 0.5f))
	{
		m_pImage = pImage;
		m_pos = Vector(0, 0);
		m_size = Vector(pImage->GetSize().width, pImage->GetSize().height);
		m_anchor = anchor;
		m_sourcePos = Vector(0, 0);
		m_sourceSize = m_size;
		m_angle = 0;
		m_scale = 1.0f;
		m_opacity = 1.0f;
		m_dir = 1;
	}

	GSprite(ID2D1Bitmap* pImage, Vector sourcePos, Vector sourceSize, Vector anchor = Vector(0.5f, 0.5f))
		: GSprite(pImage, anchor)
	{
		m_size = sourceSize;
		m_sourcePos = sourcePos;
		m_sourceSize = sourceSize;
	}

	void ResetSize() { m_size = m_sourceSize; }
	void SetPosition(Vector pos) { m_pos = pos; }
	void SetSize(Vector size) { m_size = size; }
	void SetAnchor(Vector anchor) { m_anchor = anchor; }
	void SetAngle(float angle) { m_angle = angle; }
	void SetScale(float scale) { m_scale = scale; }
	void SetOpacity(float opacity) { m_opacity = opacity; }

	Vector Position() { return m_pos; }
	Vector Size() { return m_size * m_scale; }
	Vector Anchor() { return m_anchor; }
	Vector LeftTop() { return Position() - Size() * Anchor(); }
	Vector RightBottom() { return LeftTop() + Size(); }
	Vector Center() { return LeftTop() + Size() * 0.5f; }
	float Scale() { return m_scale; }
	float Opacity() { return m_opacity; }
	float ImageWidth() { return m_pImage->GetSize().width; }
	float ImageHeight() { return m_pImage->GetSize().height; }

	bool IsCollided(Vector point) { return MATH->IsCollided(point, Box(Center(), Size())); }

	void Render(ID2D1RenderTarget* pRenderTarget)
	{
		// 스케일 적용 (좌우반전)
		pRenderTarget->SetTransform(Matrix3x2F::Scale(m_dir, 1.0f, Point2F(Center().x, Center().y)));

		D2D1_RECT_F targetRect = RectF(LeftTop().x, LeftTop().y, RightBottom().x, RightBottom().y);
		D2D1_RECT_F sourceRect = RectF(m_sourcePos.x, m_sourcePos.y, m_sourcePos.x + m_sourceSize.x, m_sourcePos.y + m_sourceSize.y);

		// 비트맵 드로우
		pRenderTarget->DrawBitmap(m_pImage, targetRect, m_opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourceRect);

		// 스케일 초기화
		pRenderTarget->SetTransform(Matrix3x2F::Identity());
	}
};

class RenderManager : public Singleton<RenderManager>
{
	ID2D1Factory*			m_pFactory;
	ID2D1HwndRenderTarget*	m_pRenderTarget;
	IDWriteFactory*			m_pWriteFactory;
	IWICImagingFactory*		m_pImageFactory;

	queue<IGraphics*>		m_queGraphics;
	map<wstring, ID2D1Bitmap*> m_images;

public:
	void Init(HWND hWnd)
	{
		// ID2D1Factory 생성
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

		// HwndRenderTarget 생성
		m_pFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(hWnd, SizeU(VIEW_WIDTH, VIEW_HEIGHT)),
			&m_pRenderTarget);

		// DWriteFactory 생성
		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(*m_pWriteFactory),
			(IUnknown**)&m_pWriteFactory);

		// WICImagingFactory 생성
		CoInitialize(NULL);
		CoCreateInstance(CLSID_WICImagingFactory, NULL,
			CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory));
	}

	void Release()
	{
		RELEASE_OBJECT(m_pImageFactory);
		RELEASE_OBJECT(m_pWriteFactory);
		RELEASE_OBJECT(m_pRenderTarget);
		RELEASE_OBJECT(m_pFactory);
	}

	bool LoadImageFile(wstring key, wstring filename)
	{
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pFrameDecode = NULL;
		IWICFormatConverter* pConverter = NULL;
		ID2D1Bitmap* pBitmap = NULL;

		if (m_images.find(key) == m_images.end())
		{
			// 이미지 파일을 Decoding
			m_pImageFactory->CreateDecoderFromFilename(filename.c_str(), NULL,
				GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder);
			if (pDecoder == NULL) return false;

			pDecoder->GetFrame(0, &pFrameDecode);

			// Converter 생성 및 초기화
			m_pImageFactory->CreateFormatConverter(&pConverter);
			pConverter->Initialize(pFrameDecode, GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone, NULL, 0, WICBitmapPaletteTypeCustom);

			// Bitmap으로 변환 및 생성
			m_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, &pBitmap);
			m_images[key] = pBitmap;
		}
		return true;
	}

	ID2D1Bitmap* GetImage(wstring key)
	{
		if (m_images.find(key) == m_images.end()) return NULL;
		return m_images[key];
	}

	void Draw(wstring text, Vector pos, Vector size, float fontSize = 10, ColorF color = ColorF::White,
		TEXT_ALIGN align = TEXT_ALIGN_LEFT, wstring font = TEXT("Arial"))
	{
		IDWriteTextFormat* pFormat = NULL;
		m_pWriteFactory->CreateTextFormat(font.c_str(), 0,
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize, TEXT("ko"), &pFormat);

		pFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)align);
		m_queGraphics.push(new GText(pFormat, text, pos, size, color));
	}

	void Draw(GSprite* pSprite)
	{
		GSprite* pNewSprite = new GSprite(*pSprite);
		m_queGraphics.push(pNewSprite);
	}

	void Draw(Line line, ColorF color, float lineSize = 1)
	{
		DrawLine(line.StartPoint(), line.EndPoint(), color, lineSize);
	}

	void Draw(Circle circle, ColorF color, float lineSize = 0)
	{
		DrawCircle(circle.center, circle.radius, color, lineSize);
	}

	void Draw(Box box, ColorF color, float lineSize = 1)
	{
		DrawLine(box.LeftTop(), box.RightTop(), color, lineSize);
		DrawLine(box.LeftTop(), box.LeftBottom(), color, lineSize);
		DrawLine(box.RightBottom(), box.RightTop(), color, lineSize);
		DrawLine(box.RightBottom(), box.LeftBottom(), color, lineSize);
	}

	void Draw(Triangle triangle, ColorF color, float lineSize = 1)
	{
		DrawLine(triangle.p0, triangle.p1, color, lineSize);
		DrawLine(triangle.p1, triangle.p2, color, lineSize);
		DrawLine(triangle.p2, triangle.p0, color, lineSize);
	}

	void DrawLine(Vector startPos, Vector endPos, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GLine(startPos, endPos, color, lineSize));
	}

	void FillRect(Vector center, Vector size, ColorF color = ColorF::White)
	{
		m_queGraphics.push(new GRect(center, size, color, 0));
	}

	void DrawRect(Vector center, Vector size, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GRect(center, size, color, lineSize));
	}

	void FillCircle(Vector center, float radius, ColorF color = ColorF::White)
	{
		m_queGraphics.push(new GCircle(center, radius, color, 0));
	}

	void DrawCircle(Vector center, float radius, ColorF color = ColorF::White, float lineSize = 1)
	{
		m_queGraphics.push(new GCircle(center, radius, color, lineSize));
	}

	void Render()
	{
		m_pRenderTarget->BeginDraw();
		m_pRenderTarget->Clear();

		// 도형 출력
		while (m_queGraphics.size() > 0)
		{
			m_queGraphics.front()->Render(m_pRenderTarget);
			delete m_queGraphics.front();
			m_queGraphics.pop();
		}

		m_pRenderTarget->EndDraw();
	}
};