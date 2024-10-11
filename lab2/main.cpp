#include <iostream>
#include "bmplib.h"
#include "shapes.h"

using namespace std;

uint8_t*** newImage(uint8_t bground[3], uint32_t h, uint32_t w)
{
	uint8_t*** img = new uint8_t**[h];
	for(int r=0; r < h; r++) {
		img[r] = new uint8_t*[w];
		for(int c = 0; c < w; c++) {
			img[r][c] = new uint8_t[3];
			img[r][c][0] = bground[0];
			img[r][c][1] = bground[1];
			img[r][c][2] = bground[2];
		}
	}
	return img;
}

int main(int argc, char* argv[]) {
    uint8_t bg[] = {255, 255, 255};
    uint8_t*** image = newImage(bg, 1024, 1024);
    
    string shapeChoice;
    while (true) {
        cout << "Enter the shape you want to draw (triangle/circle) or 'quit' to stop: ";
        cin >> shapeChoice;

        if (shapeChoice == "quit") {
            break;
        }

        if (shapeChoice == "triangle") {
            Point points[3];
            Color red = {255, 0, 0};
            cout << "Enter the coordinates for the triangle (x1 y1 x2 y2 x3 y3): ";
            cin >> points[0].x >> points[0].y >> points[1].x >> points[1].y >> points[2].x >> points[2].y;
            Triangle tri(points, red);
            tri.draw(image, 1024, 1024);
        } else if (shapeChoice == "circle") {
            Point center;
            Color blue = {0, 0, 255};
            int radius;
            cout << "Enter the center coordinates (x y) and radius: ";
            cin >> center.x >> center.y >> radius;
            Circle circle(center, radius, blue);
            circle.draw(image, 1024, 1024);
        } else {
            cout << "Invalid shape!" << endl;
        }
    }

    writeRGBBMP("output.bmp", image, 1024, 1024);
}
