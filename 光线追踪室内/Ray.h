// Ray.h: interface for the Ray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_)
#define AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "point.h"
class Ray //光线类，这里的衰减常数没有使用
{
public:
	Ray();
	Ray(const Point& begin, const Vector3& dir);
	float attenuate(const Point& object);	//光线的衰减
	float Ray::attenuate(float length);
public:
	Point beginPoint;	//光线的起点
	Vector3 direction;	//光线的方向
	Vector3 color;	//光线的颜色
	Vector3 attenuation;	//衰减常数
};

#endif // !defined(AFX_RAY_H__1E702CD5_E748_4FBF_972F_F6856A823522__INCLUDED_)