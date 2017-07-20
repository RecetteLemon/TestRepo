#pragma once
#include "UI/UILabel.h"

enum FIELD_STATE
{
	FIELD_STATE_NONE,
	FIELD_STATE_SELECT,
};

class UIInputField : public UIBase
{
	wstring m_text;
	Box m_frame;
	ColorF m_bgColor;
	FIELD_STATE m_state;

	UILabel m_label;

public:
	Event<UIInputField*> onChange;
	Event<UIInputField*> onEnter;

	UIInputField(Vector center, Vector size, float fontSize, ColorF bgColor, ColorF fontColor) :
		m_frame(center, size),
		m_bgColor(bgColor),
		m_label(center, fontSize, fontColor)
	{
		m_state = FIELD_STATE_NONE;
		WINDOW->onChar.Add(this, &UIInputField::OnChar);
	}
	
	~UIInputField()
	{
		WINDOW->onChar.Clear();
	}

	wstring GetText() { return m_text; }
	void SetText(wstring text)
	{
		m_text = text;
		m_label.SetText(text);
		onChange.Execute(this);
	}

	void Update(float deltaTime)
	{
		Vector mousePos = INPUT->GetMousePos();
		switch (m_state)
		{
		case FIELD_STATE_NONE:
			if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (MATH->IsCollided(mousePos, m_frame))
				{
					m_state = FIELD_STATE_SELECT;
				}
			}
			break;

		case FIELD_STATE_SELECT:
			if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (!MATH->IsCollided(mousePos, m_frame))
				{
					m_state = FIELD_STATE_NONE;
				}
			}
			else if (INPUT->IsKeyDown(VK_RETURN))
			{
				m_state = FIELD_STATE_NONE;
				onEnter.Execute(this);
			}
			else if (INPUT->IsKeyDown(VK_DELETE))
			{
				m_text.clear();
				m_label.SetText(m_text);
				onChange.Execute(this);
			}
			break;
		}
	}

	void Render()
	{
		RENDER->FillRect(m_frame.center, m_frame.size, m_bgColor);
		RENDER->DrawRect(m_frame.center, m_frame.size, ColorF(1, 1, 1, 0.5f));
		if (m_state == FIELD_STATE_SELECT)
		{
			RENDER->DrawRect(m_frame.center, m_frame.size, ColorF(1, 1, 1, 0.5f), 3);
		}
		m_label.Render();
	}

	void OnChar(TCHAR c)
	{
		if (m_state == FIELD_STATE_NONE) return;
		if (c == VK_RETURN) return;

		if (c == VK_BACK)
		{
			if (m_text.length() > 0) m_text.pop_back();
		}
		else
		{
			if (m_label.GetBox().size.x < m_frame.size.x)
			{
				m_text.push_back(c);
			}
		}

		m_label.SetText(m_text);
		onChange.Execute(this);
	}
};