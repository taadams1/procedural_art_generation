#include "FractalSquare.h"


//initialize fractal square, create generation string, decode string and
//draw squares at the appropriate size and location
rgb_data ** FractalSquare::drawFractalSquare(int size, rgb_data color, rgb_data ** canvas)
{
	const int DEPTH = 8;

	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	wstring output = generateString(DEPTH);

	int currentSize;
	int currentDepth = 0;
	int xPos = 0;
	int yPos = 0;

	for (int i = 0; i < output.length(); i++) {

		char p = output[i];
		currentSize = size / pow(2, currentDepth);

		switch (p)
		{
		case 'X':
			Draw::drawRectangle(color, xPos, yPos, xPos + currentSize - 2, yPos + currentSize - 2, true, canvas);
			break;
		case '[':
			currentDepth++;
			break;
		case ']':
			xPos -= currentSize;
			yPos -= currentSize;
			currentDepth--;
			break;
		case '-':
			xPos += currentSize;
			break;
		case '/':
			xPos -= currentSize;
			yPos += currentSize;
			break;
		default:
			break;
		}

	}

	return canvas;
}

//initialize fractal square, create generation string, decode string and
//draw squares at the appropriate size and location, with a chance of drawing a circle
rgb_data ** FractalSquare::drawFractalSquareWithCircles(int size, rgb_data color, rgb_data ** canvas)
{
	const int DEPTH = 8;

	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

	wstring output = generateString(DEPTH);

	int currentSize;
	int currentDepth = 0;
	int xPos = 0;
	int yPos = 0;

	for (int i = 0; i < output.length(); i++) {

		char p = output[i];
		currentSize = size / pow(2, currentDepth);

		//seed for generator
		std::random_device rndm;
		//seeded mersenne twister generator
		std::mt19937 gen(rndm());
		//range  distribution in which to generate integers
		std::uniform_int_distribution<> dist(0, 3);

		rgb_data cirClr = color;

		cirClr.r = cirClr.r - 8;
		cirClr.g = cirClr.g - 8;
		cirClr.b = cirClr.b - 8;

		int circleChance = dist(gen);
		switch (p)
		{
		case 'X':
			Draw::drawRectangle(color, xPos, yPos, xPos + currentSize - 2, yPos + currentSize - 2, true, canvas);

			if (circleChance > 1 && currentDepth < 5) {
				Draw::drawFilledCircle(cirClr, size, xPos + (currentSize / 2), yPos + (currentSize / 2), currentSize * 0.4, canvas);
			}
			break;
		case '[':
			currentDepth++;
			break;
		case ']':
			xPos -= currentSize;
			yPos -= currentSize;
			currentDepth--;
			break;
		case '-':
			xPos += currentSize;
			break;
		case '/':
			xPos -= currentSize;
			yPos += currentSize;
			break;
		default:
			break;
		}

	}

	return canvas;
}



//fractal square generated through the use of recursion,
//with square brackets to designate the depth of recursion
//"X" indicates a square at given position
wstring FractalSquare::generateString(int depth)
{
	// base case if depth is 0
	if (depth == 0) {
		int c = rand() % 5;

		if (c < 2) {
			return L"X";
		}
		return L".";
	}

	// randomizer influenced by depth, squares are more likely
	//to be present at smaller depths

	//seed for generator
	std::random_device rndm;
	//seeded mersenne twister generator
	std::mt19937 gen(rndm());
	//range  distribution in which to generate integers
	std::uniform_int_distribution<> dist(0, 10 + (depth * 8));

	int c = dist(gen);
	if (c < 5) {
		return L"X";
	}
	if (c < 10) {
		return L".";
	}

	//if no square is generated, quater the current square and call self
	wstring q1 = generateString(depth - 1);
	wstring q2 = generateString(depth - 1);
	wstring q3 = generateString(depth - 1);
	wstring q4 = generateString(depth - 1);

	//assembly of output string
	wstring output = L"";
	output += L"[";
	output += q1;
	output += L"-";
	output += q2;
	output += L"/";
	output += q3;
	output += L"-";
	output += q4;
	output += L"]";

	return output;
}
