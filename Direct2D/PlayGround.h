#pragma once
#include "GameNode.h"

class PlayGround : public GameNode
{
private:
	
	int _x, _y, _count;

public:
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);
	
	PlayGround();
	~PlayGround();
};

