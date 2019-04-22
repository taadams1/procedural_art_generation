#include "Color.h"

//This function returns a single number in the rgb range 0-255
int Color::randomRGBVal()
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generator
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, 255);

	return dist(gen);
}

//Random Color function returns rgb color with 255 alpha
rgb_data Color::randomColor()
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generator
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, 255);

	rgb_data color = { dist(gen), dist(gen), dist(gen), 255};
	return color;
}

rgb_data Color::lessRandom()
{
	std::vector<int> intervals = { 0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255 };

	rgb_data color;

	std::random_shuffle(intervals.begin(), intervals.end());
	color.r = intervals[0];

	std::random_shuffle(intervals.begin(), intervals.end());
	color.g = intervals[0];

	std::random_shuffle(intervals.begin(), intervals.end());
	color.b = intervals[0];

	color.a = 255;

	return color;
}

rgb_data Color::lessRandomTransparent()
{
	std::vector<int> intervals = { 0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255 };

	rgb_data color;

	std::random_shuffle(intervals.begin(), intervals.end());
	color.r = intervals[0];

	std::random_shuffle(intervals.begin(), intervals.end());
	color.g = intervals[0];

	std::random_shuffle(intervals.begin(), intervals.end());
	color.b = intervals[0];

	color.a = 128;

	return color;
}

//Mix Alpha takes the current canvas color and "paints" the new color
//over it using the alpha value and returns the resulting color
rgb_data Color::mixAlpha(rgb_data baseColor, rgb_data color)
{
	// convert alpha to float between 0-1
	float alphaFactor = color.a / 255;

	// if alpha is not 1 (255), calculate color blend
	if (alphaFactor != 1.0) {

		color.r = (baseColor.r * (1 - alphaFactor) + color.r * alphaFactor);
		color.g = (baseColor.g * (1 - alphaFactor) + color.g * alphaFactor);
		color.b = (baseColor.b * (1 - alphaFactor) + color.b * alphaFactor);
		color.a = 255;
	}

	return color;
}
