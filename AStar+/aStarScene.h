#pragma once
#include "gameNode.h"
#include "aStarTest.h"

class aStarScene : public gameNode
{
private:
	aStarTest* _ast;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	aStarScene();
	~aStarScene();
};

