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
	DIRECT2D->beginDraw();
	//==============================================================================
	
	
	
	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render();
	DIRECT2D->endDraw();
	

	

}
