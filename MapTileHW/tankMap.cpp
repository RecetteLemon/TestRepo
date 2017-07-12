#include "stdafx.h"
#include "tankMap.h"


tankMap::tankMap()
{
}


tankMap::~tankMap()
{

}

HRESULT tankMap::init()
{
	IMAGEMANAGER->addFrameImage("mapTiles", "mapTiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	load();

	return S_OK;
}

void tankMap::release()
{

}

void tankMap::update() 
{

}

void tankMap::render() 
{
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//�ͷ���
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
	//������Ʈ
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
}


void tankMap::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("mapSave00.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	CloseHandle(file);


	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].terrain == TR_WATER)
		{
			_attribute[i] = ATTR_UNMOVE;
		}
	}
}
