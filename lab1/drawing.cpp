#include <iostream>
#include <cmath>
#include <vector>

#include "bmplib.h"
#include "drawing.h"

//implement your classes in this file
//Point is given for the line drawing algorithm
struct Point {
	double x, y;
};

//adapted from https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
std::vector<Point> plotLine(Point start, Point end)
{
	int x0 = start.x;
	int y0 = start.y;
	int x1 = end.x;
	int y1 = end.y;
	
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
	
	std::vector<Point> line;
	
	while(true)
	{
		Point p = {x0, y0};
		line.push_back(p);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * error;
		if(e2 >= dy) {
			error = error + dy;
			x0 = x0 + sx;
		}
		if(e2 <= dx) {
			error = error + dx;
			y0 = y0 + sy;
		}
	}
	return line;
}
