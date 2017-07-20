#pragma once
#include "RenderManager.h"
#include "InputManager.h"
#include "Common.h"

class Grid
{
	Vector m_leftTop;
	Vector m_tileSize;
	Vector m_dirX;
	Vector m_dirY;

	int m_col;
	int m_row;

	ColorF m_color;

public:
	Grid(Vector leftTop, Vector tileSize, ColorF color, int col = 1, int row = 1) : m_color(color)
	{
		m_leftTop = leftTop;
		m_tileSize = tileSize;
		m_dirX = Vector::Right();
		m_dirY = Vector::Down();
		m_col = col;
		m_row = row;
	}

	bool IsValid(int col, int row)
	{
		return col >= 0 && col < MaxCol() && row >= 0 && row < MaxRow();
	}
	bool IsValid(int index)
	{
		return index >= 0 && index < MaxCount();
	}

	void SetTileSize(Vector tileSize) { m_tileSize = tileSize; }
	void SetColumn(int col) { m_col = MATH->Max(1, col); }
	void SetRow(int row) { m_row = MATH->Max(1, row); }
	void SetColor(ColorF color) { m_color = color; }
	void SetRotationX(float angle) { m_dirX = MATH->ToDirection(angle); }
	void SetRotationY(float angle) { m_dirY = MATH->ToDirection(MATH->ToAngle(m_dirX) + angle); }
	void AddPos(Vector pos) { m_leftTop += pos; }

	int Index(Vector pos)
	{
		int col = (pos.x - LeftTop().x) / TileSize().x;
		int row = (pos.y - LeftTop().y) / TileSize().y;
		if (IsValid(col, row)) return col + row * MaxCol();
		return -1;
	}
	int MaxCol() { return MATH->Max(1, m_col); }
	int MaxRow() { return MATH->Max(1, m_row); }
	int MaxCount() { return MaxCol() * MaxRow(); }
	Vector Size() { return Vector(m_tileSize.x * MaxCol(), m_tileSize.y * MaxRow()); }
	Vector DirX() { return m_dirX; }
	Vector DirY() { return m_dirY; }
	Vector Width() { return DirX() * Size().x; }
	Vector Height() { return DirY() * Size().y; }
	Vector LeftTop() { return m_leftTop; }
	Vector LeftBottom() { return LeftTop() + Height(); }
	Vector RightTop() { return LeftTop() + Width(); }
	Vector RightBottom() { return LeftTop() + Width() + Height(); }
	Vector Center() { return LeftTop() + Width() * 0.5f + Height() * 0.5f; }
	Vector TileSize() { return m_tileSize; }
	Vector TilePos(int col, int row, Vector anchor = Vector(0.5f, 0.5f))
	{
		return LeftTop() + DirX() * TileSize().x * (col + anchor.x) + DirY() * TileSize().y * (row + anchor.y);
	}
	Vector TilePos(int index, Vector anchor = Vector(0.5f, 0.5f))
	{
		return TilePos(index % MaxCol(), index / MaxCol(), anchor);
	}

	bool IsSelected(Vector point, int* selectedIndex)
	{
		Vector collidedPoint;
		if (MATH->IsCollided(Line(point, point + Height()), Line(LeftBottom(), RightBottom()), &collidedPoint))
		{
			int x = (collidedPoint - LeftBottom()).Magnitude() / TileSize().x;
			if (MATH->IsCollided(Line(point, point + Width()), Line(RightTop(), RightBottom()), &collidedPoint))
			{
				int y = (collidedPoint - RightTop()).Magnitude() / TileSize().y;
				*selectedIndex = x + y * MaxCol();
				return true;
			}
		}
		return false;
	}

	void Update(float deltaTime)
	{
	}

	void Render()
	{
		float rateX = 1.0f / MaxCol();
		for (int i = 0; i <= MaxCol(); i++)
		{
			Vector startPoint = LeftTop() + Width() * rateX * i;
			Vector endPoint = LeftBottom() + Width() * rateX * i;
			RENDER->DrawLine(startPoint, endPoint, m_color, 2);
		}

		float rateY = 1.0f / MaxRow();
		for (int i = 0; i <= MaxRow(); i++)
		{
			Vector startPoint = LeftTop() + Height() * rateY * i;
			Vector endPoint = RightTop() + Height() * rateY * i;
			RENDER->DrawLine(startPoint, endPoint, m_color, 2);
		}
	}
};