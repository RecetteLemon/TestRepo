#pragma once
//혹시 2010 쓰는 사람이 있을까봐 걸어둔다
#include <cmath>

#define DEG_TO_RAD 0.017453f	//1도의 대한 라디안 값
#define PI		3.141592654f
#define PI2		PI * 2
#define PI8		float(PI / 8.0f)
#define PI16		float(PI / 16.0f)
#define PI32		float(PI / 32.0f)
#define PI64		float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

#define RECT_WIDTH(rc) static_cast<float>(rc.right - rc.left)
#define RECT_HEIGHT(rc) static_cast<float>(rc.bottom - rc.top)
#define RECT_CENTER_X(rc) static_cast<float>((rc.left + rc.right) * 0.5f)
#define RECT_CENTER_Y(rc) static_cast<float>((rc.top + rc.bottom) * 0.5f)
#define IMAGE_FRAME_HEIGHT(keyName) (IMAGEMANAGER->findImage(keyName)->getFrameHeight())
#define IMAGE_FRAME_WIDTH(keyName) (IMAGEMANAGER->findImage(keyName)->getFrameWidth())
#define IMAGE_FRAME_HEIGHTf(keyName) static_cast<float>(IMAGEMANAGER->findImage(keyName)->getFrameHeight())
#define IMAGE_FRAME_WIDTHf(keyName) static_cast<float>(IMAGEMANAGER->findImage(keyName)->getFrameWidth())


#define FLOAT_EPSILON 0.001f	//실수의 가장 작은 단위를 지칭하는 그리스어
#define FLOAT_TO_INT(f1) static_cast<int>(f1 + FLOAT_EPSILON) //실수형을 정수형으로~
#define FLOAT_EQUAL(f1, f2) (fabs(f1, f2) <= FLOAT_EPSILON) //두 실수가 같은지 비교~


namespace LIMA_UTIL
{
	//거리가져오는 함수
	float GetDistance(float startX, float startY, float endX, float endY);

	float GetAngle(float x1, float y1, float x2, float y2);
}