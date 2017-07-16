#pragma once
#include "SingletonBase.h"
#include <vector>
#include <string>

class TxtData : public SingletonBase<TxtData>
{
private:

public:
	HRESULT Init();
	void Release();

	//세이브 
	void TxtSave(const char* saveFileName, vector<string> vStr);
	char* VectorArrayCombine(vector<string> vArray);

	//로드
	vector<string> TxtLoad(const char* loadFileName);
	vector<string> CharArraySeparation(char charArray[]);

	TxtData();
	~TxtData();
};

