## CSCI 114 Lab 1: Line Drawing
For this lab we are going to build a program that reads in a file that describes a drawing made up of individual lines.

We're going to get some experience with using classes for this lab, so we're going to use an object oriented approach. This means that we'll model the parts of a drawing as C++ structs or classes.

For writing out our drawings we're using the `bmplib.h/cpp` files that are already included in the skeleton. Remember, all you need to do to use the functions in `bmplib.cpp` is to `#include bmplib.h` in your code. 

For this lab you'll define your structs/classes in `drawing.h`, you'll implement the classes in `drawing.cpp` and you'll implement the main program in `draw.cpp`. This would allow us to re-use the objects in another program by including `drawing.h`

To compile our program we'll use:

```
clang++ -Wall drawing.cpp draw.cpp -o draw
```

#### Objects

For a line drawing we will model the following objects:

- `struct ColorPixel`: the building block of an image. Has three unsgined char values for red, green and blue colors.

- `class ColorImage`: Holds a 2D vector of ColorPixels and two integers for the `x` and `y` size.

- `struct Point`: a point with x,y coordinates

- `struct Line`: models a line with two points

- `class Drawing`: top-level class that models the drawing. Has a `ColorImage` instance and a vector of `Lines` 

#### Input

The input to our drawing program will be a text file, the name will be given on the command line as the 1st argument to the program. Make sure your program checks to see if the file exists before attempting to open the file. Your program should quit if it can not open the file.

The first line of the file contains two integers that set the dimensions of the image.

Each following line describes a line in the drawing with the following format:

```
x1 y1 x2 y2 r g b
```
Where `x1` `y1` `x2` `y2` are floating point values that set the start and end of a line and `r`, `g`, `b` are the values for the color (0-255). All coordinate values will be between 0 and `xdim` or `ydim`. You do not need to do error checking on these values.

Your task is to write a program that will read in the input file and produce a .bmp file called `output.bmp`. Since this is a lab to get practice with objects, we will be following an object oriented design approach.


#### The objects

You will need to add data memebers and method as needed to implement the functionality. The descriptions below may not be complete.

```
struct ColorPixel {
	uint8_t red, green, blue;
};
```

The `ColorPixel`struct models a pixel. Since it is a struct we do not need any methods. When necessary the red, green, and blue values can be set directly.

```
class ColorImage {
	public:
		ColorImage(uint32_t xdim, uint32_t ydim);
		void setPixel(ColorPixel p, uint32_t x, uint32_t y);
		ColorPixel getPixel(uint32_t x, uint32_t y);
		void render(string filename);
			
	private:
		vector< vector<ColorPixel> > data;
}; 
```

The `ColorImage` class models an image with a 2D array of pixels. When the image is ready to be written to a file the `render()` method is called. This method will use the `bmplib.cpp` functions to create an ouput file with the given name by rendering the 2D vector of pixels into the data needed for the `bmplib` functions.

```
struct Point {
	double x, y;
};
```
Models a point.

```
struct Line {
	Point start, end;
	ColorPixel c;
};
```

Models a line. Uses a `ColorPixel` object to model the color for the line.

```
class Drawing {
	public:
		Drawing();
		void parse(string filename);
		void draw();
		void write(string filename);
	private:
		ColorImage image;
		vector<Line> lines;
};
```
This class models our drawing. The `parse()` method takes the input file and initilizes the `ColorImage` data member and then parses the rest of the input data into a vector of `Line` objects.

The `draw()` method will iterate through the `lines` drawing each line into the `ColorImage` data member. We have given you a line drawing function that you can use to implement this. The `plotLine()` function takes two points as the start and end of a line and will return a `vector<Point>`. Each `Point` in the vector represents a pixel that should be colored in to draw a line.

The `write()` method will call the `render()` method on the `ColorImage` in order to write the output file for the image.
