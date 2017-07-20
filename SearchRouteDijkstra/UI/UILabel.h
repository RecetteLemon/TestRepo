#pragma once
#include "UI/UIBase.h"

class UILabel : public UIBase
{
	wstring m_text;
	Vector m_pos;
	Vector m_anchor;
	float m_fontSize;
	ColorF m_color;
	TEXT_ALIGN m_align;

	Box m_box;

	float m_timeLife;
	float m_timeLifeMax;
	float m_timeFadeIn;
	float m_timeFadeInMax;
	float m_timeFadeOut;
	float m_timeFadeOutMax;

	float m_floatingFadeIn;
	float m_floatingFadeOut;

public:
	Event<UILabel*> onLifeTimeUpdate;
	Event<UILabel*> onLifeTimeComplate;
	Event<UILabel*> onFadeInUpdate;
	Event<UILabel*> onFadeInComplate;
	Event<UILabel*> onFadeOutUpdate;
	Event<UILabel*> onFadeOutComplate;

	UILabel(Vector pos, float fontSize, ColorF color, Vector anchor = Vector(0.5f, 0.5f), TEXT_ALIGN align = TEXT_ALIGN_CENTER) :
		m_box(pos, Vector()),
		m_color(color)
	{
		m_pos = pos;
		m_anchor = anchor;
		m_fontSize = fontSize;
		m_align = align;

		m_timeLife = 0;
		m_timeLifeMax = 1;
		m_timeFadeIn = 0;
		m_timeFadeInMax = 1;
		m_timeFadeOut = 0;
		m_timeFadeOutMax = 1;
		m_floatingFadeIn = 0;
		m_floatingFadeOut = 0;
	}

	Box GetBox() { return m_box; }
	ColorF GetColor() { return m_color; }
	float GetFadeInRate() { return 1 - (m_timeFadeIn / m_timeFadeInMax); }
	float GetFadeOutRate() { return 1 - (m_timeFadeOut / m_timeFadeOutMax); }
	float GetLifeTimeRate() { return 1 - (m_timeLife / m_timeLifeMax); }

	void SetText(wstring text)
	{
		m_text = text;
		FixLabelSize();
		FixLabelPos();
	}
	void SetFontSize(float fontSize)
	{
		m_fontSize = fontSize;
		FixLabelSize();
		FixLabelPos();
	}
	void SetColor(ColorF color) { m_color = color; }
	void SetAlign(TEXT_ALIGN align) { m_align = align; }
	void SetFadeInFloating(float floating) { m_floatingFadeIn = floating; }
	void SetFadeOutFloating(float floating) { m_floatingFadeOut = floating; }
	void SetLifeTime(float lifeTime)
	{
		m_timeLife = lifeTime;
		if (lifeTime > 0) m_timeLifeMax = lifeTime;
		FixLabelPos();
	}
	void SetFadeTime(float fadeInTime, float fadeOutTime)
	{
		m_timeFadeIn = fadeInTime;
		m_timeFadeOut = fadeOutTime;
		if (fadeInTime > 0) m_timeFadeInMax = fadeInTime;
		if (fadeOutTime > 0) m_timeFadeOutMax = fadeOutTime;
		FixLabelPos();
	}

	void FixLabelSize()
	{
		int row = 1;
		int col = 0;
		int maxCol = 0;

		for (int i = 0; i < m_text.length(); i++)
		{
			if (m_text[i] == '\n') { row++; col = 0; }
			else
			{
				col++;
				if (col > maxCol) maxCol = col;
			}
		}

		m_box.size = Vector(m_fontSize * maxCol, m_fontSize * row * 1.15f);
	}

	void FixLabelPos()
	{
		m_box.SetLeftTop(m_pos - Vector(m_box.size.x * m_anchor.x, m_box.size.y * m_anchor.y));
	}

	void Update(float deltaTime)
	{
		if (m_timeFadeIn > 0) Update_FadeInState(deltaTime);
		else if (m_timeLife > 0) Update_LifeTimeState(deltaTime);
		else if (m_timeFadeOut > 0) Update_FadeOutState(deltaTime);
	}

	void Render()
	{
		//RENDER->Draw(m_box, ColorF::Green, 2);
		RENDER->Draw(m_text, m_box.LeftTop(), m_box.size, m_fontSize, m_color, m_align);
	}

	void Update_FadeInState(float deltaTime)
	{
		m_timeFadeIn -= deltaTime;
		float t = GetFadeInRate();
		m_color.a = MATH->Lerp(0, 1, t);
		m_box.center.y = MATH->Lerp(m_pos.y, m_pos.y + m_floatingFadeIn, t);
		onFadeInUpdate.Execute(this);

		if (m_timeFadeIn <= 0) onFadeInComplate.Execute(this);
	}

	void Update_FadeOutState(float deltaTime)
	{
		m_timeFadeOut -= deltaTime;
		float t = GetFadeOutRate();
		m_color.a = MATH->Lerp(1, 0, t);
		m_box.center.y = MATH->Lerp(m_pos.y, m_pos.y + m_floatingFadeOut, t);
		onFadeOutUpdate.Execute(this);

		if (m_timeFadeOut <= 0) onFadeOutComplate.Execute(this);
	}

	void Update_LifeTimeState(float deltaTime)
	{
		m_timeLife -= deltaTime;
		m_color.a = 1;
		onLifeTimeUpdate.Execute(this);
		
		if (m_timeLife <= 0)
		{
			if (m_timeFadeOut <= 0) m_color.a = 0;
			onLifeTimeComplate.Execute(this);
		}
	}
};