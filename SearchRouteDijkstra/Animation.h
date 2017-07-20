#pragma once
#include "UIManager.h"
using namespace std;

class Animation
{
	vector<GSprite*> m_sprites;
	Vector m_pos;
	float m_frameTime;
	float m_scale;

	unsigned int m_index;
	float m_elapsedTime;

public:
	Animation(Vector pos, int fps = 10, float scale = 1.0f)
	{
		m_pos = pos;
		m_index = 0;
		m_scale = scale;
		SetFPS(fps);
	}

	~Animation()
	{
		Clear();
	}

	void SetFPS(int fps) { m_frameTime = 1.0f / fps; }
	void SetScale(float scale) { m_scale = scale; }

	void Add(GSprite* pSprite)
	{
		if (pSprite != NULL) m_sprites.push_back(pSprite);
	}

	void Clear()
	{
		for (int i = 0; i < m_sprites.size(); i++)
		{
			delete m_sprites[i];
		}
		m_sprites.clear();
	}

	GSprite* CurrentSprite()
	{
		if (m_index < m_sprites.size()) return m_sprites[m_index];
		return NULL;
	}

	void Update(float deltaTime)
	{
		m_elapsedTime += deltaTime;
		if (m_elapsedTime > m_frameTime)
		{
			m_elapsedTime = 0;
			if (++m_index >= m_sprites.size()) m_index = 0;
		}
	}
	
	void Render()
	{
		GSprite* pCurrent = CurrentSprite();
		if (pCurrent != NULL)
		{
			pCurrent->SetPosition(m_pos);
			pCurrent->SetScale(m_scale);
			RENDER->Draw(pCurrent);
		}
	}
};