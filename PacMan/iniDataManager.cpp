#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{

}

HRESULT iniDataManager::init()
{

	return S_OK;
}

void iniDataManager::release()
{

}


//저장
void iniDataManager::addData(const char* subject, const char* title, const char* body)
{
	//데이터 입력받아서
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	//벡터에 담고
	vIniData.push_back(iniData);
	//그 정보를 한 곳에 취합
	_vIniData.push_back(vIniData);

}

void iniDataManager::iniSave(char* fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();
}


//로드
char* iniDataManager::loadDataString(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[65] = { NULL };
	GetPrivateProfileString(subject, title, "", data, 64, str);

	return data;
}

int iniDataManager::loadDataInterger(const char* fileName, const char* subject, const char* title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);
	
	return GetPrivateProfileInt(subject, title, 0, str);
}

