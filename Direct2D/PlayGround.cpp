#include "stdafx.h"
#include "PlayGround.h"


PlayGround::PlayGround()
{
}


PlayGround::~PlayGround()
{
}


HRESULT PlayGround::Init(void)
{
	GameNode::Init(true);
	
	IMAGEMANAGER->AddImage("Apple", L"test.png", 250, 250);
	
	IMAGEMANAGER->AddFrameImage("yuki", L"UraYukiHime_StandRight.png", 10879, 357, 43, 1);


	//씬 등록
	_count = _x = _y = 0;


	//씬 체인지
	


	
	return S_OK;
}

void PlayGround::Release(void)
{
	GameNode::Release();
	
}

void PlayGround::Update(void)
{
	g_SpeedRatio = 60.0f / TIMEMANAGER->GetFrameRate();
	
	if (_count % 3 == 0)
	{

		if (IMAGEMANAGER->FindImage("yuki")->GetFrameX() >= IMAGEMANAGER->FindImage("yuki")->GetMaxFrameX())
		{
			_x = 0;
			IMAGEMANAGER->FindImage("yuki")->SetFrameX(_x);
		}
		else
		{
			_x++;
			IMAGEMANAGER->FindImage("yuki")->SetFrameX(_x);
		}
	}


	_count++;
	CAMERA->Update();
	SCENEMANAGER->Update();
	//FADE->Update();

}


void PlayGround::Render(void)
{
	// Draw 시작 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->BeginDraw();
	
	//===========================================================================
	//				##		여기에 코드 작성(Start)		##


	IMAGEMANAGER->Render("Apple", WINSIZEX / 2, WINSIZEY / 2, 0.1f);
	IMAGEMANAGER->FrameRender("yuki", 100, 100, _x, 0, 1.0f);


	SCENEMANAGER->Render();
		
	
	
	//				##		여기에 코드 작성(End)		##
	//===========================================================================


	//시간 정보 출력
	TIMEMANAGER->Render();

	//카메라 정보 출력
	WCHAR str[128];
	swprintf(str, L"cameraX : %.1f / %.1f", CAMERA->posX, (float)(MAPSIZEX - WINSIZEX));
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, CAMERA->posX, CAMERA->posY + 20,
		CAMERA->posX + 300, CAMERA->posY + 40);

	swprintf(str, L"cameraY : %.1f / %.1f", CAMERA->posY, (float)(MAPSIZEY - WINSIZEY));
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"나눔고딕", 17.0f, str, CAMERA->posX, CAMERA->posY + 40,
		CAMERA->posX + 300, CAMERA->posY + 60);

	//마우스 위치 출력
	/*
	swprintf(str, L"mouseX : %.2f", (float)g_ptMouse.x);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"맑은고딕", 15.0f, str, CAMERA->posX + WINSIZEX - 200, CAMERA->posY + 40,
		CAMERA->posX + WINSIZEX, CAMERA->posY + 60);
	swprintf(str, L"mouseY : %.2f", (float)g_ptMouse.y);
	D2DMANAGER->DrawTextD2D(D2DMANAGER->defaultBrush, L"맑은고딕", 15.0f, str, CAMERA->posX + WINSIZEX - 200, CAMERA->posY + 60,
		CAMERA->posX + WINSIZEX, CAMERA->posY + 80);
	*/
	


	// Draw 끝 - 이 코드가 빠지면 D2D 출력 X
	D2DMANAGER->EndDraw();
}

