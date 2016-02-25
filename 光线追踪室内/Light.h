// Light.h: interface for the Light class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_)
#define AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "point.h"

class Light  //点光源
{
public:
	static Vector3 Ia;	//环境光强度
	Point pos;	//光源位置
	Vector3 Ip;	//光源强度
public:
	//Light(const Point& light_pos,
};

#endif // !defined(AFX_LIGHT_H__CCD0A844_279D_4B73_910D_008056236329__INCLUDED_)