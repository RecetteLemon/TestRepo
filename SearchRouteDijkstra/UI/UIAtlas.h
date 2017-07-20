#pragma once
#include "RenderManager.h"
#include "Common.h"
#include <map>
using namespace std;

class UIAtlas
{
	typedef map<wstring, GSprite*>				SpriteMap;
	typedef map<wstring, GSprite*>::iterator	SpriteMapIter;

	ID2D1Bitmap* m_pImage;
	SpriteMap m_mapSprites;

public:
	UIAtlas(ID2D1Bitmap* pImage, wstring txtFilePath)
	{
		m_pImage = pImage;
		LoadTxtFile(txtFilePath);
	}

	GSprite* NewSprite(wstring name)
	{
		if (m_mapSprites.find(name) != m_mapSprites.end())
		{
			return new GSprite(*m_mapSprites[name]);
		}
		return NULL;
	}

	vector<GSprite*> NewSprites()
	{
		vector<GSprite*> sprites;
		for (SpriteMapIter it = m_mapSprites.begin(); it != m_mapSprites.end(); it++)
		{
			sprites.push_back(it->second);
		}
		return sprites;
	}

	void LoadTxtFile(wstring txtFileName)
	{
		wifstream fileIn(txtFileName);
		if (fileIn.is_open())
		{
			while (!fileIn.eof())
			{
				TCHAR text[100] = {};
				fileIn.getline(text, 100);

				vector<wstring> dataList = Util::Split(text, ' ');
				if (dataList.size() == 7)
				{
					wstring name = dataList[0];
					float posX = Util::ToFloat(dataList[1]);
					float posY = Util::ToFloat(dataList[2]);
					float sizeX = Util::ToFloat(dataList[3]);
					float sizeY = Util::ToFloat(dataList[4]);
					float anchorX = Util::ToFloat(dataList[5]);
					float anchorY = Util::ToFloat(dataList[6]);

					m_mapSprites[name] = new GSprite(m_pImage, Vector(posX, posY), Vector(sizeX, sizeY), Vector(anchorX, anchorY));
				}
			}
			fileIn.close();
		}
	}
};
