#pragma once
#include "Image.h"


class GameNode
{
private:
	bool _managerInit;
	char str[128];

public:
	//HRESULT ���ҿ��� ���� �ǵ�
	//�Լ��� ȣ���� �� �Ǹ� S_OK, �����ϸ� E_FAIL������
	//�ʱ�ȭ�� �ߵǾ����� ���θ� ���������� �˷���
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

