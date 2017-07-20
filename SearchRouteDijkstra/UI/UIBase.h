#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "WindowManager.h"
#include "Common.h"

class UIBase
{
	bool m_show;

public:
	UIBase()
	{
		m_show = true;
	}

	bool Show() { return m_show; }
	void Show(bool show) { m_show = show; }

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};