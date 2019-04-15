#pragma once
#ifndef POINT_H
#define POINT_H
#endif // !POINT_H

#include <random>

// enum to facilitate array initialization within class
enum { rgb = 3, rgba = 4 };

class Point
{
protected:
	int x1, y1;
	int *clr;
public:
	Point(int x1, int y1, int &);
	Point(const Point &);
	virtual ~Point();
	void setCoords(int x1, int y1);
	int getX1();
	int getY1();
	void randomWalk(int x,int y, int shiftBy);
};

class Line : public Point
{
protected:
	int x2, y2;
public:
	Line(int x1, int y1, int x2, int y2, int &clr);
	Line(const Line &);
	~Line();
};

class Rect : public Line
{
protected:
	int * fillClr;
public:
	Rect(int x1, int y1, int x2, int y2, int &outlineColor, int &fillColor);
	Rect(const Rect &);
	~Rect();
};


// TODO: implement circle subclass
/*class Circle : Point
{
protected:
	int radius;
};*/

