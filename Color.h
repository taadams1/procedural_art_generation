//Color class implemented by Trevor Adams, struct by Jesse Uchytil

#pragma once

#include <random>
//A struct containing each color channel, used as part of a canvas to be saved into a bitmap.
struct rgb_data { float r, g, b, a; };

class Color
{
public:
	static int randomRGBVal();
	static rgb_data randomColor();
	static rgb_data mixAlpha(rgb_data, rgb_data);
};

