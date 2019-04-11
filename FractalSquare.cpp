#include "FractalSquare.h"



FractalSquare::FractalSquare()
{
}


FractalSquare::~FractalSquare()
{
}


void FractalSquare::drawFractalSquare(int size, vector<vector<wchar_t>> &vec) {

	const int DEPTH = 6;

	srand(time(0));

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
			drawFS(vec, xPos, yPos, xPos + currentSize, yPos + currentSize);
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

}

void FractalSquare::print(vector<vector<wchar_t>> &vec, int x, int y)
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			wcout << vec[i][j];
		}
		wcout << endl;
	}
}


wstring FractalSquare::generateString(int depth)
{

	if (depth == 0) {
		int c = rand() % 5;

		if (c < 2) {
			return L"X";
		}
		return L".";
	}

	int c = rand() % (10 + (depth * 8));
	if (c < 5) {
		return L"X";
	}
	if (c < 10) {
		return L".";
	}
	wstring q1 = generateString(depth - 1);
	wstring q2 = generateString(depth - 1);
	wstring q3 = generateString(depth - 1);
	wstring q4 = generateString(depth - 1);

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

void FractalSquare::drawFS(vector<vector<wchar_t>> &vec, int x1, int y1, int x2, int y2) {

	for (int x = x1; x < x2; x++) {
		for (int y = y1; y < y2; y++) {
			vec[x][y] = L'█';
		}
	}

}