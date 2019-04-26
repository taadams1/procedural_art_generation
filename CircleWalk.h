//Line walk class by Trevor Adams

#pragma once

#include <random>

#include "Draw.h"

class CircleWalk
{
public:

	// this function takes two lines and draws them over a set number of iterations
	// wach time shifting the coordinates of each point in a range of (-shift,shift)
	static rgb_data ** circleWalk(int xCenter, int yCenter, int radius, int size, int shift, int iterations, rgb_data ** canvas)
	{
		//black with low alpha to show iterations
		rgb_data color = { 0, 0, 0, 32 };

		//loop through iterations
		while (iterations > 0) {

			//draw the circle
			Draw::drawCircleOffCanvas(color, size, xCenter, yCenter, radius, canvas);
			
			bool inCanvas = false;
			int attempts = 50;
			while (!inCanvas) { 
				xCenter += randomWalk(shift); 
				inCanvas = inBounds(xCenter, size);
				attempts--;
				if (attempts <= 0) {
					forceBounds(xCenter, size);
					break;
				}
			}

			inCanvas = false;
			attempts = 50;
			while (!inCanvas) {
				yCenter += randomWalk(shift);
				inCanvas = inBounds(yCenter, size);
				attempts--;
				if (attempts <= 0) {
					forceBounds(yCenter, size);
					break;
				}
			}

			radius += randomWalk(shift);
			attempts = 50;
			while (radius <= 2 || radius >= (size / 2)) { 
				radius += randomWalk(shift);
				attempts--;
				if (attempts <= 0) {
					radius = size / 8;
					break;
				}
			}
			
			//subtract from iterations remaining
			iterations--;
		}
		//return the canvas
		return canvas;
	}

	//function to shift a number up or down in range (-shiftBy,shiftBy)
	static int randomWalk(int shiftBy = 1)
	{
		//seed for generator
		std::random_device rndm;
		//seeded mersenne twister generator
		std::mt19937 gen(rndm());
		//range  distribution in which to generate integers
		std::uniform_int_distribution<> dist(-shiftBy, shiftBy);

		return dist(gen);

	}

	static bool inBounds(int coord, int canvasSize)
	{
		if (coord > canvasSize - 1) {
			return false;
		}
		if (coord < 0) {
			return false;
		}
		return true;
	}

	static int forceBounds(int coord, int canvasSize)
	{
		if (coord > canvasSize - 1) {
			return canvasSize - 1;
		}
		if (coord < 0) {
			return 0;
		}
		return coord;
	}
};
