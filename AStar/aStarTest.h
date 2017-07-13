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
	//��ü Ÿ���� ����
	vector<tile*> _vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ����
	vector<tile*> _vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ����
	vector<tile*> _vCloseList;
	vector<tile*>::iterator _viCloseList;

	tile* _startTile;		//����Ÿ�� Cost From Start
	tile* _endTile;			//�� Ÿ��	Cost To Goal
	tile* _currentTile;		//���� ��� (Ÿ��)

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
