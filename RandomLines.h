#pragma once

#include <cstdio>
#include <chrono>
#include <random>

#include "Draw.h"

class RandomLines
{
public:
	static rgb_data ** randomLines(int size, int iterations, rgb_data color, rgb_data ** canvas)
	{
		while (iterations >= 0) {

			int x1 = randomCoord(size);
			int y1 = randomCoord(size);
			int x2 = randomCoord(size);
			int y2 = randomCoord(size);


			if (x1 < 0) {
				x1 = 0;
			}
			if (y1 < 0) {
				y1 = 0;
			}
			if (x2 < 0) {
				x2 = 0;
			}
			if (y2 < 0) {
				y2 = 0;
			}
			if (x1 > size) {
				x1 = size - 1;
			}
			if (y1 > size) {
				y1 = size - 1;
			}
			if (x2 > size) {
				x2 = size - 1;
			}
			if (y2 > size) {
				y2 = size - 1;
			}

			Draw::drawLine(color, x1, y1, x2, y2, canvas);

			iterations--;
		}

		return canvas;
	}

private:
	static int randomCoord(int canvasSize)
	{
		std::random_device rndm;
		//seeded mersenne twister generater
		std::mt19937 gen(rndm());
		//range  distribution in which to generate integers
		std::uniform_int_distribution<> dist(-16, canvasSize + 16);

		return dist(gen);
	}
};