#pragma once
#include "gameNode.h"
#include <string>

class tile : public gameNode
{
private:
	int _idX;
	int _idY;

	POINT _center;
	RECT _rc;

	//f = g + h
	//f == totalCost
	//g == 시작점부터 현재 노드(타일)까지 비용
	//h == 현재 노드(타일)부터 끝점까지 비용

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//갈수있나?!

	tile* _parentNode;	//상위노드(갱신이 되는)

	COLORREF _color;
	HBRUSH	_brush;
	HPEN	_pen;

	string _attribute;

public:
	tile();
	~tile();

	HRESULT init(int idX, int idY);
	void release(void);
	void update(void);
	void render(void);

	int getIdX(void) { return _idX; }
	int getIdY(void) { return _idY; }

	void setIdX(int x) { _idX = x; }
	void setIdY(int y) { _idY = y; }

	void setColor(COLORREF color)
	{
		DeleteObject(_brush);
		_color = color;
		_brush = CreateSolidBrush(_color);
	}

	RECT getRect() { return _rc; }

	void setCenter(POINT center) { _center = center; }
	POINT getCenter(void) { return _center; }

	void setAttribute(string str) { _attribute = str; }
	string getAttribute() { return _attribute; }

	void setTotalCost(float totalCost) { _totalCost = totalCost; }
	float getTotalCost() { return _totalCost; }

	void setCostFromStart(float costFromStart) { _costFromStart = costFromStart; }
	float getCostFromStart() { return _costFromStart; }

	void setCostToGoal(float costToGoal) { _costToGoal = costToGoal; }
	float getCostToGoal() { return _costToGoal; }

	void setParentNode(tile* t) { _parentNode = t; }
	tile* getParentNode() { return _parentNode; }

	void setIsOpen(bool isOpen) { _isOpen = isOpen; }
	bool getIsOpen(void) { return _isOpen; }

};

