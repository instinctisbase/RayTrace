// Ray.cpp: implementation of the Ray class.
//
//////////////////////////////////////////////////////////////////////

#include "Ray.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ray::Ray()
{

}

Ray::Ray(const Point& begin, const Vector3& dir)
{
	beginPoint = begin;
	direction = dir;
	attenuation.x = 0.01;
	attenuation.y = 0.01;
	attenuation.z = 0.01;
}

float Ray::attenuate(const Point& object)
{
	float length = beginPoint.length(object);
	return attenuate(length);
}

float Ray::attenuate(float length)
{
	float attenu = (length*attenuation.x + attenuation.y)*length + attenuation.z;
	return 1 / attenu;
}