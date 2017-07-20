#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "Common.h"

enum SELECTION_STATE
{
	SELECTION_STATE_NONE,
	SELECTION_STATE_MOVE,
	SELECTION_STATE_EDIT_L,
	SELECTION_STATE_EDIT_R,
	SELECTION_STATE_EDIT_T,
	SELECTION_STATE_EDIT_D,
};

class Selection
{
	const float BOX_MIN_SIZE = 20.0f;
	const float HANDLE_SIZE = 3.0f;

	Box m_box;
	Circle m_handleLeft;
	Circle m_handleRight;
	Circle m_handleTop;
	Circle m_handleDown;
	SELECTION_STATE m_state;

	wstring m_name;
	bool m_active;
	float m_scale;
	Vector m_anchor;

public:
	Selection(wstring name, Vector pos, Vector size, float scale) :
		m_box(Vector(), Vector(BOX_MIN_SIZE, BOX_MIN_SIZE)),
		m_handleLeft(Vector(), HANDLE_SIZE),
		m_handleRight(Vector(), HANDLE_SIZE),
		m_handleTop(Vector(), HANDLE_SIZE),
		m_handleDown(Vector(), HANDLE_SIZE)
	{
		m_state = SELECTION_STATE_NONE;
		m_name = name;
		m_active = false;
		m_anchor = Vector(0.5f, 0.5f);
		m_scale = scale;
		SetLeftTop(pos);
		SetSize(size);
	}

	void SetName(wstring name) { m_name = name; }
	void SetActive(bool active) { m_active = active; }
	void SetState(SELECTION_STATE state) { m_state = state; }
	void SetAnchor(Vector anchor) { m_anchor = anchor; }
	void SetLeftTop(Vector pos)
	{
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;
		m_box.SetLeftTop(pos);
		m_handleLeft.center = m_box.Left();
		m_handleRight.center = m_box.Right();
		m_handleTop.center = m_box.Top();
		m_handleDown.center = m_box.Down();
	}
	void SetSize(Vector size)
	{
		Vector leftTop = m_box.LeftTop();
		size.x = MATH->Max(size.x, BOX_MIN_SIZE);
		size.y = MATH->Max(size.y, BOX_MIN_SIZE);
		m_box.size = size;
		SetLeftTop(leftTop);
	}
	void SetScale(float scale)
	{
		Vector leftTop = m_box.LeftTop() / m_scale * scale;
		m_box.size = m_box.size / m_scale * scale;
		m_scale = scale;
		SetLeftTop(leftTop);
	}

	void AddPos(Vector addedPos) { SetLeftTop(m_box.LeftTop() + addedPos); }
	void AddSize(Vector addedSize) { SetSize(m_box.size + addedSize); }
	void AddAnchor(Vector addedAnchor)
	{
		m_anchor += addedAnchor;
		m_anchor.x = MATH->Clamp(m_anchor.x, 0, 1);
		m_anchor.y = MATH->Clamp(m_anchor.y, 0, 1);
	}

	bool GetActive() { return m_active; }
	wstring GetName() { return m_name; }
	Vector GetLeftTop() { return m_box.LeftTop(); }
	Vector GetSize() { return m_box.size; }
	Vector GetAnchor() { return m_anchor; }
	Box GetBox() { return m_box; }

	bool IsSelected(Vector point)
	{
		if (m_active)
		{
			if (MATH->IsCollided(point, m_handleLeft)) return true;
			if (MATH->IsCollided(point, m_handleRight)) return true;
			if (MATH->IsCollided(point, m_handleTop)) return true;
			if (MATH->IsCollided(point, m_handleDown)) return true;
		}
		return MATH->IsCollided(point, m_box);
	}

