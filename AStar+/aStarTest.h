#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>

#define TILEWIDTH 32
#define TILEHEIGHT 32

#define TILENUMX ((int)(WINSIZEX / TILEWIDTH))
#define TILENUMY ((int)(WINSIZEY / TILEHEIGHT))

class aStarTest : public gameNode
{
private:
	//전체 타일을 담을
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 길을 담을
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 빠른 길을 담을
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//시작타일 Cost From Start
	tile* _endTile;			//끝 타일	Cost To Goal
	tile* _currentTile;		//현재 노드 (타일)

	int _count;
	bool _start;

public:
	aStarTest();
	~aStarTest();

	HRESULT init();
	
	void setTiles();
	vector<tile*> addOpenList(tile* currentTile);
	void pathFinder(tile* currentTile);
	
	void release();
	void update();
	void render();


	void ControlEndTile();
};

