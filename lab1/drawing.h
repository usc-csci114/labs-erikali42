#ifndef DRAWING_H
#define DRAWING_H

#include <vector>
#include <string>
#include <cstdint>

// Struct for modeling a single pixel with RGB values
struct ColorPixel {
    uint8_t red, green, blue;
};

// Class for modeling the entire image as a 2D array of ColorPixels
class ColorImage {
public:
    // Constructor to initialize the image with given dimensions
    ColorImage(uint32_t xdim = 0, uint32_t ydim = 0);

    // Method to set a pixel at (x, y) with a given color
    void setPixel(ColorPixel p, uint32_t x, uint32_t y);

    // Method to get the pixel at (x, y)
    ColorPixel getPixel(uint32_t x, uint32_t y);

    // Method to render the image to a BMP file
    void render(std::string filename);

    // Method to get image width (x dimension)
    uint32_t getWidth() const { return data[0].size(); }

    // Method to get image height (y dimension)
    uint32_t getHeight() const { return data.size(); }

private:
    // 2D vector representing the image data (a matrix of ColorPixel)
	std::vector<std::vector<ColorPixel> > data;
};

// Struct for modeling a point with x, y coordinates
struct Point {
    double x, y;
};

// Struct for modeling a line with start and end points, and color
struct Line {
    Point start, end;
    ColorPixel color;
};

// Class for managing the drawing process, reading data from file, and drawing lines
class Drawing {
public:
    Drawing();  // Constructor

    // Method to parse the input file and initialize the image and lines
    void parse(std::string filename);

    // Method to draw all the lines onto the image
    void draw();

    // Method to write the final image to a BMP file
    void write(std::string filename);

private:
    ColorImage image;         // The canvas for the drawing
    std::vector<Line> lines;  // A collection of lines to be drawn
};

// Helper function (provided by the lab) to compute points that represent a line
std::vector<Point> plotLine(Point start, Point end);

#endif
