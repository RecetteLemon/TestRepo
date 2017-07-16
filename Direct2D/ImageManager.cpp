#include "stdafx.h"
#include "ImageManager.h"


ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}



HRESULT ImageManager::Init(void)
{


	return S_OK;
}

void ImageManager::Release(void)
{
	DeleteAll();
}



/*
===================================================================
						�̹��� �߰�
===================================================================
*/

//���ҽ����� �߰�
/*
Image* ImageManager::AddImage(string strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor, BOOL useAlphaBlend)
{
	//���� ������ Ű ���� ���� �̹����� �ִ��� �˻�
	Image* img = FindImage(strKey);

	//���࿡ �̹����� ������~ �� �̹����� ��ȯ
	if (img) return img;

	//������� ������ ���°Ŵϱ�
	img = new Image;

	//���� ����� �̹����� �ʱ�ȭ ���� �ʾ����� �ΰ����� �ʱ�ȭ
	if (FAILED(img->Init(resID, width, height, trans, transColor, useAlphaBlend)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//������ �� �� ��Ȳ�̹Ƿ� �ʿ� �־��ݴϴ� �� _��
	_mImageList.insert(make_pair(strKey, img));

	return img;
}
*/

// ���Ͽ��� �߰�
Image* ImageManager::AddImage(string strKey, LPCWSTR fileName, int width, int height)
{
	//���� ������ Ű ���� ���� �̹����� �ִ��� �˻�
	Image* img = FindImage(strKey);

	// �̹����� ������ �� �̹����� ��ȯ
	if (img) return img;

	// �̹����� ������ �޸� ���� �Ҵ�
	img = new Image;

	//�̹����� �ʱ�ȭ�ϰ� �������� ��� �޸� ����
	if (FAILED(img->Init(fileName, width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//�ʿ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//������ �̹��� �߰�
Image* ImageManager::AddFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY)
{
	//���� ������ Ű ���� ���� �̹����� �ִ��� �˻�
	Image* img = FindImage(strKey);

	// �̹����� ������ �� �̹����� ��ȯ
	if (img) return img;

	// �̹����� ������ �޸� ���� �Ҵ�
	img = new Image;

	//�̹����� �ʱ�ȭ�ϰ� �������� ��� �޸� ����
	if (FAILED(img->Init(fileName, width, height, frameNumX, frameNumY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//�ʿ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;

}


//�̹��� ã�� �Լ�
Image* ImageManager::FindImage(string strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL ImageManager::DeleteImage(string strKey)
{
	//�ش� Ű ���� �����ϴ��� �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->Release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;

}

BOOL ImageManager::DeleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->Release();
			SAFE_DELETE(iter->second);
			iter = _mImageList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	_mImageList.clear();

	return TRUE;
}

/*
===================================================================
			���� �Լ� - Left Top �������� ����
===================================================================
*/


//�⺻ ���
void ImageManager::Render(string strKey, float opacity)
{
	Image* img = FindImage(strKey);
	if (img) img->Render(opacity);
}


//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����
void ImageManager::Render(string strKey, float destX, float destY, float opacity)
{
	Image* img = FindImage(strKey);
	if (img) img->Render(destX, destY, opacity);
}

//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ����, ����
void ImageManager::Render(string strKey, float destX, float destY, int showWidth, int showHeight, float opacity = 1.0f)
{
	Image* img = FindImage(strKey);
	if (img) img->Render(destX, destY, showWidth, showHeight, opacity);
}


//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
void ImageManager::Render(string strKey, float destX, float destY, float sourX, float sourY,
	int sourWidth, int sourHeight, float opacity)
{
	Image* img = FindImage(strKey);
	if (img) img->Render(destX, destY, sourX, sourY,
		sourWidth, sourHeight, opacity);
}

//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
void ImageManager::Render(string strKey, float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
	int sourWidth, int sourHeight, float opacity = 1.0f)
{
	Image* img = FindImage(strKey);
	if (img) img->Render(destX, destY, showWidth, showHeight, sourX, sourY,
		sourWidth, sourHeight, opacity);
}



//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
void ImageManager::FrameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float opacity)
{
	Image* img = FindImage(strKey);
	if (img) img->FrameRender(destX, destY, currentFrameX, currentFrameY, opacity);
}

//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
void ImageManager::FrameRender(string strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX = 0, int currentFrameY = 0, float opacity = 1.0f)
{
	Image* img = FindImage(strKey);
	if (img) img->FrameRender(destX, destY, showWidth, showHeight, currentFrameX, currentFrameY, opacity);
}



//���� ���� - ���� �ʿ�
/*
void ImageManager::LoopRender(string strKey, const LPRECT drawArea, int offSetX, int offSetY, float opacity)
{
	Image* img = FindImage(strKey);
	if (img) img->LoopRender(drawArea, offSetX, offSetY, opacity);
}
*/


