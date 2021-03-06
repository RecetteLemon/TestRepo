#include "stdafx.h"
#include "effectTest.h"


effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("폭발", "explosion.bmp", 0, 0, 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("폭발"), 32, 62, 1, 1.0f);

	//					이펙트 키값   파일이름     이미지가로, 세로, 프레임 가로, 세로, FPS, 이펙트 애니메이션 속도, 버퍼량
	EFFECTMANAGER->addEffect("폭발", "explosion.bmp", 832, 62, 32, 62, 1, 1.0f, 300);

	_count = 0;

	return S_OK;
}

void effectTest::release()
{

}

void effectTest::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		EFFECTMANAGER->play("폭발", _ptMouse.x, _ptMouse.y);
	}


	//_count++;
	//
	//if (_count % 10 == 0)
	//{
	//	EFFECTMANAGER->play("폭발", RND->getFromIntTo(100, 300),RND->getFromIntTo(100, 300));
	//}

	EFFECTMANAGER->update();
	_effect->update();
}

void effectTest::render()
{
	EFFECTMANAGER->render();
	_effect->render();
}
