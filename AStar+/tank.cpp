#include "stdafx.h"
#include "tank.h"


tank::tank()
{
}


tank::~tank()
{

}

HRESULT tank::init()
{
	_direction = DIRECTION_RIGHT;

	_image = IMAGEMANAGER->addFrameImage("tank", "tank.bmp", 0, 0, 256, 128, 8, 4, true, RGB(255, 0, 255));

	_speed = 100.0f;

	return S_OK;
}

void tank::release()
{

}

void tank::update()	
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = DIRECTION_RIGHT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = DIRECTION_LEFT;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = DIRECTION_UP;
		tankMove();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = DIRECTION_DOWN;
		tankMove();
	}

}

void tank::render()	
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}


void tank::tankMove()
{
	//타일(렉트) 검출용 렉트를 하나 둔다
	RECT rcCollision;

	//타일 검출할때는 타일인덱스 2개면 충분!
	int tileIndex[2];
	int tileX, tileY;

	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;

	switch (_direction)
	{
		case DIRECTION_LEFT:
			_image->setFrameX(0);
			_image->setFrameY(3);

			_x -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_RIGHT:
			_image->setFrameX(0);
			_image->setFrameY(2);

			_x += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_UP:
			_image->setFrameX(0);
			_image->setFrameY(0);

			_y -= moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case DIRECTION_DOWN:
			_image->setFrameX(0);
			_image->setFrameY(1);

			_y += moveSpeed;

			rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	rcCollision.left += 2;
	rcCollision.top += 2;
	rcCollision.right -= 2;
	rcCollision.bottom -= 2;

	tileX = rcCollision.left / TILESIZE;
	tileY = rcCollision.top / TILESIZE;

	switch (_direction)
	{
		case DIRECTION_LEFT:
			tileIndex[0] = tileX + TILEX * tileY;
			tileIndex[1] = tileX + TILEX * (tileY + 1);
		break;
		case DIRECTION_RIGHT:
			tileIndex[0] = tileX + TILEX * tileY + 1;
			tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
		break;
		case DIRECTION_UP:
			tileIndex[0] = tileX + TILEX * tileY;
			tileIndex[1] = tileX + TILEX * (tileY + 1);
		break;
		case DIRECTION_DOWN:
			tileIndex[0] = tileX + TILEX * (tileY + 1);
			tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
		break;
	}

	//if밤에 잠이안와 -> 시프트 연산자 & 비트 연산자
	//else밤에 잠이온다 -> 자
	for (int i = 0; i < 2; i++)
	{
		RECT rc;
		if (((_tankMap->getAttribute()[tileIndex[i]] & ATTR_UNMOVE) == ATTR_UNMOVE) &&
			IntersectRect(&rc, &_tankMap->getTile()[tileIndex[i]].rc, &rcCollision))
		{
			switch (_direction)
			{
				case DIRECTION_LEFT:
					_rc.left = _tankMap->getTile()[tileIndex[i]].rc.right;
					_rc.right = _rc.left + 30;

					_x = _rc.left + (_rc.right - _rc.left) / 2;

				break;
				case DIRECTION_RIGHT:
					_rc.right = _tankMap->getTile()[tileIndex[i]].rc.left;
					_rc.left = _rc.right - 30;

					_x = _rc.left + (_rc.right - _rc.left) / 2;
				break;
				case DIRECTION_UP:
					_rc.top = _tankMap->getTile()[tileIndex[i]].rc.bottom;
					_rc.bottom = _rc.top + 30;

					_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
				case DIRECTION_DOWN:
					_rc.bottom = _tankMap->getTile()[tileIndex[i]].rc.top;
					_rc.top = _rc.bottom - 30;

					_y = _rc.top + (_rc.bottom - _rc.top) / 2;
				break;
			}
			return;
		}
	}

	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
	_rc = rcCollision;
}


void tank::setTankPosition()
{
	_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
