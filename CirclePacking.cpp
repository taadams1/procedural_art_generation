#include "CirclePacking.h"

rgb_data ** CirclePacking::packCircles(int size, rgb_data color, rgb_data ** canvas)
{

	for (int i = 0; i < TOTAL_CIRCLES; i++) {

		createAndDrawCircle(size, color, canvas);
	}

	return canvas;
}

rgb_data ** CirclePacking::packFilledCircles(int size, rgb_data color, rgb_data ** canvas)
{

	for (int i = 0; i < TOTAL_CIRCLES; i++) {

		createAndDrawFilledCircle(size, color, canvas);
	}

	return canvas;
}

void CirclePacking::createAndDrawCircle(int size, rgb_data color, rgb_data ** canvas)
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generator
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, size - 1);

	circle newCircle;

	bool canBeDrawn = false;
	for (int tries = 0; tries < ATTEMPTS; tries++) {

		newCircle = {
		color,
		(int)dist(gen),
		(int)dist(gen),
		MIN_RADIUS
		};

		if (hasCollision(newCircle)) {
			continue;
		}
		else
		{
			canBeDrawn = true;
			break;
		}
	}

	if (!canBeDrawn) {
		return;
	}

	for (int radiusSize = MIN_RADIUS; radiusSize < MAX_RADIUS; radiusSize++) {
		newCircle.radius = radiusSize;
		if (hasCollision(newCircle)) {
			newCircle.radius--;
			break;
		}
	}

	
	circles.push_back(newCircle);
	//circleCounter++;
	Draw::drawThickCircle(newCircle.color, size, newCircle.x, newCircle.y, newCircle.radius, canvas);
}

void CirclePacking::createAndDrawFilledCircle(int size, rgb_data color, rgb_data ** canvas)
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generator
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, size - 1);

	circle newCircle;

	bool canBeDrawn = false;
	for (int tries = 0; tries < ATTEMPTS; tries++) {

		newCircle = {
		color,
		(int)dist(gen),
		(int)dist(gen),
		MIN_RADIUS
		};

		if (hasCollision(newCircle)) {
			continue;
		}
		else
		{
			canBeDrawn = true;
			break;
		}
	}

	if (!canBeDrawn) {
		return;
	}

	for (int radiusSize = MIN_RADIUS; radiusSize < MAX_RADIUS; radiusSize++) {
		newCircle.radius = radiusSize;
		if (hasCollision(newCircle)) {
			newCircle.radius--;
			break;
		}
	}


	circles.push_back(newCircle);
	//circleCounter++;
	Draw::drawFilledCircle(newCircle.color, size, newCircle.x, newCircle.y, newCircle.radius, canvas);
}


bool CirclePacking::hasCollision(circle c)
{
	for (int i = 0; i < circles.size(); i++) {
		circle otherCircle = circles[i];
		int a = c.radius + otherCircle.radius;
		int x = c.x - otherCircle.x;
		int y = c.y - otherCircle.y;

		if (a >= sqrt((x*x) + (y*y))) {
			return true;
		}
	}
	return false;
}
