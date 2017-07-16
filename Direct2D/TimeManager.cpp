#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
	: _timer(NULL)
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::Init(void)
{
	_timer = new Timer;
	_timer->Init();


	return S_OK;
}

void TimeManager::Release(void)
{
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}

}

void TimeManager::Update(float lock)
{
	if (_timer != NULL)
	{
		_timer->Tick(lock);
	}
}

void TimeManager::Render()
{
	WCHAR str[256];
	string strFrame;

	
#ifdef _DEBUG
	if (_timer != NULL)
	{
		//FPS
		swprintf(str, L"FPS : %d", _timer->GetFrameRate());
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"¸¼Àº°íµñ", 18.0f, str, CAMERA->posX, CAMERA->posY,
			CAMERA->posX + 200, CAMERA->posY + 20);

		//¿ùµåÅ¸ÀÓ
		swprintf(str, L"worldTime : %f", _timer->GetWorldTime());
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"¸¼Àº°íµñ", 18.0f, str, CAMERA->posX, CAMERA->posY + 20,
			CAMERA->posX + 200, CAMERA->posY + 40);

		//°»½Å tick
		swprintf(str, L"elapsedTime : %f", _timer->GetElapsedTime());
		D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"¸¼Àº°íµñ", 18.0f, str, CAMERA->posX, CAMERA->posY + 40,
			CAMERA->posX + 200, CAMERA->posY + 60);
	}
#else
	{
		if (_timer != NULL)
		{
			swprintf(str, L"FPS : %d", _timer->GetFrameRate());
			D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, str, CAMERA->posX, CAMERA->posY,
				CAMERA->posX + 200, CAMERA->posY + 20);
		}
	}
#endif
}
