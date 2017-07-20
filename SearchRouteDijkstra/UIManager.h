#pragma once
#include <map>
#include "Singleton.h"
#include "UI/UIAtlas.h"
#include "UI/UIButton.h"
#include "UI/UIInputField.h"
#include "UI/UILabel.h"
#include "UI/UIProgressBar.h"
#include "UI/UIScrollBar.h"

#define UI UIManager::Instance()

class UIManager : public Singleton<UIManager>
{
	typedef map<int, UIBase*>				UIMap;
	typedef map<int, UIBase*>::iterator		UIMapIter;
	typedef map<int, UIAtlas*>				AtlasMap;
	typedef map<int, UIAtlas*>::iterator	AtlasMapIter;

	UIMap m_mapUI;
	AtlasMap m_mapAtlas;

	void AddUI(int id, UIBase* pUI) { m_mapUI[id] = pUI; }
	void AddAtlas(int id, UIAtlas* pAtlas) { m_mapAtlas[id] = pAtlas; }
	void RemoveUI(int id) { m_mapUI.erase(id); }
	void RemoveAtlas(int id) { m_mapAtlas.erase(id); }
	UIBase* GetUI(int id)
	{
		if (m_mapUI.find(id) == m_mapUI.end()) return NULL;
		return m_mapUI[id];
	}
	UIAtlas* GetAtlas(int id)
	{
		if (m_mapAtlas.find(id) == m_mapAtlas.end()) return NULL;
		return m_mapAtlas[id];
	}

public:
	void Init()
	{

	}

	void Release()
	{

	}

	void Update(float deltaTime)
	{
		for (UIMapIter it = m_mapUI.begin(); it != m_mapUI.end(); it++)
		{
			if ((*it).second->Show())
			{
				(*it).second->Update(deltaTime);
			}
		}
	}

	void Render()
	{
		for (UIMapIter it = m_mapUI.begin(); it != m_mapUI.end(); it++)
		{
			if ((*it).second->Show())
			{
				(*it).second->Render();
			}
		}
	}

	void Show(int id, bool show)
	{
		UIBase* pUI = GetUI(id);
		if (pUI != NULL) pUI->Show(show);
	}

	UIAtlas* Atlas(int id) { return GetAtlas(id); }
	UILabel* Label(int id) { return (UILabel*)GetUI(id); }
	UIButton* Button(int id) { return (UIButton*)GetUI(id); }
	UIScrollBar* ScrollBar(int id) { return (UIScrollBar*)GetUI(id); }
	UIInputField* InputField(int id) { return (UIInputField*)GetUI(id); }
	UIProgressBar* ProgressBar(int id) { return (UIProgressBar*)GetUI(id); }

	void DestroyUI(int id)
	{
		UIBase* pUI = GetUI(id);
		if (pUI != NULL)
		{
			RemoveUI(id);
			delete pUI;
		}
	}

	void DestroyAtlas(int id)
	{
		UIAtlas* pAtlas = GetAtlas(id);
		if (pAtlas != NULL)
		{
			RemoveAtlas(id);
			delete pAtlas;
		}
	}

	GSprite* CreateSprite(int atlasID, wstring spriteName)
	{
		UIAtlas* pAtlas = Atlas(atlasID);
		if (pAtlas != NULL) return pAtlas->NewSprite(spriteName);
		return NULL;
	}

	vector<GSprite*> CreateSprites(int atlasID)
	{
		UIAtlas* pAtlas = Atlas(atlasID);
		if (pAtlas != NULL) return pAtlas->NewSprites();
		return vector<GSprite*>();
	}

	UIAtlas* CreateAtlas(int id, wstring filePath)
	{
		UIAtlas* pAtlas = GetAtlas(id);
		if (pAtlas == NULL)
		{
			if (RENDER->LoadImageFile(filePath, filePath))
			{
				ID2D1Bitmap* pImage = RENDER->GetImage(filePath);
				wstring txtFilePath = filePath.substr(0, filePath.find_last_of('.')) + TEXT(".txt");
				pAtlas = new UIAtlas(pImage, txtFilePath);
				AddAtlas(id, pAtlas);
			}
		}
		return pAtlas;
	}

	UIButton* CreateButton(int id, Vector center, Vector size, ColorF color)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UIButton(center, size, color);
			AddUI(id, pUI);
		}
		return (UIButton*)pUI;
	}

	UIInputField* CreateInputField(int id, Vector center, Vector size, float fontSize,
		ColorF fontColor = ColorF::White, ColorF bgColor = ColorF::SlateGray)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UIInputField(center, size, fontSize, bgColor, fontColor);
			AddUI(id, pUI);
		}
		return (UIInputField*)pUI;
	}

	UILabel* CreateLabel(int id, Vector pos, float fontSize, ColorF color,
		Vector anchor = Vector(0.5f, 0.5f), TEXT_ALIGN align = TEXT_ALIGN_CENTER)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UILabel(pos, fontSize, color, anchor, align);
			AddUI(id, pUI);
		}
		return (UILabel*)pUI;
	}

	UIProgressBar* CreateProgressBar(int id, Vector center, Vector size,
		ColorF barColor = ColorF::DeepSkyBlue, ColorF frameColor = ColorF::SlateGray)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UIProgressBar(center, size, barColor, frameColor);
			AddUI(id, pUI);
		}
		return (UIProgressBar*)pUI;
	}

	UIScrollBar* CreateScrollBarH(int id, Vector center, Vector size,
		ColorF barColor = ColorF::DeepSkyBlue, ColorF frameColor = ColorF::SlateGray)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UIScrollBar(SCROLL_TYPE_H, center, size, frameColor, barColor);
			AddUI(id, pUI);
		}
		return (UIScrollBar*)pUI;
	}

	UIScrollBar* CreateScrollBarV(int id, Vector center, Vector size,
		ColorF barColor = ColorF::DeepSkyBlue, ColorF frameColor = ColorF::SlateGray)
	{
		UIBase* pUI = GetUI(id);
		if (pUI == NULL)
		{
			pUI = new UIScrollBar(SCROLL_TYPE_V, center, size, frameColor, barColor);
			AddUI(id, pUI);
		}
		return (UIScrollBar*)pUI;
	}
};