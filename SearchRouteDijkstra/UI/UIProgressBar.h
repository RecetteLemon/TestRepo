#pragma once
#include "UI/UIBase.h"

enum PROGRESS_STATE
{
	PROGRESS_STATE_NONE,
	PROGRESS_STATE_CHANGE,
	PROGRESS_STATE_DRAG,
};

class UIProgressBar : public UIBase
{
	Box m_bar;
	Box m_frame;

	ColorF m_colorMin;
	ColorF m_colorMax;
	ColorF m_colorBar;
	ColorF m_colorFrame;
	ColorF m_colorBg;

	PROGRESS_STATE m_state;
	float m_value;
	float m_targetValue;

	Vector m_originSize;
	Vector m_originLeftTop;

public:
	Event<UIProgressBar*> onChange;

	UIProgressBar(Vector center, Vector size, ColorF barColor, ColorF frameColor) :
		m_bar(center, size * 0.99f),
		m_frame(center, size),
		m_colorMin(barColor),
		m_colorMax(barColor),
		m_colorBar(barColor),
		m_colorFrame(frameColor),
		m_colorBg(ColorF::Black),
		m_value(1)
	{
		m_state = PROGRESS_STATE_NONE;
		m_originSize = m_bar.size;
		m_originLeftTop = m_bar.LeftTop();

		SetValue(0);
		SetTargetValue(0);
	}

	float GetValue() { return m_value; }

	void SetMinMaxColor(ColorF minColor, ColorF maxColor)
	{
		m_colorMin = minColor;
		m_colorMax = maxColor;
	}

	void SetValue(float value)
	{
		if (m_value == value) return;

		m_value = MATH->Clamp(value, 0.0f, 1.0f);
		m_bar.size.x = MATH->Lerp(0.0f, m_originSize.x, m_value);
		m_bar.SetLeftTop(m_originLeftTop);
		m_colorBar.r = MATH->Lerp(m_colorMin.r, m_colorMax.r, m_value);
		m_colorBar.g = MATH->Lerp(m_colorMin.g, m_colorMax.g, m_value);
		m_colorBar.b = MATH->Lerp(m_colorMin.b, m_colorMax.b, m_value);
		m_colorBar.a = MATH->Lerp(m_colorMin.a, m_colorMax.a, m_value);

		onChange.Execute(this);
	}

	void SetTargetValue(float value)
	{
		m_targetValue = MATH->Clamp(value, 0.0f, 1.0f);
	}

	void Update(float deltaTime)
	{
		Vector mousePos = INPUT->GetMousePos();

		switch (m_state)
		{
		case PROGRESS_STATE_NONE:
			if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (MATH->IsCollided(mousePos, m_frame))
				{
					m_state = PROGRESS_STATE_DRAG;
				}
			}
			else if (m_value != m_targetValue)
			{
				m_state = PROGRESS_STATE_CHANGE;
			}
			break;

		case PROGRESS_STATE_CHANGE:
			SetValue(MATH->MoveForward(m_value, m_targetValue, deltaTime));
			if (m_value == m_targetValue) m_state = PROGRESS_STATE_NONE;
			break;
			
		case PROGRESS_STATE_DRAG:
			SetTargetValue((mousePos.x - m_originLeftTop.x) / m_originSize.x);
			//SetValue(MATH->MoveForward(m_value, m_targetValue, deltaTime));
			SetValue(m_targetValue);
			if (INPUT->IsMouseUp(MOUSE_LEFT)) m_state = PROGRESS_STATE_NONE;
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_frame.center, m_frame.size, m_colorBg);
		RENDER->FillRect(m_bar.center, m_bar.size, m_colorBar);
		RENDER->DrawRect(m_bar.center, m_bar.size, ColorF(1, 1, 1, 0.3f), 3);
		RENDER->DrawRect(m_frame.center, m_frame.size, m_colorFrame, 3);
	}
};