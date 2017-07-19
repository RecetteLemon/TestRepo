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

	SCENEMANAGER->addScene(L"LoadingScene", new loadingScene);
	SCENEMANAGER->addScene(L"MenuScene", new menuScene);
	SCENEMANAGER->addScene(L"MapToolScene", new mapToolScene);
	SCENEMANAGER->addScene(L"DungeonScene", new dungeonScene);
	SCENEMANAGER->addScene(L"testScene", new testScene);
	SCENEMANAGER->changeScene(L"testScene");


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
	SCENEMANAGER->update();
	
}

//���Ⱑ �׷��ִ� ��
void disgaea::render(void)
{
	DIRECT2D->beginDraw();
	//==============================================================================
	
	
	SCENEMANAGER->render();


	//================================================================================
	//�ǵ������� �̰ŵ�
	TIMEMANAGER->render();
	DIRECT2D->endDraw();
}
