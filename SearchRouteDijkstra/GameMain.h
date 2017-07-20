#pragma once
#include "UIManager.h"
#include "Common.h"
#include "Grid.h"
#include "Graph.h"
#include "GraphSearch.h"

#define MAIN	GameMain::Instance()

class Player
{
	Grid* m_pGrid;
	Circle m_circle;
	float m_speed;

	vector<int> m_path;

public:
	Player(Grid* pGrid, Vector pos, float speed) : m_circle(pos, 10)
	{
		m_pGrid = pGrid;
		m_speed = speed;
	}

	int Index() { return m_pGrid->Index(m_circle.center); }
	void SetPath(vector<int> path) { m_path = path; }

	void Update(float deltaTime)
	{
		if (m_path.size() > 0)
		{
			Vector targetPos = m_pGrid->TilePos(m_path.back());
			m_circle.center = MATH->MoveForward(m_circle.center, targetPos, m_speed * deltaTime);

			if (m_circle.center == targetPos) m_path.pop_back();
		}
	}

	void Render()
	{
		RENDER->Draw(m_circle, ColorF::Cyan);

		if (m_path.size() > 0)
		{
			Vector fromPos = m_circle.center;
			for (int i = m_path.size() - 1; i >= 0; i--)
			{
				Vector toPos = m_pGrid->TilePos(m_path[i]);
				RENDER->DrawLine(fromPos, toPos, ColorF::Yellow, 3);
				fromPos = toPos;
			}
		}
	}
};

class GameMain : public Singleton<GameMain>
{
	Grid m_grid;
	Graph m_graph;

	Player m_player;

public:
	GameMain() :
		m_grid(Vector(10, 10), Vector(50, 50), ColorF::SlateGray, 10, 10),
		m_graph(m_grid.MaxCount()),
		m_player(&m_grid, m_grid.LeftTop(), 200)
	{
	}

	void Init()
	{
		for (int i = 0; i < m_graph.NodeCount(); i++)
		{
			m_graph.GetNode(i)->SetActive(true);
			m_graph.GetNode(i)->SetPos(m_grid.TilePos(i));

			// index -> col, row
			int x = i % m_grid.MaxCol();	// 열 번호
			int y = i / m_grid.MaxCol();	// 줄 번호

			AddEdge(i, x - 1, y + 0);
			AddEdge(i, x + 1, y + 0);
			AddEdge(i, x + 0, y - 1);
			AddEdge(i, x + 0, y + 1);
			AddEdge(i, x - 1, y - 1);
			AddEdge(i, x - 1, y + 1);
			AddEdge(i, x + 1, y - 1);
			AddEdge(i, x + 1, y + 1);
		}
	}

	void AddEdge(int from, int col, int row)
	{
		if (m_grid.IsValid(col, row))
		{
			int to = col + row * m_grid.MaxCol();
			Vector fromPos = m_grid.TilePos(from);
			Vector toPos = m_grid.TilePos(to);
			m_graph.AddEdge(from, to, (toPos - fromPos).Magnitude());
		}
	}

	void Release()
	{
		
	}

	void Update(float deltaTime)
	{
		Vector mousePos = INPUT->GetMousePos();

		if (INPUT->IsMouseDown(MOUSE_RIGHT))
		{
			int index = -1;
			if (m_grid.IsSelected(mousePos, &index))
			{
				GraphNode* pNode = m_graph.GetNode(index);
				pNode->SetActive(!pNode->Active());
			}
		}

		if (INPUT->IsMouseDown(MOUSE_LEFT))
		{
			int index = -1;
			if (m_grid.IsSelected(mousePos, &index))
			{
				GraphSearch_Dijkstra gs(&m_graph, m_player.Index(), index);
				if (gs.Search())
				{
					m_player.SetPath(gs.GetPath());
				}
			}
		}

		m_player.Update(deltaTime);
	}

	void Render()
	{
		m_grid.Render();
		m_graph.Render();
		m_player.Render();
	}
};