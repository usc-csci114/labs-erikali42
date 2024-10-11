#ifndef __SHAPES_H__
#define __SHAPES_H__

#include <vector>
#include <cstdint> // Include for uint8_t, uint32_t types

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

// Declaration of PointInTriangle
bool PointInTriangle(Point p, Point tri[3]);

class Shape {
public:
    Shape(Color c);
    void draw(uint8_t*** image, uint32_t h, uint32_t w);
    virtual bool inside(uint32_t x, uint32_t y) = 0;
    virtual BoundingBox getBoundingBox() = 0;

private:
    Color m_color;
};

// Derived class for Triangle
class Triangle : public Shape {
public:
    Triangle(Point t[3], Color c);
    ~Triangle();
    bool inside(uint32_t x, uint32_t y);
    BoundingBox getBoundingBox();

private:
    Point m_tri[3];
};

// Derived class for Circle
class Circle : public Shape {
public:
    Circle(Point center, unsigned int r, Color c);
    ~Circle();
    bool inside(uint32_t x, uint32_t y);
    BoundingBox getBoundingBox();

private:
    Point m_center; 
    uint32_t m_radius;
};    

#endif // __SHAPES_H__
