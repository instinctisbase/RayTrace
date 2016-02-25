// Polygon.h: interface for the Polygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__9C8C4F78_4215_4D82_9068_872B64550991__INCLUDED_)
#define AFX_POLYGON_H__9C8C4F78_4215_4D82_9068_872B64550991__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include "light.h"
using namespace std;

class Polygon
{
public:
	Polygon(const vector<Point>& nvertex);
	Polygon();
	Polygon(const Polygon& polygon);
	Vector3 Ks;	//反射参数
	Vector3 Kt;	//透射参数
	Vector3 Cs;	//反射颜色参数
	Vector3 Ct;	//透射颜色参数
	Vector3 Kd;	//漫反射参数
	Vector3 Ka;	//环境光参数
	Point normal;	//多边形的方向向量 
	float d;	//多边形距原点的距离
	float na, nb;//na面为正面，nb面为负面
	bool isTransparente;
	vector<Point> vertex;
public:
	bool isPointInPolygon(const Point& pt);	// 判断点是不是在多边形内
	bool isNormalSide(const Point& pt);	//判断点是不是位于多边形的正面(正面是多边形方向向量所在的面)
	void setVertexes(const vector<Point>& nvertex);	//设置多边形的顶点
	void addVertex(const Point& pt);	//增加顶点
	void setVertexes(const Point vpt[], int index[], int n);	//设置多边形的顶点
	void refresh();	//刷新计算多边形的方向向量与多边形距原点的距离
};

#endif // !defined(AFX_POLYGON_H__9C8C4F78_4215_4D82_9068_872B64550991__INCLUDED_)
