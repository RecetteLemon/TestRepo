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
	//g == ���������� ���� ���(Ÿ��)���� ���
	//h == ���� ���(Ÿ��)���� �������� ���

	float _totalCost;
	float _costFromStart;
	float _costToGoal;

	bool _isOpen;	//�����ֳ�?!

	tile* _parentNode;	//�������(������ �Ǵ�)

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

