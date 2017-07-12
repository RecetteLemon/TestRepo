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
	
	this->tankControl();
	this->tankMove();
}

void tank::render()	
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top);
}

void tank::tankControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = DIRECTION_RIGHT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = DIRECTION_LEFT;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = DIRECTION_UP;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = DIRECTION_DOWN;
	}
	else
	{
		_direction = DIRECTION_STOP;
	}
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

		case DIRECTION_STOP:
			break;
	}

	RECT temp;
	rcCollision = RectMakeCenter(_x, _y, _image->getFrameWidth() - 10, _image->getFrameHeight() - 10);
	tileX = (int)((_x - _image->getFrameWidth() / 2) / TILESIZE);
	tileY = (int)((_y - _image->getFrameWidth() / 2) / TILESIZE);
	switch (_direction)
	{
	case DIRECTION_LEFT:
		tileIndex[0] = tileX + TILEX * tileY;
		tileIndex[1] = tileX + TILEX * (tileY + 1);
		if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
			{
				_x = _tankMap->getTile()[tileIndex[0]].rc.right + (rcCollision.right - rcCollision.left) / 2;
			}
		}
		else if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
			{
				_x = _tankMap->getTile()[tileIndex[0]].rc.right + (rcCollision.right - rcCollision.left) / 2;
			}
		}

		/*if (isCollision(rcCollision, _tankMap->getTile()[tileIndex[0]].rc))
		{
			if (!isCollision(rcCollision, _tankMap->getTile()[tileIndex[0]].rc))
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
				{
					_x = _tankMap->getTile()[tileIndex[0]].rc.right + (rcCollision.right - rcCollision.left) / 2;
				}
			}
			else
			{
				if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || 
					_tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
				{
					_x = _tankMap->getTile()[tileIndex[0]].rc.right + (rcCollision.right - rcCollision.left) / 2;
				}
			}
		}*/
		break;
	case DIRECTION_RIGHT:
		tileIndex[0] = tileX + TILEX * tileY + 1;
		tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
		if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
			{
				_x = _tankMap->getTile()[tileIndex[0]].rc.left - (rcCollision.right - rcCollision.left) / 2;
			}
		}
		else if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
			{
				_x = _tankMap->getTile()[tileIndex[0]].rc.left - (rcCollision.right - rcCollision.left) / 2;
			}
		}
		break;
	case DIRECTION_UP:
		tileIndex[0] = tileX + TILEX * tileY;
		tileIndex[1] = tileX + TILEX * tileY + 1;
		if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
			{
				_y = _tankMap->getTile()[tileIndex[0]].rc.bottom + (rcCollision.right - rcCollision.left) / 2;
			}
		}
		else if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
			{
				_y = _tankMap->getTile()[tileIndex[0]].rc.bottom + (rcCollision.right - rcCollision.left) / 2;
			}
		}
		break;
	case DIRECTION_DOWN:
		tileIndex[0] = tileX + TILEX * (tileY + 1);
		tileIndex[1] = tileX + TILEX * (tileY + 1) + 1;
		if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && !IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE)
			{
				_y = _tankMap->getTile()[tileIndex[0]].rc.top - (rcCollision.right - rcCollision.left) / 2;
			}
		}
		else if (IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[0]].rc) && IntersectRect(&temp, &rcCollision, &_tankMap->getTile()[tileIndex[1]].rc))
		{
			if (_tankMap->getAttribute()[tileIndex[0]] == ATTR_UNMOVE || _tankMap->getAttribute()[tileIndex[1]] == ATTR_UNMOVE)
			{
				_y = _tankMap->getTile()[tileIndex[0]].rc.top - (rcCollision.right - rcCollision.left) / 2;
			}
		}
		break;
	}

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

}


void tank::setTankPosition()
{
	_rc = _tankMap->getTile()[_tankMap->getPosFirst()].rc;

	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
}
