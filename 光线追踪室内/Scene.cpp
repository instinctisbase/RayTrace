// Scene.cpp: implementation of the Scene class.
//
//////////////////////////////////////////////////////////////////////
#include "Scene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//折射 refraction
//反射 reflection
//透射 transmission
int TRACE_DEPTH = 0;
template<class T>
int sign(T t)
{
	if (t>0)
		return 1;
	else if (t<0)
		return -1;
	else
		return 0;
}
void pabs(Point& pt)
{
	pt.x = fabs(pt.x);
	pt.y = fabs(pt.y);
	pt.z = fabs(pt.z);
}

void Scene::initScene()
{
	int i;
	Point box[8];
	Polygon polygon;
	int vIndex[6][4] = {
		{ 2, 3, 7, 6 },
		{ 0, 1, 5, 4 },
		{ 0, 2, 3, 1 },
		{ 4, 6, 7, 5 },
		{ 1, 5, 7, 3 },
		{ 0, 4, 6, 2 }
	};
	for (i = 0; i<8; i++)
	{
		box[i].x = ((i >> 2) & 1) - 0.5;
		box[i].y = ((i >> 1) & 1) - 0.5;
		box[i].z = ((i & 1)) - 0.5;
	}
	for (i = 0; i<6; i++)
	{
		polygon.setVertexes(box, vIndex[i], 4);
		plane.push_back(polygon);
	}
	polygon.vertex.resize(4);//加入一个档板
	polygon.vertex[0] = Point(-0.5, -0.5, -0.35);
	polygon.vertex[1] = Point(0, -0.5, -0.35);
	polygon.vertex[2] = Point(0, 0.5, -0.35);
	polygon.vertex[3] = Point(-0.5, 0.5, -0.35);
	polygon.refresh();

	plane.push_back(polygon);

	Light tmp;//加入光源
	tmp.Ia = 1;
	tmp.Ip = 0.5;
	tmp.pos = 0;
	light.push_back(tmp);

	lb = -1;	//设置视点与投影平面
	lb.z = -0.5;
	rt = 1;
	rt.z = -0.2;
	width = height = 400;
	buffer.resize(width*height);
	eye = 0;
	eye.z = 0.3;
	isSceneChanged = true;
}

Scene::Scene()
{
	initScene();
}

Vector3 Scene::localLightting(const Polygon& polygon, const Point& current_pos, const Point& out)
{
	float t1, t2;
	int i;
	Vector3 color(0.2, 0, 0);
	Vector3 Ka = polygon.Ka;
	Vector3 Kd = polygon.Kd;
	Vector3 normal = polygon.normal;
	for (i = 0; i<light.size(); i++)
	{
		Light lt = light[i];
		t1 = polygon.normal.dot(lt.pos) + polygon.d;
		t2 = polygon.normal.dot(out) + polygon.d;
		if (sign(t1) == sign(t2))	//如果入射光线与观察点在多边形的同一侧,那么就用上环境光与漫反射光
		{
			Point L = lt.pos - current_pos;
			L.normalize();
			Point tmp = (lt.Ip)*Kd*(L.dot(normal));
			pabs(tmp);
			color += tmp;

		}
	}
	return color;
}

Point Scene::crossRayPlane(const Ray& ray, const Polygon& plane)
{
	Point Q = ray.beginPoint;
	Vector3 E = ray.direction;
	Vector3 N = plane.normal;
	float d = plane.d;
	return Q - E*((d + N.dot(Q)) / N.dot(E));
}

int Scene::findNearestPolygon(const Ray& ray)
{
	int i;
	int nearest = -1;
	float minLength = 1e20;
	for (i = 0; i<plane.size(); i++)
	{
		Polygon& pan = plane[i];
		Point crossPoint = crossRayPlane(ray, pan);
		//if(i==6)
		//	printf("%f %f %f\n",crossPoint.x,crossPoint.y,crossPoint.z);
		if (pan.isPointInPolygon(crossPoint))
		{

			float t = -(pan.d + pan.normal.dot(ray.beginPoint)) / (pan.normal.dot(ray.direction));	//计算从光源到入射点的距离
			if (t>0)
			{
				if (minLength>t)//如果计算出平面的距离比以前的距离要短,那么替换
				{
					minLength = t;
					nearest = i;
				}
			}
		}
	}
	return nearest;
}

void Scene::writeFrameBuffer()
{
	int i, j, point = 0;
	Point Q = eye;
	Vector3 E;
	Point screenSize(width - 1, height - 1, 1);
	Ray ray;
	ray.beginPoint = Q;
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			Point s = Point(j, i, 0) / screenSize*(rt - lb) + lb;
			s.z = lb.z;
			E = s - Q;
			E.normalize();
			ray.direction = E;
			Vector3 color = RayTracing(ray, 0);
			buffer[point++] = color;
		}
	}
}

Vector3 Scene::RayTracing(const Ray& ray, int depth)
{
	int nearestPolygon = findNearestPolygon(ray);
	Vector3 color(0, 0, 0);
	Vector3 Is(0, 0, 0), It(0, 0, 0), Ir(0, 0, 0), Il(0, 0, 0);
	Point crossPoint;
	Point dir, norm;
	float n;
	float cosThetai;
	if (nearestPolygon >= 0)//如果有交点，那么计算
	{
		//if(nearestPolygon==6)
		//printf("%d\n",nearestPolygon);
		Polygon& pan = plane[nearestPolygon];
		crossPoint = crossRayPlane(ray, pan);
		Il = localLightting(plane[nearestPolygon], crossPoint, ray.beginPoint);
		color = Il;
		if (depth<TRACE_DEPTH)
		{
			Ray mray;
			mray.beginPoint = crossPoint;
			if (pan.isNormalSide(ray.beginPoint))//从正面透射到反面
			{
				norm = pan.normal;
				n = pan.nb / pan.na;
			}
			else	//从反面透射到正面
			{
				norm = -pan.normal;
				n = pan.na / pan.nb;
			}
			cosThetai = -norm.dot(ray.direction);	//入射角的余弦值
			mray.direction = ray.direction + norm*cosThetai * 2;	//计算反射光的方向
			mray.direction.normalize();
			Is = RayTracing(mray, depth + 1);

			mray.direction = norm*(n*cosThetai - sqrt(1 - n*n*(1 - cosThetai*cosThetai))) + ray.direction*n;//计算透射光的方向
			mray.direction.normalize();
			It = RayTracing(mray, depth + 1);
			color = Il + pan.Ks*pan.Cs*Is + pan.Kt*pan.Ct*It;
		}
	}
	return color;
}

void Scene::displayScene()
{
	if (isSceneChanged)
	{
		writeFrameBuffer();
		isSceneChanged = false;
	}
	glRasterPos2f(-1, -1);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, (const GLvoid*)&buffer[0]);
}

void Scene::setViewport(int w, int h)
{
	width = w;
	height = h;
	buffer.resize(width*height);
}