#pragma once
#include "SingletonBase.h"

#define CAMERA_SPEED 10.0f * g_SpeedRatio


class Camera : public SingletonBase<Camera>
{
public:
	float posX;
	float posY;



public:
	HRESULT Init();
	HRESULT Init(float x, float y);
	void Release();
	void Update();
	void Render();
	void Move();


	Camera();
	~Camera();
};

