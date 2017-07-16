#include "stdafx.h"
#include "Image.h"

//pragma == �����Ϸ� ���ñ�
#pragma comment(lib, "msimg32.lib")

// Constructor - Member Initializer
Image::Image()
	: imageInfo(NULL),
	fileName(NULL)
{
}


Image::~Image()
{
}

/*
//���ҽ��κ��� �о�鿩�� �� ���
HRESULT Image::Init(const DWORD resID, int width, int height)
{
	if (imageInfo != NULL) Release();
	HRESULT hr = E_FAIL;

	//�̹��� ���� ����
	imageInfo = new IMAGE_INFO;
	imageInfo->loadType = LOAD_RESOURCE;
	imageInfo->resID = resID;
	imageInfo->width = width;
	imageInfo->height = height;

	

	
	fileName = NULL;

	
	//���࿡ �̹������ҽ� �����°� ����������~
	if (imageInfo->pBitmap == 0)
	{
		//�������ش�
		Release();

		return E_FAIL;
	}

	

	return S_OK;
}
*/

/*
===================================================================
							�̹��� �ʱ�ȭ
===================================================================
*/ 
// ���Ϸκ��� �о�鿩�� �� ���
HRESULT Image::Init(LPCWSTR pFileName, int width, int height)
{
	
	if (pFileName == NULL) return E_FAIL;

	if (imageInfo != NULL) Release();

	// �̹��� ���� ����
	HRESULT hr = E_FAIL;
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->currentFrameX = 0;
	imageInfo->currentFrameY = 0;
	imageInfo->frameWidth = width;
	imageInfo->frameHeight = height;
	

	// ���� ��� ����
	int len;
	len = lstrlenW(pFileName);
	fileName = new WCHAR[len + 1];
	lstrcpyW(fileName, pFileName);


	
	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWICImagingFactory));	
	assert(hr == S_OK);
	
	// ���ڴ� ����
	hr = imageInfo->pWICImagingFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWICDecoder));
	assert(hr == S_OK);
	
	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = imageInfo->pWICDecoder->GetFrame(0, &imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ����
	hr = imageInfo->pWICImagingFactory->CreateFormatConverter(&imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = imageInfo->pWICFormatConverter->Initialize(imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(imageInfo->pWICFormatConverter, NULL, &imageInfo->pBitmap);


	// �̹����� �������� �ʾ��� ���
	if (imageInfo->pBitmap == 0)
	{
		Release();
		return E_FAIL;
	}
	
	return S_OK;
}


/*
===================================================================
						������ �̹��� �ʱ�ȭ
===================================================================
*/

// ���� ũ��� �����ϰ� ����� ��
HRESULT Image::Init(LPCWSTR pFileName, int width, int height, int frameNumX, int frameNumY)
{
	if (pFileName == NULL) return E_FAIL;

	if (imageInfo != NULL) Release();

	// �̹��� ���� ����
	HRESULT hr = E_FAIL;
	imageInfo = new IMAGE_INFO;
	imageInfo->width = width;
	imageInfo->height = height;
	imageInfo->currentFrameX = 0;
	imageInfo->currentFrameY = 0;
	imageInfo->maxFrameX = frameNumX - 1;
	imageInfo->maxFrameY = frameNumY - 1;
	imageInfo->frameWidth = width / frameNumX;
	imageInfo->frameHeight = height / frameNumY;

	// ���� ��� ����
	int len;
	len = lstrlenW(pFileName);
	fileName = new WCHAR[len + 1];
	lstrcpyW(fileName, pFileName);



	// WIC�� ����ϱ� ���� Factory ��ü ����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWICImagingFactory));
	assert(hr == S_OK);

	// ���ڴ� ����
	hr = imageInfo->pWICImagingFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWICDecoder));
	assert(hr == S_OK);

	// ù ��° �������� ����� �� �ִ� ��ü ����
	hr = imageInfo->pWICDecoder->GetFrame(0, &imageInfo->pWICFrameDecoder);
	assert(hr == S_OK);

	// ���� ������ ����
	hr = imageInfo->pWICImagingFactory->CreateFormatConverter(&imageInfo->pWICFormatConverter);
	assert(hr == S_OK);

	// ��Ʈ������ ��ȯ
	hr = imageInfo->pWICFormatConverter->Initialize(imageInfo->pWICFrameDecoder, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);

	// ��ȯ�� �̹��� ������ ����Ͽ� D2D�� ��Ʈ�� ����
	hr = D2DMANAGER->pRenderTarget->CreateBitmapFromWicBitmap(imageInfo->pWICFormatConverter, NULL, &imageInfo->pBitmap);


	// �̹����� �������� �ʾ��� ���
	if (imageInfo->pBitmap == 0)
	{
		Release();
		return E_FAIL;
	}

	return S_OK;
}



