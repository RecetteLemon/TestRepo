#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init()
{

	return S_OK;
}

void aStar::loadCurrentMap(void* iso)
{
	_currentMap = (tagIso***)iso;	
}

vector<aStarTile*> aStar::addOpenList(aStarTile* currentTile)
{
	int startX = currentTile->getIso().x / TILESIZEX - 1;
	int startY = currentTile->getIso().y / TILESIZEY - 1;
	int startZ = currentTile->getIso().z / TILESIZEZ - 1;


	for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) for (int k = 0; k < 3; ++k)
	{
		aStarTile* node = new aStarTile;

//		if (!node->getIsOpen()) continue;
//		if (node->getAttribute() == TR_START) continue;
//		if (node->getAttribute() == TR_WALL) continue;

		node->setIso(_currentMap[startX + k][startY + j][startZ + i]);

		bool addObj = true;

		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == node)
			{
				addObj = false;
				break;
			}
		}

		if (!addObj) continue;

		_vOpenList.push_back(node);
	}

	return _vOpenList;
}
void aStar::pathFinder(aStarTile* currentTile)
{
	float tempTotalCost = 5000;
	aStarTile* tempTile;

	for (int i = 0; i < addOpenList(currentTile).size(); i++)
	{
		_vOpenList[i]->setCostToGoal((abs(_endTile->getIdX() - _vOpenList[i]->getIdX())
			+ abs(_endTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		_vOpenList[i]->setCostFromStart(10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//���� ����� ���� �ָ� ����
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		//���¸���Ʈ�� ��� Ÿ���� ����Ÿ���̸�(���� ª�� ���̸�)
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				//addObj ����
				addObj = false;
				continue;
			}
		}

		_vOpenList[i]->setIsOpen(false);
		if (!addObj) continue;
		_vOpenList.push_back(tempTile);
	}

	if (addOpenList(currentTile).size() == NULL)
	{
		_vOpenList.clear();
		_vCloseList.clear();
		return;
	}

	//����Ÿ���� �Ӽ��� ���� -> ����������!
	if (tempTile->getIso().ter == TER_WALL)
	{
		_vMoveList.insert(_vMoveList.begin(), tempTile->getIso());
		//�̶����� ������ Ÿ���� ��ĥ�ض�
		while (_startTile->getParentNode() != NULL)
		{
			_vMoveList.insert(_vMoveList.begin(), _startTile->getIso());
			_startTile = _startTile->getParentNode();
		}
		return;
	}

	//����� Ÿ�� ��� ���Ϳ� ����Ÿ�� Ǫ�ù�
	_vCloseList.push_back(tempTile);

	//���¸���Ʈ�߿� ����� Ÿ���� ������ ����
	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}

	_startTile = tempTile;

	pathFinder(_startTile);
}

void aStar::release()
{

}


void aStar::update() 
{
	
}

void aStar::render() 
{
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		IMAGEMANAGER->findImage(L"isoTerrain")->frameRender(_currentMap[x][y][z].x - TILESIZEX / 2,
			_currentMap[x][y][z].y - _currentMap[x][y][z].z,
			_currentMap[x][y][z].terFrame.x, _currentMap[x][y][z].terFrame.y);
	}
	for (int z = 0; z < TILEZ; z++) for (int y = 0; y < TILEY; y++) for (int x = 0; x < TILEX; x++)
	{
		if (_currentMap[x][y][z].obj == OBJ_ERASE) continue;
		IMAGEMANAGER->findImage(L"isoObject")->frameRender(_currentMap[x][y][z].x - TILESIZEX / 2 - IMAGEMANAGER->findImage(L"isoObject")->getFrameWidth() + TILESIZEX,
			_currentMap[x][y][z].y - _currentMap[x][y][z].z - IMAGEMANAGER->findImage(L"isoObject")->getFrameHeight() + TILESIZEY,
			_currentMap[x][y][z].objFrame.x, _currentMap[x][y][z].objFrame.y);
	}
}