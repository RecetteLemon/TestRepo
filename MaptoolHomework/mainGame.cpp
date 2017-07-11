#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

//초기화 해주는 함수
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addFrameImage("mapTiles", "mapTiles.bmp", 0, 0, 640, 288, SAMPLETILEX, SAMPLETILEY, true, RGB(255, 0, 255));

	setup();

	return S_OK;
}

//메모리 해제 함수
void mainGame::release(void)
{
	gameNode::release();


}

//연산해주는 곳
void mainGame::update(void)
{
	gameNode::update();

	//.map <----- MSDN 
	

}

//여기가 그려주는 곳
void mainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================================
	
	IMAGEMANAGER->render("mapTiles", getMemDC(), WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth(), 0);

	//터레인
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
	}
	//오브젝트
	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (_tiles[i].obj == OBJ_NONE) continue;

		IMAGEMANAGER->frameRender("mapTiles", getMemDC(),
			_tiles[i].rc.left, _tiles[i].rc.top,
			_tiles[i].objFrameX, _tiles[i].objFrameY);
	}
	
	//TIMEMANAGER->render(getMemDC());
	//================================================================================
	//건들지마라 이거도
	this->getBackBuffer()->render(getHDC(), 0, 0);
	
}

void mainGame::setup(void)
{
	_btnSave = CreateWindow("button", "저장", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 500, 100, 30,
		_hWnd, HMENU(0), _hInstance, NULL);

	_btnLoad = CreateWindow("button", "불러오기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 500, 100, 30,
		_hWnd, HMENU(1), _hInstance, NULL);

	_btnTerrainDraw = CreateWindow("button", "지형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 700, 560, 100, 30,
		_hWnd, HMENU(2), _hInstance, NULL);

	_btnObjDraw = CreateWindow("button", "구조물", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 800, 560, 100, 30,
		_hWnd, HMENU(3), _hInstance, NULL);

	_btnEraser = CreateWindow("button", "지우개", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 900, 560, 100, 30,
		_hWnd, HMENU(4), _hInstance, NULL);

	_ctrSelect = CTRL_TERRAINDRAW;

	//샘플
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTiles[i * SAMPLETILEX + j].terrainFrameY = i;

			SetRect(&_sampleTiles[i * SAMPLETILEX + j].rcTile,
				(WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE,
				i * TILESIZE, (WINSIZEX - IMAGEMANAGER->findImage("mapTiles")->getWidth()) + j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	//타일
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i * TILEX + j].rc,
				j * TILESIZE,
				i * TILESIZE,
				j * TILESIZE + TILESIZE,
				i * TILESIZE + TILESIZE);
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = 1;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 0;
		_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}

}

void mainGame::setMap(void)
{
	//타일셋에서 정보받아오기
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++)
	{
		if (PtInRect(&_sampleTiles[i].rcTile, _ptMouse))
		{
			_currentTile.x = _sampleTiles[i].terrainFrameX;
			_currentTile.y = _sampleTiles[i].terrainFrameY;
			break;
		}
	}

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		if (PtInRect(&_tiles[i].rc, _ptMouse))
		{
			if (_ctrSelect == CTRL_TERRAINDRAW)
			{
				_tiles[i].terrainFrameX = _currentTile.x;
				_tiles[i].terrainFrameY = _currentTile.y;

				_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_OBJDRAW)
			{
				_tiles[i].objFrameX = _currentTile.x;
				_tiles[i].objFrameY = _currentTile.y;

				_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
			}
			else if (_ctrSelect == CTRL_ERASER)
			{
				_tiles[i].objFrameX = 0;
				_tiles[i].objFrameY = 0;
				
				_tiles[i].obj = OBJ_NONE;
			}
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}

void mainGame::save(void)
{
	char temp[128];
	vector<string> vStr;

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		vStr.push_back(itoa(_tiles[i].terrainFrameX, temp, 10));
		vStr.push_back(itoa(_tiles[i].terrainFrameY, temp, 10));
		vStr.push_back(itoa(_tiles[i].objFrameX, temp, 10));
		vStr.push_back(itoa(_tiles[i].objFrameY, temp, 10));
		vStr.push_back(itoa(int(_tiles[i].terrain), temp, 10));
		vStr.push_back(itoa(int(_tiles[i].obj), temp, 10));
	}

	/*vStr.push_back(itoa(_tiles[0].terrainFrameX, temp, 10));
	vStr.push_back(itoa(_tiles[0].terrainFrameY, temp, 10));*/

	TXTDATA->txtSave("TileMapSave.txt", vStr);
}


void mainGame::load(void)
{
	vector<string> vStr;

	vStr = TXTDATA->txtLoad("TilemapSave.txt");

	for (int i = 0; i < TILEX * TILEY; i++)
	{
		_tiles[i].terrainFrameX = (atoi(vStr[6 * i + 0].c_str()));
		_tiles[i].terrainFrameY = (atoi(vStr[6 * i + 1].c_str()));
		_tiles[i].objFrameX = (atoi(vStr[6 * i + 2].c_str()));
		_tiles[i].objFrameY = (atoi(vStr[6 * i + 3].c_str()));
		_tiles[i].terrain = (TERRAIN)(atoi(vStr[6 * i + 4].c_str()));
		_tiles[i].obj = (OBJECT)(atoi(vStr[6 * i + 5].c_str()));

	}
}


TERRAIN mainGame::terrainSelect(int frameX, int frameY)
{
	if (frameX == 1 && frameY == 0)
	{
		return TR_CEMENT;
	}
	else if (frameX == 2 && frameY == 0)
	{
		return TR_DESERT;
	}
	else if (frameX == 3 && frameY == 0)
	{
		return TR_GRASS;
	}
	else if (frameX == 4 && frameY == 0)
	{
		return TR_WATER;
	}
	
	return TR_CEMENT;
}

OBJECT mainGame::objSelect(int frameX, int frameY)
{
	if (frameX == 0 && frameY == 0)
	{
		return OBJ_TANK1;
	}
	else if (frameX == 0 && frameY == 8)
	{
		return OBJ_TANK2;
	}
	else if (frameX == 0 && frameY == 1)
	{
		return OBJ_BLOCK1;
	}
	else if (frameX == 0 && frameY == 2)
	{
		return OBJ_BLOCK1;
	}
	else if (frameX == 15 && frameY == 3)
	{
		return OBJ_BLOCK3;
	}
	else if (frameX == 4 && frameY == 2)
	{
		return OBJ_BLOCKS;
	}

	return OBJ_BLOCK1;
}