// ������
void Image::Release(void)
{
	if (imageInfo)
	{
		SAFE_DELETE(imageInfo);
	}
}






/*
===================================================================
						D2D ��� ���� �Լ�
- ī�޶� �̵� ���� & ������ ���� ���븸 ����
- Left Top ����
===================================================================
*/


//�⺻ ���
void Image::Render(float opacity)
{
	float posX = 0 - CAMERA->posX;
	float posY = 0 - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + imageInfo->width < 0) return;
		if (posY + imageInfo->height< 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + imageInfo->width, posY + imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, imageInfo->width, imageInfo->height);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}


//���� ũ�� ���
void Image::Render(float destX, float destY, float opacity)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;
	
	if (imageInfo->pBitmap != NULL)
	{
		if (posX + imageInfo->width < 0) return;
		if (posY + imageInfo->height< 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + imageInfo->width, posY + imageInfo->height);
		D2D1_RECT_F dxArea2 = RectF(0, 0, imageInfo->width, imageInfo->height);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}

//���� ũ�� ���
void Image::Render(float destX, float destY, int showWidth, int showHeight, float opacity)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + showWidth < 0) return;
		if (posY + showHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + showWidth, posY + showHeight);
		D2D1_RECT_F dxArea2 = RectF(0, 0, imageInfo->width, imageInfo->height);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}

//���� ũ��� �߶� ���
void Image::Render(float destX, float destY, float sourX, float sourY, int sourWidth, int sourHeight, float opacity)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + sourWidth < 0) return;
		if (posY + sourHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + sourWidth, posY + sourHeight);
		D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}

}

//���� ũ��� �߶� ���
void Image::Render(float destX, float destY, int showWidth, int showHeight, float sourX, float sourY, int sourWidth, int sourHeight, float opacity = 1.0f)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + showWidth < 0) return;
		if (posY + showHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + showWidth, posY + showHeight);
		D2D1_RECT_F dxArea2 = RectF(sourX, sourY, sourX + sourWidth, sourY + sourHeight);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}

}




/*
===================================================================
						������ �̹��� ���� �Լ�
- ī�޶� �̵� ���� & ������ ���� ���븸 ����
- Left Top ����
===================================================================
*/

//���� ũ�� �����ӷ���
void Image::FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float opacity)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + imageInfo->frameWidth < 0) return;
		if (posY + imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + imageInfo->frameWidth, posY + imageInfo->frameHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * imageInfo->frameWidth, currentFrameY * imageInfo->frameHeight,
			(currentFrameX + 1) * imageInfo->frameWidth, (currentFrameY + 1) * imageInfo->frameHeight);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}

//���� ũ�� �����ӷ���
void Image::FrameRender(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float opacity)
{
	float posX = destX - CAMERA->posX;
	float posY = destY - CAMERA->posY;

	if (imageInfo->pBitmap != NULL)
	{
		if (posX + showWidth < 0) return;
		if (posY + showHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;

		D2D1_RECT_F dxArea = RectF(posX, posY, posX + showWidth, posY + showHeight);
		D2D1_RECT_F dxArea2 = RectF(currentFrameX * imageInfo->frameWidth, currentFrameY * imageInfo->frameHeight,
			(currentFrameX + 1) * imageInfo->frameWidth, (currentFrameY + 1) * imageInfo->frameHeight);
		D2DMANAGER->pRenderTarget->DrawBitmap(imageInfo->pBitmap, dxArea, opacity,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, dxArea2);
	}
}




/*
===================================================================
							���� ���� �Լ�
- ī�޶� �̵� ���� & ������ ���� ���븸 ����
- Left Top ����
						###	���� �ʿ� ###
===================================================================
*/

/*
void Image::LoopRender(const LPRECT drawArea, int offSetX, int offSetY, float opacity)
{
	//offSet���� ������ ��� �ٽ� �纸��
	if (offSetX < 0) offSetX = imageInfo->width + (offSetX % imageInfo->width);
	if (offSetY < 0) offSetY = imageInfo->height + (offSetY % imageInfo->height);

	//�׷����� �ҽ��� ����(�̹���) ����
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� ����
	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�̹��� �ҽ��� ���� ���
		rcSour.top = (y + offSetY) % imageInfo->height;
		rcSour.bottom = imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ��� ������ ��ο� �����(�׷��ִ� ����) ������ ������
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ������ ������
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ������ �ȿ��ٰ�!
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ��� ���� ���� ���
			rcSour.left = (x + offSetX) % imageInfo->width;
			rcSour.right = imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷��ش�
			Render(rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, opacity);
		}
	}
}

*/


