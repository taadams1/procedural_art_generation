//Line walk class by Trevor Adams

#pragma once

#include <random>

#include "Draw.h"

class LineWalk
{
public:

	// this function takes two lines and draws them over a set number of iterations
	// wach time shifting the coordinates of each point in a range of (-shift,shift)
	static rgb_data ** lineWalk(int lines[2][4], int size, int shift, int iterations, rgb_data ** canvas)
	{
		//black with low alpha to show iterations
		rgb_data color = { 0, 0, 0, 32 };

		//loop through iterations
		while (iterations > 0) {

			//shifting of line coordinates and bounds checking
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 4; j++) {
					lines[i][j] += randomWalk(shift);
				}
				if (lines[i][0] < 0) {
					lines[i][0] = 0;
				}
				if (lines[i][1] < 0) {
					lines[i][1] = 0;
				}
				if (lines[i][2] < 0) {
					lines[i][2] = 0;
				}
				if (lines[i][3] < 0) {
					lines[i][3] = 0;
				}
				if (lines[i][0] > size) {
					lines[i][0] = size - 1;
				}
				if (lines[i][1] > size) {
					lines[i][1] = size - 1;
				}
				if (lines[i][2] > size) {
					lines[i][2] = size - 1;
				}
				if (lines[i][3] > size) {
					lines[i][3] = size - 1;
				}
				//draw the line
				Draw::drawLine(color, lines[i][0], lines[i][1], lines[i][2], lines[i][3], canvas);
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
		//seeded mersenne twister generater
		std::mt19937 gen(rndm());
		//range  distribution in which to generate integers
		std::uniform_int_distribution<> dist(-shiftBy, shiftBy);

		return dist(gen);

	}
};
