#pragma once

//===========================================
// - ## Macro Function 15. 10. 19 ## -
//===========================================

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}


//RECT
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}