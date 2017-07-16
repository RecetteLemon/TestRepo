#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}


HRESULT Scene::Init(void)
{
	self = nullptr;
	parent = nullptr;
	prev = nullptr;
	next = nullptr;
	current = nullptr;
	childrenHead = nullptr;
	childrenTail = nullptr;
	SetSelf(this);

	isFocus = false;

	return S_OK;
}

void Scene::Release(void)
{
	current = childrenHead;
	Scene* temp;
	while (current != nullptr)
	{
		temp = current->GetNext();
		current->Release();
		SAFE_DELETE(current);
		current = childrenHead = temp;
	}
}

void Scene::Update(void)
{
	Scene* current = childrenHead;
	while (current != nullptr)
	{
		current->Update();
		current = current->GetNext();
	}
}

void Scene::Render(void)
{
	Scene* current = childrenHead;

	while (current != nullptr)
	{
		current->Render();
		current = current->GetNext();
	}
}

void Scene::AddChild(Scene* node)
{
	if (childrenHead == nullptr)
	{
		node->SetParent(this);
		SetChildrenHead(node);
		SetChildrenTail(nullptr);
	}
	else
	{
		current = childrenHead;

		while (current->GetNext() != nullptr)
		{
			current = current->GetNext();
		}

		node->SetParent(this);
		node->SetPrev(current);
		current->SetNext(node);
		node->SetNext(nullptr);
		childrenTail = node;
	}
}

void Scene::AddChild(Scene* node, int order)
{

}
void Scene::RemoveChild(Scene* node)
{
	int count = 0;
	current = childrenHead;
	Scene* _prev = nullptr;

	while (current != nullptr)
	{
		if (current == node)
		{
			if (count != 0)
			{
				_prev->SetNext(current->GetNext());
				if (current->GetNext() != nullptr) current->GetNext()->SetPrev(_prev);
				else childrenTail = current;
			}
			else
			{
				childrenHead = current->GetNext();
				if (childrenHead != nullptr) childrenHead->SetPrev(nullptr);
			}
			current->Release();
			SAFE_DELETE(current);
			break;
		}
		_prev = current;
		current = current->GetNext();
		count++;
	}
}