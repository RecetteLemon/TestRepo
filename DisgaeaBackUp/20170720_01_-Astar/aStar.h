#pragma once
#include "gameNode.h"
#include "mapToolScene.h"

class aStarTile
{
private:
	tagIso _iso;

	//f = g + h
	//f == totalCost
	//g == ���������� ���� ���(Ÿ��)���� ���
	//h == ���� ���(Ÿ��)���� �������� ���

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//�����ֳ�?!

	aStarTile* _parentNode;	//�������(������ �Ǵ�)
public:
	int getIdX(void) { return _iso.x / TILESIZEX; }
	int getIdY(void) { return _iso.y / TILESIZEY; }

//	POINT getCenter(void) { return _center; }

//	TERRAIN_TYPE getAttribute() { return _iso.ter; }

	// == getter, setter �Լ��� == //

	// ���̼� Ÿ��
	void setIso(tagIso iso) { _iso = iso; }
	tagIso getIso() { return _iso; }
	// ���� �ڽ�Ʈ
	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }
	// �������������� �ڽ�Ʈ
	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }
	// �������������� �ڽ�Ʈ
	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }
	// �θ� ���
	void setParentNode(aStarTile* t) { _parentNode = t; }
	aStarTile* getParentNode() { return _parentNode; }
	// ���� ����?
	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }
};

class aStar : public gameNode
{
private:
	// ã�� ���� ����
	vector<aStarTile*> _vOpenList;
	vector<aStarTile*>::iterator _viOpenList;

	// _vOpenList���� �� �ڽ�Ʈ�� ���� ������ ã�� ����
	vector<aStarTile*> _vCloseList;
	vector<aStarTile*>::iterator _viCloseList;

	// ĳ�������� �ѱ� ����
	vector<tagIso> _vMoveList;
	vector<tagIso>::iterator _viMoveList;

	// ���� ��
	tagIso*** _currentMap;

	aStarTile* _startTile;
	aStarTile* _endTile;
	aStarTile* _currentTile;
public:
	HRESULT init();

	//	inline void setStartPosition() { ; }
	void loadCurrentMap(void* iso);
	vector<aStarTile*> addOpenList(aStarTile* currentTile);					// �˻��� Ÿ�� ����
	void pathFinder(aStarTile* currentTile);								// Ÿ�� �˻�

	void release();
	void update();
	void render();

	aStar();
	~aStar();
};

