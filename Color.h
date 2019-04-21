//Color class implemented by Trevor Adams, struct by Jesse Uchytil

#pragma once

#include <random>
#include <vector>

//A struct containing each color channel, used as part of a canvas to be saved into a bitmap.
struct rgb_data { float r, g, b, a; };

class Color
{
public:
	static int randomRGBVal();
	static rgb_data randomColor();
	static rgb_data lessRandom();
	static rgb_data mixAlpha(rgb_data, rgb_data);

	const rgb_data WHITE = { 255, 255, 255, 255 };
	const rgb_data BLACK = { 255, 255, 255, 255 };
	const rgb_data RED = { 255, 0, 0, 255 };
	const rgb_data GREEN = { 0, 255, 0, 255 };
	const rgb_data BLUE = { 0, 0, 255, 255 };
	const rgb_data YELLOW = { 255, 255, 0, 255 };
	const rgb_data MAGENTA = { 255, 0, 255, 255 };
	const rgb_data CYAN = { 0, 255, 255, 255 };

};

