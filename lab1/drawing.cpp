#include "drawing.h"
#include "bmplib.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include <vector>
#include <cmath>

std::vector<Point> plotLine(Point p0, Point p1) {
    std::vector<Point> points;

    int dx = std::abs(static_cast<int>(p1.x - p0.x)), sx = p0.x < p1.x ? 1 : -1;
    int dy = -std::abs(static_cast<int>(p1.y - p0.y)), sy = p0.y < p1.y ? 1 : -1;
    int err = dx + dy, e2;

    while (true) {
        points.push_back(p0);
        if (p0.x == p1.x && p0.y == p1.y) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; p0.x += sx; }
        if (e2 <= dx) { err += dx; p0.y += sy; }
    }

    return points;
}

// ColorImage constructor to initialize the 2D vector with given dimensions
ColorImage::ColorImage(uint32_t xdim, uint32_t ydim) {
    data.resize(ydim, std::vector<ColorPixel>(xdim)); // Create a 2D vector with ydim rows and xdim columns
}

// Method to set the pixel at position (x, y) to the provided ColorPixel
void ColorImage::setPixel(ColorPixel p, uint32_t x, uint32_t y) {
    data[y][x] = p;
}

// Method to get the pixel at position (x, y)
ColorPixel ColorImage::getPixel(uint32_t x, uint32_t y) {
    return data[y][x];
}

// Method to render the image to a BMP file
void ColorImage::render(std::string filename) {
    // Create a 3D array for the BMP data
    uint8_t*** bmp_data = new uint8_t**[data.size()]; // height
    for (size_t y = 0; y < data.size(); ++y) {
        bmp_data[y] = new uint8_t*[data[y].size()]; // width
        for (size_t x = 0; x < data[y].size(); ++x) {
            bmp_data[y][x] = new uint8_t[3]; // RGB
            bmp_data[y][x][0] = data[y][x].red;
            bmp_data[y][x][1] = data[y][x].green;
            bmp_data[y][x][2] = data[y][x].blue;
        }
    }

    // Write to BMP using the function from bmplib
    writeRGBBMP(filename.c_str(), bmp_data, data.size(), data[0].size());

    // Clean up the dynamically allocated memory
    for (size_t y = 0; y < data.size(); ++y) {
        for (size_t x = 0; x < data[y].size(); ++x) {
            delete[] bmp_data[y][x]; // delete each pixel
        }
        delete[] bmp_data[y]; // delete each row
    }
    delete[] bmp_data; // delete the array of rows
}

// Drawing constructor
Drawing::Drawing() : image(0, 0) {}

// Method to parse the input file and initialize the ColorImage and Lines
void Drawing::parse(std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line)) {
        std::stringstream ss(line);

        if (firstLine) {
            // First line contains the dimensions of the image
            uint32_t xdim, ydim;
            ss >> xdim >> ydim;
            image = ColorImage(xdim, ydim);  // Initialize the ColorImage with dimensions
            firstLine = false;
        } else {
            // Parse the line data
            double x1, y1, x2, y2;
            int r, g, b;
            ss >> x1 >> y1 >> x2 >> y2 >> r >> g >> b;

            // Create Line object
            Line line;

            // Initialize the Points and ColorPixel
            line.start.x = x1;
            line.start.y = y1;

            line.end.x = x2;
            line.end.y = y2;

            line.color.red = static_cast<uint8_t>(r);
            line.color.green = static_cast<uint8_t>(g);
            line.color.blue = static_cast<uint8_t>(b);

            // Add the line to the vector of lines
            lines.push_back(line);
        }
    }

    file.close();
}

// Method to draw all the lines on the ColorImage
void Drawing::draw() {
    for (size_t i = 0; i < lines.size(); ++i) {
        const Line &line = lines[i];
        // Use plotLine to get the vector of points that represent the line
        std::vector<Point> points = plotLine(line.start, line.end);
        
        // Set each point on the ColorImage to the color of the line
        for (size_t j = 0; j < points.size(); ++j) {
            const Point &p = points[j];
            if (p.x >= 0 && p.x < image.getWidth() && p.y >= 0 && p.y < image.getHeight()) {
                image.setPixel(line.color, static_cast<uint32_t>(p.x), static_cast<uint32_t>(p.y));
            }
        }
    }
}

// Method to write the final image to the file
void Drawing::write(std::string filename) {
    image.render(filename);  // Render the image to a BMP file
}
