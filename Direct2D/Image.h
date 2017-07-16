#pragma once

//============================================
//			## D2D Image Class ##
//============================================

class Image
{
public:
	// �̹��� ���� ����ü
	typedef struct tagImageInfo
	{
		DWORD					resID;
		IWICImagingFactory*		pWICImagingFactory;		//Windows Imaging Component�� ���� Factory �������̽�
		IWICFormatConverter*	pWICFormatConverter;	//Format Converter
		IWICBitmapDecoder*		pWICDecoder;			//Bitmap Decoder
		IWICBitmapFrameDecode*	pWICFrameDecoder;		//������ ������ ���ڵ��� Decoder �������̽�
		ID2D1Bitmap*			pBitmap;				//D2D�� ��Ʈ��
		int						width;					//���� �̹��� ��
		int						height;					//���� �̹��� ����
		int						currentFrameX;			//���� ������X(��°)
		int						currentFrameY;			//���� ������Y(��°)
		int						maxFrameX;				//�ִ������� 
		int						maxFrameY;				  
		int						frameWidth;				//������ ���� ũ��
		int						frameHeight;			//������ ���� ũ��
		tagImageInfo()
		{
			resID = 0;
			pWICImagingFactory = nullptr;
			pWICFormatConverter = nullptr;
			pWICDecoder = nullptr; 
			pWICFrameDecoder = nullptr;
			pBitmap = nullptr;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	imageInfo;		//�̹��� ����ü
	LPWSTR			fileName;		//���� �̸� ���� ĳ����������
	
	
public:
	Image();
	~Image();


	/*
	===================================================================
								�̹��� �ʱ�ȭ
	===================================================================
	*/

	//���ҽ��κ��� �о�鿩�� �� ���
	//HRESULT Init(const DWORD resID, int width, int height);

	// �Ϲ� �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����
	HRESULT Init(LPCWSTR pFileName, int width, int height);

	// ������ �̹����� ���Ͽ��� ������ ��, ���ϸ�, ���� �ʺ�, ���� ����, ���� ������ ��, ���� ������ ��
	HRESULT Init(LPCWSTR pFileName, int width, int height, int frameNumX, int frameNumY);
	
	// �̹��� ������
	void Release(void);


	/*
	===================================================================
							D2D ��� ���� �Լ�
	- ī�޶� �̵� ���� & ������ ���� ���븸 ����
	- Left Top ����
	===================================================================
	*/
	
	//�⺻ ���
	void Render(float opacity);

	//���� ũ�� ��� - �׷��� x��ǥ, y��ǥ, ����
	void Render(float destX, float destY, float opacity);

	//���� ũ�� ��� - �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ����, ����
	void Render(float destX, float destY, int showWidth, int showHeight, float opacity);

	//���� ũ��� �߶� �������� - �׷��� x��ǥ, y��ǥ -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void Render(float destX, float destY, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);

	//���� ũ��� �߶� �������� - �׷��� x��ǥ, y��ǥ, ����� �ʺ�, ����� ���� -> ������ ���� left, top, ���� ũ��, ���� ũ��, ����
	void Render(float destX, float destY, int showWidth, int showHeight, float sourX, float sourY,
		int sourWidth, int sourHeight, float opacity);


	//���� ũ�� �����ӷ��� - �׷��� x, y ��ǥ, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void FrameRender(float destX, float destY, int currentFrameX, int currentFrameY, float opacity);

	//���� ũ�� �����ӷ��� - �׷��� x, y ��ǥ, ����� �ʺ�, ����� ����, ���� ���� ������ �ε���, ���� ���� ������ �ε���, ����
	void FrameRender(float destX, float destY, int showWidth, int showHeight, int currentFrameX, int currentFrameY, float opacity);

	//���� ���� - ���� �ʿ�
	//void LoopRender(const LPRECT drawArea, int offSetX = 0, int offSetY = 0, float opacity = 1.0f);
	

	/*
	===================================================================
							�̹��� ���� Get, Set
	===================================================================
	*/

	//���� �ػ�
	inline int GetWidth(void) { return imageInfo->width; }

	//���� �ػ�
	inline int GetHeight(void) { return imageInfo->height; }

	//������ �̹��� ����
	inline void SetFrameX(int frameX)
	{
		imageInfo->currentFrameX = frameX;
		if (frameX > imageInfo->maxFrameX) imageInfo->currentFrameX = imageInfo->maxFrameX;
	}

	inline void SetFrameY(int frameY)
	{
		imageInfo->currentFrameY = frameY;
		if (frameY > imageInfo->maxFrameY) imageInfo->currentFrameY = imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX(void) { return imageInfo->maxFrameX; }
	inline int GetMaxFrameY(void) { return imageInfo->maxFrameY; }

	inline int GetFrameX(void) { return imageInfo->currentFrameX; }
	inline int GetFrameY(void) { return imageInfo->currentFrameY; }

	inline int GetFrameWidth(void) { return imageInfo->frameWidth; }
	inline int GetFrameHeight(void) { return imageInfo->frameHeight; }
	

};
