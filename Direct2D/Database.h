#pragma once
#include "SingletonBase.h"
#include <vector>
#include <map>

class Elements
{
public:
	const char* name;
	/*
	int currentHP;
	int maxHP;
	float angle;
	float accelaration;
	float maxSpeed;
	*/
	Elements() {};
	~Elements() {};
};


class Database : public SingletonBase< Database >
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;
	typedef map<string, Elements*> arrElement;
	typedef map<string, Elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;

public:
	HRESULT Init(void);
	void Release(void);

	void LoadDatabase(string name);

	//접근자
	Elements* GetElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자

	/*
	void SetElementDataCurrentHP(string str, float ch);
	void SetElementDataMaxHP(string str, float mh);
	void SetElementDataAngle(string str, float a);
	void SetElementDataAcceleration(string str, float ac);
	void SetElementDataMaxSpeed(string str, float ms);
	*/

	Database();
	~Database();
};

