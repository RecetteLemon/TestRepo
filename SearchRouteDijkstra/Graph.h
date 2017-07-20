#pragma once
#include "RenderManager.h"
#include "Common.h"

class GraphNode
{
	bool m_active;
	int m_id;
	Vector m_pos;

public:
	GraphNode(int id) : m_id(id) {}

	bool Active() { return m_active; }
	int Id() { return m_id; }
	Vector Pos() { return m_pos; }
	void SetActive(bool active) { m_active = active; }
	void SetPos(Vector pos) { m_pos = pos; }
};

class GraphEdge
{
	int m_from;
	int m_to;
	float m_cost;

public:
	GraphEdge(int from, int to, float cost) : m_from(from), m_to(to), m_cost(cost) {}

	void SetCost(float cost) { m_cost = cost; }

	int From() { return m_from; }
	int To() { return m_to; }
	float Cost() { return m_cost; }

	bool operator > (const GraphEdge& edge) const { return m_cost > edge.m_cost; }
	bool operator < (const GraphEdge& edge) const { return m_cost < edge.m_cost; }
};

class Graph
{
	typedef vector<GraphNode*>			NodeVector;
	typedef list<GraphEdge*>			EdgeList;
	typedef list<GraphEdge*>::iterator	EdgeListIter;
	typedef vector<EdgeList>			EdgeListVector;

	NodeVector m_nodes;
	EdgeListVector m_edges;

public:
	Graph(int nodeCount)
	{
		for (int i = 0; i < nodeCount; i++)
		{
			m_nodes.push_back(new GraphNode(i));
		}

		for (int i = 0; i < nodeCount; i++)
		{
			m_edges.push_back(list<GraphEdge*>());
		}
	}

	~Graph()
	{
		for (int i = 0; i < m_nodes.size(); i++) { delete m_nodes[i]; }
		m_nodes.clear();

		for (int i = 0; i < m_edges.size(); i++)
		{
			for (EdgeListIter it = m_edges[i].begin(); it != m_edges[i].end(); it++)
			{
				delete *it;
			}
			m_edges[i].clear();
		}
		m_edges.clear();
	}

	int NodeCount() { return m_nodes.size(); }

	bool IsValid(int nodeIndex)
	{
		return nodeIndex >= 0 && nodeIndex < NodeCount();
	}

	GraphNode* GetNode(int index)
	{
		if (IsValid(index)) return m_nodes[index];
		return NULL;
	}

	EdgeList GetEdgeList(int index)
	{
		if (IsValid(index)) { return m_edges[index]; }
		return EdgeList();
	}

	GraphEdge* GetEdge(int from, int to)
	{
		EdgeList list = GetEdgeList(from);
		for (EdgeListIter it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->To() == to) { return *it; }
		}
		return NULL;
	}

	void AddEdge(int from, int to, float cost = 0)
	{
		if (IsValid(from) && IsValid(to))
		{
			m_edges[from].push_back(new GraphEdge(from, to, cost));
		}
	}

	void RemoveEdge(int from, int to)
	{
		EdgeList list = GetEdgeList(from);
		for (EdgeListIter it = list.begin(); it != list.end(); it++)
		{
			if ((*it)->To() == to) { it = list.erase(it); break; }
		}
	}

	void Render()
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i]->Active())
			{
				RENDER->FillCircle(m_nodes[i]->Pos(), 5, ColorF::Green);

				EdgeList list = GetEdgeList(i);
				for (EdgeListIter it = list.begin(); it != list.end(); it++)
				{
					GraphNode* pFromNode = GetNode((*it)->From());
					GraphNode* pToNode = GetNode((*it)->To());
					if (pToNode->Active())
					{
						RENDER->DrawLine(pFromNode->Pos(), pToNode->Pos(), ColorF::Green);
					}
				}
			}
		}
	}
};