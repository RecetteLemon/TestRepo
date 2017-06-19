#pragma once
#include "gameNode.h"
#include "starcraftScene.h"


class mainGame : public gameNode
{
private:
	starcraftScene* _starScene;
	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	

	mainGame();
	~mainGame();
};

