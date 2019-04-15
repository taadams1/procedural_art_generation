#include "Point.h"


// Point constructor, takes x&y coordinates and color
Point::Point(int x, int y, int &clr)
{
	x1 = x;
	y1 = y;
	// assign rgb values
	this->clr = &clr;
	
}

// Copy constructor, copies x&y coordinates and color array
Point::Point(const Point &obj)
{
	x1 = obj.x1;
	y1 = obj.y1;

	// assign rgb values
	clr = obj.clr;
}


Point::~Point()
{
	delete[] clr;
}

//setter for point coordinates
void Point::setCoords(int x1, int y1)
{
	this->x1 = x1;
	this->y1 = y1;
}

//getter for x coordinate of point
int Point::getX1()
{
	return x1;
}

//getter for y coordinate of point
int Point::getY1()
{
	return y1;
}

//function to randomly move a point -n to n pixels, default 1
void Point::randomWalk(int x, int y, int shiftBy = 1)
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generater
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(-shiftBy, shiftBy);

	x1 += dist(gen);
	y1 += dist(gen);

}

////////// Line Subclass //////////////

// Line constructor with two points, rgb
Line::Line(int x1, int y1, int x2, int y2, int &clr)
	: Point(x1, y1, clr)
{
	this->x2 = x2;
	this->y2 = y2;
}


// copy constructor for line subclass, calls parent
Line::Line(const Line &obj)
	: Point(obj)
{
	this->x2 = obj.x2;
	this->y2 = obj.y2;
}

Line::~Line()
{
}

//////////// Rectangle Subclass //////////////////

//Rectagle constructor, takes two points, outline color, and fill color
Rect::Rect(int x1, int y1, int x2, int y2, int &outlineColor, int &fillColor)
	: Line( x1, y1, x2, x2, outlineColor)
{
		this->fillClr = &fillColor;
	
}

// copy constructor for Rectangle, calls parent and copies fill color
Rect::Rect(const Rect &obj)
	: Line(obj)
{
		this->fillClr = obj.fillClr;
}

Rect::~Rect()
{
	delete[] fillClr;
}
