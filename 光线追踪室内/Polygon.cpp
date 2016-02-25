// Polygon.cpp: implementation of the Polygon class.
//
//////////////////////////////////////////////////////////////////////

#include "Polygon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Polygon::Polygon(const vector<Point>& nvertex)
{
	setVertexes(nvertex);
}

Polygon::Polygon(const Polygon& polygon)
{
	*this = polygon;
}

Polygon::Polygon()//调节这些参数可以改变效果
{
	Ka = 0.8;
	Kd = 0.5;
	Ks = 0.8;
	Kt = 1;
	Cs = 1;
	Ct = 1;
	na = 1;
	nb = 1.5;
	isTransparente = false;
}

bool Polygon::isPointInPolygon(const Point& pt)
{
	int i;
	Point a, b, c;
	for (i = 0; i<vertex.size() - 1; i++)
	{
		a = vertex[i + 1] - vertex[i];
		b = pt - vertex[i];
		c = a.cross(b);
		c.normalize();
		if (!normal.isSame(c))
			return false;
	}
	a = vertex[0] - vertex[i];
	b = pt - vertex[i];
	c = a.cross(b);
	c.normalize();
	if (!normal.isSame(c))
		return false;
	else
		return true;
}

bool Polygon::isNormalSide(const Point& pt)
{
	return pt.dot(normal) + d>0;
}

void Polygon::setVertexes(const vector<Point>& nvertex)
{
	vertex = nvertex;
	refresh();
}

void Polygon::addVertex(const Point& pt)
{
	vertex.push_back(pt);
	refresh();
}

void Polygon::setVertexes(const Point vpt[], int index[], int n)
{
	int i;
	vertex.resize(n);
	for (i = 0; i<n; i++)
		vertex[i] = vpt[index[i]];
	refresh();
}

void Polygon::refresh()
{
	if (vertex.size()>2)
	{
		//printf("i here\n");
		Point a = vertex[1] - vertex[0];
		Point b = vertex[vertex.size() - 1] - vertex[0];
		normal = a.cross(b);
		normal.normalize();
		d = -normal.dot(vertex[0]);
	}
}