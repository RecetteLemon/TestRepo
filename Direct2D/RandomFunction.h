#pragma once
#include "SingletonBase.h"
#include <time.h>

//=======================================
// ## 2015. 10. 21 ## randomFunction ##
//=======================================

class RandomFunction : public SingletonBase < RandomFunction >
{
public:
	RandomFunction(void)
	{
		srand(GetTickCount());
	}
	~RandomFunction(void)
	{

	}

	//int형 랜덤값 가져와보세!!
	inline int GetInt(int num) { return rand() % num; }
	inline int GetFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

	//float형 랜덤값 가져와보기
	float GetFloat() { return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float num) { return ((float)rand() / (float)RAND_MAX) * num; }
	float GetFromFloatTo(float fromFloat, float toFloat)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toFloat - fromFloat) + fromFloat);
	}


};