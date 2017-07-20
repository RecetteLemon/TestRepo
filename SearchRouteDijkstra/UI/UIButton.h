#pragma once
#include "UI/UIBase.h"

enum BUTTON_STATE
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_OVER,
	BUTTON_STATE_CLICK,
};

class UIButton : public UIBase
{
	const float SCALE_TIME = 0.1f;

	Box m_button;

	ColorF m_colorCurrent;
	ColorF m_colorNormal;
	ColorF m_colorOver;

	BUTTON_STATE m_state;
	Vector m_normalSize;
	Vector m_clickSize;
	float m_elapsedTime;

public:
	Event<UIButton*> onClick;

	UIButton(Vector center, Vector size, ColorF color) :
		m_button(center, size),
		m_colorCurrent(color),
		m_colorNormal(color),
		m_colorOver(color.r - 0.2f, color.g - 0.2f, color.b - 0.2f, color.a)
	{
		m_state = BUTTON_STATE_NONE;
		m_normalSize = size;
		m_clickSize = size * 0.9f;
		m_elapsedTime = 0.0f;
	}

	void Update(float deltaTime)
	{
		Vector mousePos = INPUT->GetMousePos();

		switch (m_state)
		{
		case BUTTON_STATE_NONE:
			if (MATH->IsCollided(mousePos, m_button))
			{
				m_state = BUTTON_STATE_OVER;
				m_colorCurrent = m_colorOver;
			}
			break;

		case BUTTON_STATE_OVER:
			if (!MATH->IsCollided(mousePos, m_button))
			{
				m_state = BUTTON_STATE_NONE;
				m_colorCurrent = m_colorNormal;
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = BUTTON_STATE_CLICK;
				m_elapsedTime = 0.0f;
			}
			break;

		case BUTTON_STATE_CLICK:
			m_elapsedTime += deltaTime;

			if (m_elapsedTime < SCALE_TIME)
			{
				m_button.size = MATH->Lerp(m_normalSize, m_clickSize, m_elapsedTime / SCALE_TIME);
			}
			else
			{
				m_button.size = MATH->Lerp(m_clickSize, m_normalSize, (m_elapsedTime - SCALE_TIME) / SCALE_TIME);
				if (m_button.size == m_normalSize)
				{
					m_state = BUTTON_STATE_NONE;
					m_colorCurrent = m_colorNormal;
					onClick.Execute(this);
				}
			}
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_button.center, m_button.size, m_colorCurrent);
		RENDER->DrawRect(m_button.center, m_button.size, ColorF(1, 1, 1, 0.3f), 3);
	}
};