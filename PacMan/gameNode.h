#pragma once
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

//메시지박스로 컨트롤 할 종류
enum CTRL
{
	CTRL_SAVE,			//세이브
	CTRL_LOAD,			//로드
	CTRL_TERRAINDRAW,	//지형 그리기
	CTRL_OBJDRAW,		//오브젝트 그리기
	CTRL_ERASER,		//지우개
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

