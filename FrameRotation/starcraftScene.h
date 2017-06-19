#pragma once
#include "gameNode.h"
#include "ship.h"

class battle;

class starcraftScene : public gameNode
{
private:
	ship* _battle;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	starcraftScene();
	~starcraftScene();
};

