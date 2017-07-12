#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

//�޽����ڽ��� ��Ʈ�� �� ����
enum CTRL
{
	CTRL_SAVE,			//���̺�
	CTRL_LOAD,			//�ε�
	CTRL_TERRAINDRAW,	//���� �׸���
	CTRL_OBJDRAW,		//������Ʈ �׸���
	CTRL_ERASER,		//���찳
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	

public:
	int _ctrSelect;

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setMap(void);
	virtual void save(void);
	virtual void load(void);

	void setCtrlSelect(int num) { _ctrSelect = num; }

	image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);


	gameNode();
	virtual ~gameNode();
};

