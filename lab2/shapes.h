#ifndef __SHAPES_H__
#define __SHAPES_H__
#include <vector>

//define our (virtual) base class
using namespace std;

struct Color {
	uint8_t r, g, b;
};

struct Point {
	uint32_t x, y;
};

struct BoundingBox {
	Point ul, br;
};

bool PointInTriangle(Point p, Point tri[3])
{
	int s = (tri[0].x - tri[2].x) * (p.y - tri[2].y) - (tri[0].y - tri[2].y) * (p.x - tri[2].x);
	int t = (tri[1].x - tri[0].x) * (p.y - tri[0].y) - (tri[1].y - tri[0].y) * (p.x - tri[0].x);

	if ((s < 0) != (t < 0) && s != 0 && t != 0)
		return false;

	int d = (tri[2].x - tri[1].x) * (p.y - tri[1].y) - (tri[2].y - tri[1].y) * (p.x - tri[1].x);
	return d == 0 || (d < 0) == (s + t <= 0);
}

class Shape {
public:
	Shape(Color c);
	void draw(uint8_t*** image, uint32_t h, uint32_t w);
	virtual bool inside(uint32_t x, uint32_t y) = 0;
	virtual BoundingBox getBoundingBox() = 0;
private:
	Color m_color;
};

//define a derived class for Triangle, Rectagle, and Circle
class Triangle : public Shape {
public:
	//What data does the constructor need?
	Triangle(/* ?? */);
	bool inside(uint32_t x, uint32_t y); //we'll give you this code
	BoundingBox getBoundingBox(); //how do you get the bounding box for a triangle?
private:
	//what data structures do we need to describe a triangle?
};

//Now follow this pattern and create a derived class for the Circle and Rectangle

#endif