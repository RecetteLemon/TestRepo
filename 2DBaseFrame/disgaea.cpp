#include "stdafx.h"
#include "disgaea.h"


disgaea::disgaea()
{
}


disgaea::~disgaea()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT disgaea::init(void)
{
	gameNode::init(true);


	return S_OK;
}

//�޸� ���� �Լ�
void disgaea::release(void)
{
	

	gameNode::release();

	

}

//�������ִ� ��
void disgaea::update(void)
{
	gameNode::update();



}

//���Ⱑ �׷��ִ� ��
void disgaea::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
