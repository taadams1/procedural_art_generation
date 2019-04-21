#include "Color.h"



Color::Color()
{
}


Color::~Color()
{
}

int Color::randomRGBVal()
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generater
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, 255);

	return dist(gen);
}

rgb_data Color::randomColor()
{
	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generater
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, 255);

	rgb_data color = { dist(gen), dist(gen), dist(gen), 255};
	return color;
}

rgb_data Color::mixAlpha(rgb_data baseColor, rgb_data newColor)
{
	float alphaFactor = newColor.a;
	int r = (baseColor.r * (1 - alphaFactor) + newColor.r * alphaFactor);
	int g = (baseColor.g * (1 - alphaFactor) + newColor.g * alphaFactor);
	int b = (baseColor.b * (1 - alphaFactor) + newColor.b * alphaFactor);

	rgb_data color = { r, g, b, 255 };

	return color;
}
