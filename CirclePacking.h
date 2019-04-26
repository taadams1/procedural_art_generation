#pragma once

#include <vector>
#include <random>

#include "Draw.h"

static struct circle {
	rgb_data color;
	int x, y, radius;
};

static int circleCounter = 1;

class CirclePacking
{
private:
	
	static const int MIN_RADIUS = 3;
	static const int MAX_RADIUS = 180;
	static const int TOTAL_CIRCLES = 2200;
	static const int ATTEMPTS = 4000;
	static std::vector<circle> circles;
public:
	static rgb_data ** packCircles(int, rgb_data, rgb_data **);
	static rgb_data ** packFilledCircles(int, rgb_data, rgb_data **);
	static void createAndDrawCircle(int, rgb_data, rgb_data **);
	static void createAndDrawFilledCircle(int, rgb_data, rgb_data **);
	static bool hasCollision(circle);
};
