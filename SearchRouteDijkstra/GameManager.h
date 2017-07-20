#pragma once
#include "Common.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "GameMain.h"
#include "UIManager.h"

#define GAME GameManager::Instance()

class GameManager : public Singleton<GameManager>
{
	float m_frameTime;			// �� �����Ӵ� �ð�(Second)
	int m_currentTime;			// ���� �������� �ð�(MilliSecond)
	int m_prevTime;				// ���� �������� �ð�(MilliSecond)

public:
	void Init()
	{
		m_frameTime = 1.0f / (float)FPS;
		m_currentTime = timeGetTime();
		m_prevTime = timeGetTime();

		WINDOW->RegisterData(TEXT("Main"), CS_HREDRAW | CS_VREDRAW, RGB(255, 255, 255));
		WINDOW->Create(WND_MAIN, TEXT("Main"), TEXT("MainWindow"), 0, 0, VIEW_WIDTH, VIEW_HEIGHT);
		WINDOW->onPaint.Add(this, &GameManager::OnPaint);

		INPUT->Init(WINDOW->GetHandle(WND_MAIN));
		RENDER->Init(WINDOW->GetHandle(WND_MAIN));
		UI->Init();
		MAIN->Init();
	}

	void Release()
	{
		WINDOW->onPaint.Clear();
		MAIN->Release();
		UI->Release();
		RENDER->Release();
		INPUT->Release();
		WINDOW->Destroy(WND_MAIN);
	}

	void Update()
	{
		m_currentTime = timeGetTime();
		float deltaTime = (m_currentTime - m_prevTime) * 0.001f;	// ���� �� ������ �ð�
		
		if (deltaTime >= m_frameTime)
		{
			m_prevTime = m_currentTime;
			INPUT->Update();
			UI->Update(deltaTime);
			MAIN->Update(deltaTime);

			InvalidateRect(WINDOW->GetHandle(WND_MAIN), NULL, false);
		}
	}

	void OnPaint(HDC hdc)
	{
		MAIN->Render();
		UI->Render();
		RENDER->Render();
	}
};