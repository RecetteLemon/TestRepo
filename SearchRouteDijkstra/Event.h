#pragma once
#include <functional>
#include <list>
using namespace std;

template <typename T>
class Event
{
	typedef typename function<void(T)>		Handler;
	typedef typename list<Handler>				HandlerList;
	typedef typename list<Handler>::iterator	HandlerListIter;

	HandlerList m_handlers;

public:
	template <typename OBJ>
	void Add(OBJ* pObj, void(OBJ::*pFunc)(T))
	{
		m_handlers.push_back(bind1st(mem_fun(pFunc), pObj));
	}

	void Clear()
	{
		m_handlers.clear();
	}

	void Execute(T param)
	{
		for (HandlerListIter it = m_handlers.begin(); it != m_handlers.end(); it++)
		{
			(*it)(param);
		}
	}
};