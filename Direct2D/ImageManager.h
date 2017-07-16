#pragma once
#include "SingletonBase.h"
#include "Image.h"
#include <map>

class ImageManager : public SingletonBase<ImageManager>
{
public:
	typedef map<string, Image*> mapImageList;
	typedef map<string, Image*>::iterator mapImageIter;

private:
	mapImageList _mImageList;

public:
	
	HRESULT Init(void);
	void Release(void);

		
	/*
	===================================================================
								�̹��� �߰�
	===================================================================
	*/

	//���ҽ����� �̹��� �߰�
	//Image* AddImage(string strKey, const DWORD resID, int width, int height, bool trans, COLORREF transColor, BOOL useAlphaBlend = false);
	
	//�Ϲ� �̹��� �߰�
	Image* AddImage(string strKey, LPCWSTR fileName, int width, int height);
	
	//������ �̹��� �߰�
	Image* AddFrameImage(string strKey, LPCWSTR fileName, int width, int height, int frameNumX, int frameNumY);




	//�̹��� ã�� �Լ�
	Image* FindImage(string strKey);

	BOOL DeleteImage(string strKey);

	BOOL DeleteAll(void);



	/*
	===================================================================
					���� �Լ� - Left Top �������� ����
	===================================================================
	*/


	//�⺻ ���
	void Render(string strKey, float opacity);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����
	void Render(string strKey, float destX, float destY, float opacity);

	//���� ũ�� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���̤� ����
	void Render(string strKey, float destX, float destY, int showWidth, int showHeight, float opacity);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void Render(string strKey, float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);

	//���� ũ��� �߶� �������� - Ű��, �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void Render(string strKey, float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);





	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void FrameRender(string strKey, float destX, float destY, int currentFrameX, int currentFrameY, float opacity);

	//���� ũ�� �����ӷ��� - Ű��, �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void FrameRender(string strKey, float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float opacity);


	//���� ���� - Image::LoopRender ���� �ʿ�
	//void LoopRender(string strKey, const LPRECT drawArea, int offSetX = 0, int offSetY = 0, float opacity = 1.0f);

	

	ImageManager();
	~ImageManager();
};

