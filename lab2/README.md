## CSCI 114 Lab2: Shape Drawing

For this lab we are going to write an interactive shape drawing program that will help us practice with inheritance.

Inheritance in C++ lets us create a heirarchy of object types that are related. Shared or common code is put higher up the heirarchy and objects are specialized as needed to implement functionality unique to the object type.

For this lab we will use a two-level heirarchy of Shapes. We will implement Trianges, Rectangles and Circles all as derived (or child) classes from a base (or parent) class `Shape`. `Shape` will contain code common to all Shapes, while the derived classes will implement functionaly specific to their shape.

#### Your Task

You will implement an interactive program that will draw filled in shapes in a 1024x1024 sized image. The skeleton code allowcates a blank image for you.

Your program will ask the user to enter which shape they want to draw. Then given the shape type, your program will collect the inputs required to instantiate the shape, e.g for a circle you would collect the center (x, y), the radius, and the fill color.

Once you have the required data, your program will instantiate an object of the correct type and use the object to draw the shape into the image.

After drawing, ask the user if they want to draw another shape. If the user enters "quit", quit the program and output the image (the output code is given).

### The objects

```C++
struct Color {
	uint8_t r, g, b;
};

struct Point {
	uint32_t x, y;
};

struct BoundingBox {
	Point ul, br;
};

class Shape {
public:
	Shape(Color c);
	void draw(uint8_t*** image, uint32_t h, uint32_t w);
	virtual bool inside(uint32_t x, uint32_t y) = 0;
	virtual BoundingBox getBoundingBox() = 0;
private:
	Color m_color;
};
```

Here we can see the interface for the `Shape` class. This class is a `virtual` class, meaning it is incomplete and can not be instantiated. Your job is to use the class as the base for the other classes. 

But we can see some common code: the `Shape()` constructor takes a color. This makes sense because all shapes have a color, which is stored as the `Color m_color` data member.

The drawing algorithm is based on tracing over the "bounding box" for the given shape and deciding if the current pixel is "inside" or "outside" the shape. Thus, we can have a common `draw()` method, but we need shape-specific `inside()` and `getBoundingBox()` methods.

When implementing the `draw()` method, if you encounter `x,y` pixel locations that are out-of-bounds, you should ignore them.

##### The Triangle
```
class Triangle : public Shape {
public:
	//What data does the constructor need?
	Triangle(/* ?? */);
	bool inside(uint32_t x, uint32_t y); //we'll give you this code
	BoundingBox getBoundingBox(); //how do you get the bounding box for a triangle?
private:
	//what data structures do we need to describe a triangle?
};
```
The `Triangle` definition is partially done for you. Follow the comments to implement the triangle. After the triangle is implemented, you should be able to complete `main.cpp` enough to draw triangles in your image.

Now implement the `Circle` and `Rectangle` classes following the pattern in `Triangle`. What data do you need to model a `Circle` or a `Rectangle`? How do you determine the bounding box and how do you determine if a given `x,y` location is "inside" the shape?