	void Update(float deltaTime)
	{
		if (!m_active) return;

		// 키 입력시 처리
		if (INPUT->IsKeyPress(VK_LEFT))
		{
			if (INPUT->IsKeyPress(VK_SHIFT)) AddSize(Vector::Left());
			else if (INPUT->IsKeyPress(VK_CONTROL)) AddAnchor(Vector(-0.01f, 0.0f));
			else AddPos(Vector::Left());
		}
		if (INPUT->IsKeyPress(VK_RIGHT))
		{
			if (INPUT->IsKeyPress(VK_SHIFT)) AddSize(Vector::Right());
			else if (INPUT->IsKeyPress(VK_CONTROL)) AddAnchor(Vector(0.01f, 0.0f));
			else AddPos(Vector::Right());
		}
		if (INPUT->IsKeyPress(VK_UP))
		{
			if (INPUT->IsKeyPress(VK_SHIFT)) AddSize(Vector::Up());
			else if (INPUT->IsKeyPress(VK_CONTROL)) AddAnchor(Vector(0.0f, -0.01f));
			else AddPos(Vector::Up());
		}
		if (INPUT->IsKeyPress(VK_DOWN))
		{
			if (INPUT->IsKeyPress(VK_SHIFT)) AddSize(Vector::Down());
			else if (INPUT->IsKeyPress(VK_CONTROL)) AddAnchor(Vector(0.0f, 0.01f));
			else AddPos(Vector::Down());
		}

		// 마우스 입력시 처리
		Vector mousePos = INPUT->GetMousePos();
		Vector mouseDelta = INPUT->GetMouseDelta();

		switch (m_state)
		{
		case SELECTION_STATE_NONE:
			if (INPUT->IsMouseDown(MOUSE_LEFT))
			{
				if (MATH->IsCollided(mousePos, m_handleLeft))  m_state = SELECTION_STATE_EDIT_L;
				else if (MATH->IsCollided(mousePos, m_handleRight)) m_state = SELECTION_STATE_EDIT_R;
				else if (MATH->IsCollided(mousePos, m_handleTop)) m_state = SELECTION_STATE_EDIT_T;
				else if (MATH->IsCollided(mousePos, m_handleDown)) m_state = SELECTION_STATE_EDIT_D;
				else if (MATH->IsCollided(mousePos, m_box)) m_state = SELECTION_STATE_MOVE;
			}
			break;

		case SELECTION_STATE_MOVE:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				AddPos(mouseDelta);
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SELECTION_STATE_NONE;
			}
			break;

		case SELECTION_STATE_EDIT_L:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				AddPos(Vector(mouseDelta.x, 0));
				AddSize(Vector(-mouseDelta.x, 0));
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SELECTION_STATE_NONE;
			}
			break;

		case SELECTION_STATE_EDIT_R:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				AddSize(Vector(mouseDelta.x, 0));
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SELECTION_STATE_NONE;
			}
			break;

		case SELECTION_STATE_EDIT_T:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				AddPos(Vector(0, mouseDelta.y));
				AddSize(Vector(0, -mouseDelta.y));
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SELECTION_STATE_NONE;
			}
			break;

		case SELECTION_STATE_EDIT_D:
			if (INPUT->IsMouseDrag(MOUSE_LEFT))
			{
				AddSize(Vector(0, mouseDelta.y));
			}
			else if (INPUT->IsMouseUp(MOUSE_LEFT))
			{
				m_state = SELECTION_STATE_NONE;
			}
			break;
		}
	}

	void Draw()
	{
		ColorF activateColor = (m_active) ? ColorF::Red : ColorF::Green;
		RENDER->DrawRect(m_box.center, m_box.size, activateColor);
		RENDER->DrawCircle(m_box.LeftTop() + m_box.size * m_anchor, HANDLE_SIZE, ColorF::OrangeRed, 2);

		if (m_active)
		{
			RENDER->Draw(m_handleLeft, ColorF::DeepSkyBlue);
			RENDER->Draw(m_handleRight, ColorF::DeepSkyBlue);
			RENDER->Draw(m_handleTop, ColorF::DeepSkyBlue);
			RENDER->Draw(m_handleDown, ColorF::DeepSkyBlue);
		}
	}
};