#include "stdafx.h"
#include "Database.h"


Database::Database()
{
}


Database::~Database()
{
}

HRESULT Database::Init(void)
{
	LoadDatabase("Database.txt");

	return S_OK;
}

void Database::Release(void)
{

}

void Database::LoadDatabase(string name)
{
	arrElements vTemp;
	vTemp = TXTDATA->TxtLoad(name.c_str());

	string str;
	int count = 0;

	for (int i = 0; i < vTemp.size(); i++)
	{
		if (vTemp[i] == "|")
		{
			Elements* em = new Elements;
			str = vTemp[i + 1];
			_mTotalElement.insert(pair<string, Elements*>(vTemp[i + 1], em));
			if (i != 0) count += 7;
			continue;
		}

		iterElement mIter = _mTotalElement.find(str);

		/*
		if (i == count + 1) mIter->second->name = vTemp[i].c_str();
		else if (i == count + 2) mIter->second->currentHP = (int)atoi(vTemp[i].c_str());
		else if (i == count + 3) mIter->second->maxHP = (int)atoi(vTemp[i].c_str());
		else if (i == count + 4) mIter->second->angle = (float)atof(vTemp[i].c_str());
		else if (i == count + 5) mIter->second->accelaration = (float)atof(vTemp[i].c_str());
		else if (i == count + 6) mIter->second->maxSpeed = (float)atof(vTemp[i].c_str());
		*/
	}

	vTemp.clear();
}

//¼³Á¤ÀÚ

/*
void Database::SetElementDataCurrentHP(string str, float ch)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->currentHP = ch;
}

void Database::SetElementDataMaxHP(string str, float mh)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->maxHP = mh;
}

void Database::setElementDataAngle(string str, float a)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->angle = a;
}

void Database::setElementDataAcceleration(string str, float ac)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->accelaration = ac;
}

void Database::setElementDataMaxSpeed(string str, float ms)
{
	iterElement mIter = _mTotalElement.find(str);
	mIter->second->maxSpeed = ms;
}
*/