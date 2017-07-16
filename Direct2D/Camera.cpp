#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}



HRESULT Camera::Init()
{
	posX = posY = 0.0f;

	return S_OK;
}

HRESULT Camera::Init(float x, float y)
{
	posX = x;
	posY = y;

	return S_OK;
}



void Camera::Release()
{

}

void Camera::Update()
{
	if (KEYMANAGER->IsStayKeyDown(VK_RIGHT) && posX + WINSIZEX < MAPSIZEX)
	{
		posX += (CAMERA_SPEED);
		if (posX + WINSIZEX > MAPSIZEX)
			posX = MAPSIZEX - WINSIZEX;
	}
	if (KEYMANAGER->IsStayKeyDown(VK_LEFT) && posX > 0)
	{
		posX -= CAMERA_SPEED;
		if (posX < 0)
			posX = 0;
	}


	if (KEYMANAGER->IsStayKeyDown(VK_DOWN) && posY + WINSIZEY < MAPSIZEY)
	{
		posY += CAMERA_SPEED;
		if (posY + WINSIZEY > MAPSIZEY)
			posY = MAPSIZEY - WINSIZEY;
	}

	if (KEYMANAGER->IsStayKeyDown(VK_UP) && posY > 0)
	{
		posY -= CAMERA_SPEED;
		if (posY < 0)
			posY = 0;
	}
}


void Camera::Render()
{

}

void Camera::Move()
{

}