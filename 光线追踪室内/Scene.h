// Scene.h: interface for the Scene class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCENE_H__1BB16233_561A_4D63_BA15_8FE397FA36DF__INCLUDED_)
#define AFX_SCENE_H__1BB16233_561A_4D63_BA15_8FE397FA36DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <gl/glut.h>
#include "polygon.h"
#include "ray.h"
//#define TRACE_DEPTH 1
using namespace std;

class Scene
{
public:
	Scene();
	void initScene();	//场景的初始设置
	void displayScene();	//最终的显示函数,opengl调用该函数即可
	Vector3 localLightting(const Polygon& polygon, const Point& current_pos, const Point& out);//局部光照模型
	Point crossRayPlane(const Ray& ray, const Polygon& plane);	//计算平面与入射光线的交点
	int findNearestPolygon(const Ray& ray);	//找到距光源最近的多边形
	void writeFrameBuffer();	//把场景中的物体用光线跟踪法写入到buffer中去
	Vector3 RayTracing(const Ray& ray, int depth);
	void setViewport(int w, int h);
public:
	vector<Polygon> plane;
	vector<Light> light;
	Point eye;
	Point lb;	//左下角
	Point rt;	//右上角
	int width;
	int height;
	vector<Vector3> buffer;	//RGB三色的buffer
	bool isSceneChanged;
};

#endif // !defined(AFX_SCENE_H__1BB16233_561A_4D63_BA15_8FE397FA36DF__INCLUDED_)