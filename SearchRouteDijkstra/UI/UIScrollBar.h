#pragma once
#include "UI/UIBase.h"

enum SCROLL_TYPE
{
	SCROLL_TYPE_H,
	SCROLL_TYPE_V,
};

enum SCROLL_STATE
{
	SCROLL_STATE_NONE,
	SCROLL_STATE_DRAG,
	SCROLL_STATE_MOVE,
};

class UIScrollBar : public UIBase
{
	SCROLL_TYPE m_type;
	SCROLL_STATE m_state;
	Box m_frame;
	Box m_bar;

	ColorF m_colorFrame;
	ColorF m_colorBar;

	float m_value;
	Vector m_targetPos;

public:
	Event<UIScrollBar*> onChange;

	UIScrollBar(SCROLL_TYPE type, Vector center, Vector frameSize, ColorF frameColor, ColorF barColor) :
		m_frame(center, frameSize),
		m_bar(center, frameSize),
		m_colorFrame(frameColor),
		m_colorBar(barColor)
	{
		m_type = type;
		m_state = SCROLL_STATE_NONE;
		SetBarScale((type == SCROLL_TYPE_H) ? Vector(0.1f, 1.5f) : Vector(1.5f, 0.1f));
		SetValue(-1);
	}

	float GetValue() { return m_value; }

	void SetValue(float value)
	{
		if (m_value != value)
		{
			m_value = MATH->Clamp(value, 0.0f, 1.0f);
			SetBarPos(value);
			onChange.Execute(this);
		}
	}

	void SetBarScale(Vector scale)
	{
		m_bar.size = Vector(m_frame.size.x * scale.x, m_frame.size.y * scale.y);
	}

	void SetBarPos(Vector pos)
	{
		float value = 0;
		switch (m_type)
		{
			case SCROLL_TYPE_H:
			{
				float minPosX = m_frame.LeftTop().x + m_bar.size.x * 0.5f;
				float maxPosX = m_frame.RightBottom().x - m_bar.size.x * 0.5f;
				m_bar.center.x = MATH->Clamp(pos.x, minPosX, maxPosX);
				value = (pos.x - minPosX) / (maxPosX - minPosX);
			}
			break;

			case SCROLL_TYPE_V:
			{
				float minPosY = m_frame.LeftTop().y + m_bar.size.y * 0.5f;
				float maxPosY = m_frame.RightBottom().y - m_bar.size.y * 0.5f;
				m_bar.center.y = MATH->Clamp(pos.y, minPosY, maxPosY);
				value = (pos.y - minPosY) / (maxPosY - minPosY);
			}
			break;
		}

		SetValue(value);
	}

	void SetBarPos(float value)
	{
		switch (m_type)
		{
			case SCROLL_TYPE_H:
			{
				float minPosX = m_frame.LeftTop().x + m_bar.size.x * 0.5f;
				float maxPosX = m_frame.RightBottom().x - m_bar.size.x * 0.5f;
				m_bar.center.x = MATH->Lerp(minPosX, maxPosX, value);
			}
			break;

			case SCROLL_TYPE_V:
			{
				float minPosY = m_frame.LeftTop().y + m_bar.size.y * 0.5f;
				float maxPosY = m_frame.RightBottom().y - m_bar.size.y * 0.5f;
				m_bar.center.y = MATH->Lerp(minPosY, maxPosY, value);
			}
			break;
		}
	}

	void Update(float deltaTime)
	{
		Vector mousePos = INPUT->GetMousePos();
		Vector mouseDelta = INPUT->GetMouseDelta();

		switch (m_state)
		{
		case SCROLL_STATE_NONE:
			if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (MATH->IsCollided(mousePos, m_bar))
				{
					m_state = SCROLL_STATE_DRAG;
				}
				else if (MATH->IsCollided(mousePos, m_frame))
				{
					m_state = SCROLL_STATE_MOVE;
					m_targetPos = mousePos;
				}
			}
			break;

		case SCROLL_STATE_DRAG:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				SetBarPos(m_bar.center + mouseDelta);
			}
			if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SCROLL_STATE_NONE;
			}
			break;

		case SCROLL_STATE_MOVE:
			Vector prevPos = m_bar.center;
			float speed = (m_type == SCROLL_TYPE_H) ? m_frame.size.x * 2 : m_frame.size.y * 2;
			SetBarPos(MATH->MoveForward(m_bar.center, m_targetPos, speed * deltaTime));

			if (MATH->SqrDistance(prevPos, m_bar.center) < EPSILON)
			{
				m_state = SCROLL_STATE_NONE;
			}
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_frame.center, m_frame.size, m_colorFrame);
		RENDER->DrawRect(m_frame.center, m_frame.size, ColorF(1, 1, 1, 0.5f));
		RENDER->FillRect(m_bar.center, m_bar.size, m_colorBar);
		RENDER->DrawRect(m_bar.center, m_bar.size, ColorF(1, 1, 1, 0.5f));
	}
};