#pragma once
#include "Image.h"


class GameNode
{
private:
	bool _managerInit;
	char str[128];

public:
	//HRESULT 마소에서 만든 건데
	//함수가 호출이 잘 되면 S_OK, 실패하면 E_FAIL등으로
	//초기화가 잘되었는지 여부를 실패했을때 알려줌
	virtual HRESULT Init(void);
	virtual HRESULT Init(bool managerInit);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

public:
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode();
	virtual ~GameNode();
};

