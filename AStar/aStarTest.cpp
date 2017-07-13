#include "stdafx.h"
#include "aStarTest.h"


aStarTest::aStarTest()
{
}


aStarTest::~aStarTest()
{
}

HRESULT aStarTest::init()
{
	//타일셋팅
	setTiles();

	_start = _count = 0;

	return S_OK;
}

void aStarTest::setTiles()
{
	_startTile = new tile;
	_startTile->init(4, 12);
	_startTile->setAttribute("start");

	_endTile = new tile;
	_endTile->init(20, 12);
	_endTile->setAttribute("end");

	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; i++)
	{
		for (int j = 0; j < TILENUMX; j++)
		{
			if (j == _startTile->getIdX() && i == _startTile->getIdY())
			{
				_startTile->setColor(RGB(0, 255, 255));
				_vTotalList.push_back(_startTile);
				continue;
			}

			if (j == _endTile->getIdX() && i == _endTile->getIdY())
			{
				_endTile->setColor(RGB(10, 120, 55));
				_vTotalList.push_back(_endTile);
				continue;
			}

			tile* node = new tile;
			node->init(j, i);
			_vTotalList.push_back(node);
		}
	}
}

vector<tile*> aStarTest::addOpenList(tile* currentTile)
{
	int startX = currentTile->getIdX() - 1;
	int startY = currentTile->getIdY() - 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			tile* node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			node->setParentNode(_currentTile);

			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == node)
				{
					addObj = false;
					break;
				}
			}

			if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));

			if (!addObj) continue;

			_vOpenList.push_back(node);
		}
	}
	return _vOpenList;
}

void aStarTest::pathFinder(tile* currentTile)
{
	float tempTotalCost = 5000;
	tile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX())
			+ abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() +
			_vOpenList[i]->getCostFromStart());

		//가장 비용이 작은 애를 색출
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	//템프타일의 속성이 엔드 -> 도착했으면!
	if (tempTile->getAttribute() == "end")
	{
		//이때까지 지나온 타일을 색칠해라
		while (_currentTile->getParentNode() != NULL)
		{
			_currentTile->setColor(RGB(22, 14, 128));
			_currentTile = _currentTile->getParentNode();
		}

		return;
	}

	_vCloseList.push_back(tempTile);

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_currentTile = tempTile;

	pathFinder(_currentTile);
	

}

void aStarTest::release()
{

}

void aStarTest::update()
{
	//if (_start)
	//{
	//	_count++;
	//
	//	if (_count % 10 == 0)
	//	{
	//		pathFinder(_currentTile);
	//		_count = 0;
	//	}
	//}


	if (KEYMANAGER->isOnceKeyDown('S')) pathFinder(_currentTile);

	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < _vTotalList.size(); i++)
		{
			if (PtInRect(&_vTotalList[i]->getRect(), _ptMouse))
			{
				if (_vTotalList[i]->getAttribute() == "start") continue;
				if (_vTotalList[i]->getAttribute() == "end") continue;

				_vTotalList[i]->setIsOpen(false);
				_vTotalList[i]->setAttribute("wall");
				_vTotalList[i]->setColor(RGB(230, 140, 200));
				break;
			}
		}
	}

	
	this->ControlEndTile();
	_startTile->update();
	_endTile->update();
}

void aStarTest::render()
{
	for (int i = 0; i < _vTotalList.size(); i++)
	{
		_vTotalList[i]->render();
	}
}


void aStarTest::ControlEndTile()
{
	POINT point;

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		point = { _endTile->getCenter().x + TILEWIDTH,  _endTile->getCenter().y };
		_endTile->setCenter(point);
		_endTile->setIdX(_endTile->getIdX() + 1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		point = { _endTile->getCenter().x - TILEWIDTH,  _endTile->getCenter().y };
		_endTile->setCenter(point);
		_endTile->setIdX(_endTile->getIdX() - 1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		point = { _endTile->getCenter().x,  _endTile->getCenter().y - TILEHEIGHT };
		_endTile->setCenter(point);
		_endTile->setIdY(_endTile->getIdY() - 1);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		point = { _endTile->getCenter().x,  _endTile->getCenter().y + TILEHEIGHT };
		_endTile->setCenter(point);
		_endTile->setIdY(_endTile->getIdY() + 1);
	}
}