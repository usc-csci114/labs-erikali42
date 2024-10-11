#include <algorithm>
#include <cmath>
#include "shapes.h"

// Implement your shapes here
Shape::Shape(Color c) : m_color(c) {}

bool PointInTriangle(Point p, Point tri[3]) {
    int s = (tri[0].x - tri[2].x) * (p.y - tri[2].y) - (tri[0].y - tri[2].y) * (p.x - tri[2].x);
    int t = (tri[1].x - tri[0].x) * (p.y - tri[0].y) - (tri[1].y - tri[0].y) * (p.x - tri[0].x);

    if ((s < 0) != (t < 0) && s != 0 && t != 0)
        return false;

    int d = (tri[2].x - tri[1].x) * (p.y - tri[1].y) - (tri[2].y - tri[1].y) * (p.x - tri[1].x);
    return d == 0 || (d < 0) == (s + t <= 0);
}

void Shape::draw(uint8_t*** image, uint32_t h, uint32_t w) {
    BoundingBox bb = getBoundingBox(); // Grab bounding box
    for (int r = bb.ul.y; r < bb.br.y; r++) {
        for (int c = bb.ul.x; c < bb.br.x; c++) {
            if (inside(c, r)) { // Check if inside shape
                image[r][c][0] = m_color.r;
                image[r][c][1] = m_color.g;
                image[r][c][2] = m_color.b;
            }
        }
    } 
}

Triangle::Triangle(Point t[3], Color c) : Shape(c) {
    // Initialize triangle coordinates
    m_tri[0] = t[0];
    m_tri[1] = t[1];
    m_tri[2] = t[2];
}

Triangle::~Triangle() {} // No need for anything because no memory was allocated

BoundingBox Triangle::getBoundingBox() {
    BoundingBox b;
    b.ul.x = std::min(std::min(m_tri[0].x, m_tri[1].x), m_tri[2].x);
    b.ul.y = std::min(std::min(m_tri[0].y, m_tri[1].y), m_tri[2].y);
    b.br.x = std::max(std::max(m_tri[0].x, m_tri[1].x), m_tri[2].x);
    b.br.y = std::max(std::max(m_tri[0].y, m_tri[1].y), m_tri[2].y);

    return b;
}

bool Triangle::inside(uint32_t x, uint32_t y) {
    Point p = { x, y }; // Create point to check
    return PointInTriangle(p, m_tri); // You need to implement PointInTriangle
}

Circle::Circle(Point center, uint32_t r, Color c) : Shape(c) {
    m_center = center;
    m_radius = r;
}

Circle::~Circle() {}

BoundingBox Circle::getBoundingBox() {
    BoundingBox b;
    b.ul.x = m_center.x - m_radius; 
    b.ul.y = m_center.y - m_radius;
    b.br.x = m_center.x + m_radius;
    b.br.y = m_center.y + m_radius;

    return b;
}

bool Circle::inside(uint32_t x, uint32_t y) {
    double dx = static_cast<double>(x);
    double dy = static_cast<double>(y);
    double distance = sqrt((m_center.x - dx) * (m_center.x - dx) + 
                           (m_center.y - dy) * (m_center.y - dy));

    return distance < m_radius; // Use < for inside
}

// Remember to implement the PointInTriangle function somewhere in your code.
