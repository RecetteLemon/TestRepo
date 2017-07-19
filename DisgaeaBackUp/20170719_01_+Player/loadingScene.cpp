#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init()
{
	_ld = new loading;
	_ld->init();
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}
void loadingScene::release()
{
	SAFE_DELETE(_ld);
}
void loadingScene::update()
{
	_ld->update();
	if (_ld->loadingDone()) SCENEMANAGER->changeScene(L"DungeonScene");
}
void loadingScene::render()
{
	_ld->render();
}
void loadingScene::loadingImage()
{
	
	// �޴��� �̹���
	_ld->loadImage(L"Menu", L"Image/Menu/M01.png", 1600, 900);
	_ld->loadImage(L"MenuMouse", L"Image/Menu/MMouse.png", 50, 39);
	_ld->loadFrameImage(L"startButton", L"Image/MapTool/buttonStart.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"saveButton", L"Image/MapTool/buttonSave.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"loadButton", L"Image/MapTool/buttonLoad.png", 243, 258, 1, 2);
	_ld->loadFrameImage(L"terrainButton", L"Image/MapTool/BtnTerrain.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"objectButton", L"Image/MapTool/BtnObject.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"eraseButton", L"Image/MapTool/BtnEraser.png", 125, 64, 1, 2);
	_ld->loadFrameImage(L"isoTerrain", L"Image/MapTool/isoTile.png", 480, 96, 5, 2);
	_ld->loadFrameImage(L"isoTerrain", L"Image/MapTool/isoTile96.png", 960, 480, 10, 5);
	_ld->loadFrameImage(L"isoObject", L"Image/MapTool/isoObject2.png", 180, 160, 2, 1);
	_ld->loadImage(L"isoEraser", L"Image/MapTool/isoEraser.png", 128, 128);

	// ?? �̹���


	// ?? �̹���


	// ?? �̹���


	// ?? �̹���


}
void loadingScene::loadingSound()
{
	// �޴� �����


	// ?? Sound


	// ?? Sound


	// ?? Sound

	
	// ?? Sound

	
	// ?? Sound
}