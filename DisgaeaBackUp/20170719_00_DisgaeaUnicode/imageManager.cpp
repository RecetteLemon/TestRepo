#include "stdafx.h"
#include "ImageManager.h"


imageManager::imageManager()
{
}


imageManager::~imageManager()
{
}


void imageManager::release(void)
{
	deleteAll();
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
image* imageManager::addImage(wstring strKey, LPCWSTR fileName, int width, int height)
{
	//���� ������ Ű ���� ���� �̹����� �ִ��� �˻�
	image* img = findImage(strKey);

	// �̹����� ������ �� �̹����� ��ȯ
	if (img) return img;

	// �̹����� ������ �޸� ���� �Ҵ�
	img = new image;

	//�̹����� �ʱ�ȭ�ϰ� �������� ��� �޸� ����
	if (FAILED(img->init(fileName, width, height)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//�ʿ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;
}


//������ �̹��� �߰�
image* imageManager::addFrameImage(wstring strKey, LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY)
{
	//���� ������ Ű ���� ���� �̹����� �ִ��� �˻�
	image* img = findImage(strKey);

	// �̹����� ������ �� �̹����� ��ȯ
	if (img) return img;

	// �̹����� ������ �޸� ���� �Ҵ�
	img = new image;

	//�̹����� �ʱ�ȭ�ϰ� �������� ��� �޸� ����
	if (FAILED(img->init(fileName, width, height, frameNumX, frameNumY)))
	{
		SAFE_DELETE(img);

		return NULL;
	}

	//�ʿ� �߰�
	_mImageList.insert(make_pair(strKey, img));

	return img;

}


//�̹��� ã�� �Լ�
image* imageManager::findImage(wstring strKey)
{
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		return key->second;
	}

	return NULL;
}


BOOL imageManager::deleteImage(wstring strKey)
{
	//�ش� Ű ���� �����ϴ��� �˻��Ѵ�
	mapImageIter key = _mImageList.find(strKey);

	if (key != _mImageList.end())
	{
		key->second->release();
		SAFE_DELETE(key->second);
		_mImageList.erase(key);

		return true;
	}

	return false;

}

BOOL imageManager::deleteAll(void)
{
	mapImageIter iter = _mImageList.begin();

	for (; iter != _mImageList.end();)
	{
		if (iter->second != NULL)
		{
			iter->second->release();
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
void imageManager::render(wstring strKey, float opacity)
{
	image* img = findImage(strKey);
	if (img) img->render(opacity);
}


//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����
void imageManager::render(wstring strKey, float destX, float destY, float opacity)
{
	image* img = findImage(strKey);
	if (img) img->render(destX, destY, opacity);
}

//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ����, ����
void imageManager::render(wstring strKey, float destX, float destY, int showWidth, int showHeight, float opacity = 1.0f)
{
	image* img = findImage(strKey);
	if (img) img->render(destX, destY, showWidth, showHeight, opacity);
}


//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
void imageManager::render(wstring strKey, float destX, float destY, float sourX, float sourY,
	int sourWidth, int sourHeight, float opacity)
{
	image* img = findImage(strKey);
	if (img) img->render(destX, destY, sourX, sourY,
		sourWidth, sourHeight, opacity);
}

//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
void imageManager::render(wstring strKey, float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
	int sourWidth, int sourHeight, float opacity = 1.0f)
{
	image* img = findImage(strKey);
	if (img) img->render(destX, destY, showWidth, showHeight, sourX, sourY,
		sourWidth, sourHeight, opacity);
}



//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
void imageManager::frameRender(wstring strKey, float destX, float destY, int currentFrameX, int currentFrameY, float opacity)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(destX, destY, currentFrameX, currentFrameY, opacity);
}

//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
void imageManager::frameRender(wstring strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX = 0, int currentFrameY = 0, float opacity = 1.0f)
{
	image* img = findImage(strKey);
	if (img) img->frameRender(destX, destY, showWidth, showHeight, currentFrameX, currentFrameY, opacity);
}



//���� ���� - ���� �ʿ�
/*
void ImageManager::LoopRender(string strKey, const LPRECT drawArea, int offSetX, int offSetY, float opacity)
{
Image* img = FindImage(strKey);
if (img) img->LoopRender(drawArea, offSetX, offSetY, opacity);
}
*/