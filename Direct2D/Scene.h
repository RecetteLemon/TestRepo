#pragma once
#include "GameNode.h"

class Scene : public GameNode
{
protected:
	Scene* self;
	Scene* parent;
	Scene* prev;
	Scene* next;

	Scene* childrenHead;
	Scene* childrenTail;
	Scene* current;

	BOOL isFocus;

public :
	virtual HRESULT Init(void);
	virtual void Release(void);
	virtual void Update(void);
	virtual void Render(void);

public:
	virtual void AddChild(Scene* node);
	virtual void AddChild(Scene* node, int order);
	virtual void RemoveChild(Scene* node);

	inline void SetSelf(Scene* node) { self = node; }
	inline Scene* GetSelf() { return self; }

	inline void SetChildrenHead(Scene* node) { childrenHead = node; }
	inline Scene* GetChildrenHead() { return childrenHead; }

	inline void SetChildrenTail(Scene* node) { childrenTail = node; }
	inline Scene* GetChildrenTail() { return childrenTail; }

	inline void SetParent(Scene* node) { parent = node; }
	inline Scene* GetParent() { return parent; }

	inline void SetPrev(Scene* node) { prev = node; }
	inline Scene* GetPrev() { return prev; }

	inline void SetNext(Scene* node) { next = node; }
	inline Scene* GetNext() { return next; }

	void SetIsFocus(BOOL focus) { isFocus = focus; }
	BOOL GetIsFocus() { return isFocus; }

	Scene();
	~Scene();
};

