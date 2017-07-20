#pragma once
#include "Graph.h"
#include <vector>
#include <list>
#include <stack>
#include <queue>
using namespace std;

// Depth First Search (깊이 우선 탐색)
class GraphSearch_DFS
{
	Graph* m_pGraph;

	int m_source;
	int m_target;

	vector<bool> m_visit;
	vector<int> m_route;

public:
	GraphSearch_DFS(Graph* pGraph, int source, int target) :
		m_visit(pGraph->NodeCount(), false),
		m_route(pGraph->NodeCount(), -1)
	{
		m_pGraph = pGraph;
		m_source = source;
		m_target = target;
	}

	bool Search()
	{
		stack<GraphEdge*> edgeStack;

		GraphEdge dummy(m_source, m_source, 0);
		edgeStack.push(&dummy);

		while (edgeStack.size() > 0)
		{
			GraphEdge* pEdge = edgeStack.top();
			edgeStack.pop();

			m_visit[pEdge->To()] = true;
			m_route[pEdge->To()] = pEdge->From();

			if (pEdge->To() == m_target) return true;

			list<GraphEdge*> edgeList = m_pGraph->GetEdgeList(pEdge->To());
			list<GraphEdge*>::iterator it;
			for (it = edgeList.begin(); it != edgeList.end(); it++)
			{
				GraphNode* pNode = m_pGraph->GetNode((*it)->To());
				if (pNode->Active() && !m_visit[(*it)->To()])
				{
					edgeStack.push(*it);
				}
			}
		}
		return false;
	}

	vector<int> GetPath()
	{
		vector<int> result;
		result.push_back(m_target);

		int index = m_target;
		while (m_route[index] != m_source)
		{
			result.push_back(m_route[index]);
			index = m_route[index];
		}
		return result;
	}
};

// Breadth First Search (너비 우선 탐색)
class GraphSearch_BFS
{
	Graph* m_pGraph;

	int m_source;
	int m_target;

	vector<bool> m_visit;
	vector<int> m_route;

public:
	GraphSearch_BFS(Graph* pGraph, int source, int target) :
		m_visit(pGraph->NodeCount(), false),
		m_route(pGraph->NodeCount(), -1)
	{
		m_pGraph = pGraph;
		m_source = source;
		m_target = target;
	}

	bool Search()
	{
		queue<GraphEdge*> edgeQue;

		GraphEdge dummy(m_source, m_source, 0);
		edgeQue.push(&dummy);

		while (edgeQue.size() > 0)
		{
			GraphEdge* pEdge = edgeQue.front();
			edgeQue.pop();

			m_visit[pEdge->To()] = true;
			m_route[pEdge->To()] = pEdge->From();

			if (pEdge->To() == m_target) return true;

			list<GraphEdge*> edgeList = m_pGraph->GetEdgeList(pEdge->To());
			list<GraphEdge*>::iterator it;
			for (it = edgeList.begin(); it != edgeList.end(); it++)
			{
				GraphNode* pNode = m_pGraph->GetNode((*it)->To());
				if (pNode->Active() && !m_visit[(*it)->To()])
				{
					edgeQue.push(*it);
				}
			}
		}
		return false;
	}

	vector<int> GetPath()
	{
		vector<int> path;
		path.push_back(m_target);

		int index = m_target;
		while (m_route[index] != m_source)
		{
			path.push_back(m_route[index]);
			index = m_route[index];
		}
		return path;
	}
};

// Dijkstra (다익스트라)
class GraphSearch_Dijkstra
{
	Graph* m_pGraph;

	int m_source;
	int m_target;

	vector<float> m_cost;
	vector<bool> m_visit;
	vector<int> m_route;

public:
	GraphSearch_Dijkstra(Graph* pGraph, int source, int target) :
		m_cost(pGraph->NodeCount(), 9999999.9f),
		m_visit(pGraph->NodeCount(), false),
		m_route(pGraph->NodeCount(), -1)
	{
		m_pGraph = pGraph;
		m_source = source;
		m_target = target;
	}

	bool Search()
	{
		priority_queue<GraphEdge, vector<GraphEdge>, greater<GraphEdge>> edgeQue;

		GraphEdge dummy(m_source, m_source, 0);
		edgeQue.push(dummy);
		m_cost[m_source] = 0;

		while (edgeQue.size() > 0)
		{
			GraphEdge edge = edgeQue.top();
			edgeQue.pop();

			m_visit[edge.To()] = true;
			m_route[edge.To()] = edge.From();

			if (edge.To() == m_target) return true;

			list<GraphEdge*> edgeList = m_pGraph->GetEdgeList(edge.To());
			list<GraphEdge*>::iterator it;
			for (it = edgeList.begin(); it != edgeList.end(); it++)
			{
				GraphNode* pNode = m_pGraph->GetNode((*it)->To());
				if (pNode->Active() && !m_visit[(*it)->To()])
				{
					GraphEdge* pEdge = *it;
					int totalCost = m_cost[pEdge->From()] + pEdge->Cost();
					if (totalCost < m_cost[pEdge->To()])
					{
						m_cost[pEdge->To()] = totalCost;
						edgeQue.push(GraphEdge(pEdge->From(), pEdge->To(), totalCost));
					}
				}
			}
		}
		return false;
	}

	vector<int> GetPath()
	{
		vector<int> path;
		path.push_back(m_target);

		int index = m_target;
		while (m_route[index] != m_source)
		{
			path.push_back(m_route[index]);
			index = m_route[index];
		}
		return path;
	}
};