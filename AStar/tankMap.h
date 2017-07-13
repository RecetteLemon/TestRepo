#pragma once
#include "tileNode.h"
#include "gameNode.h"

class tankMap : public gameNode
{
private:
	tagTile _tiles[TILEX * TILEY];		//Ÿ��
	DWORD _attribute[TILEX * TILEY];	//���� �Ӽ�

	int _pos[2];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load();

	tagTile* getTile() { return _tiles; }
	DWORD* getAttribute() { return _attribute; }

	//�Ӽ� ������

	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }

	tankMap();
	~tankMap();
};

