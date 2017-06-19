#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//�ʱ�ȭ ���ִ� �Լ�
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("�޹��", "background.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 0, 0, 1536, 79, 16, 1, true, RGB(255, 0, 255));


	_starScene = new starcraftScene;
	_starScene->init();
	
	
	return S_OK;
}

//�޸� ���� �Լ�
void mainGame::release(void)
{
	gameNode::release();


}

//�������ִ� ��
void mainGame::update(void)
{
	gameNode::update();

	_starScene->update();

}

//���Ⱑ �׷��ִ� ��
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================

	IMAGEMANAGER->findImage("�޹��")->render(getMemDC(),0,0);
	
	_starScene->render();
	
	TIMEMANAGER->render(getMemDC());
	//================================================================================
	//�ǵ������� �̰ŵ�
	this->getBackBuffer()->render(getHDC(), 0, 0);

}
