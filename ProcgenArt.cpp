//Trevor Adams, taadams1@dmacc.edu, 3-18-19
//Tests for procgen art group project

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <fstream>

#include "FractalSquare.h"

using namespace std;

int randRGB();

/*int main() {

	_setmode(_fileno(stdout), _O_U16TEXT);

	const int SIZE = 128;

	vector<vector<wchar_t>> canvas(SIZE);

	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			canvas[i].push_back(L'░');
		}
	}

	FractalSquare::drawFractalSquare(SIZE, canvas);

	FractalSquare::print(canvas, SIZE, SIZE);

	/*unsigned seed = time(0);
	srand(seed);

	const int WIDTH = 4;
	const int HEIGHT = 4;
	

	int pixels[WIDTH][HEIGHT][3];

	for (int x = 0; x < WIDTH; x++) {

		for (int y = 0; y < HEIGHT; y++) {

			for (int i = 0; i < 3; i++) {
				pixels[x][y][i] = randRGB();
			}
		}
	}

	for (int x = 0; x < WIDTH; x++) {

		for (int y = 0; y < HEIGHT; y++) {

			cout << "RBG: ( ";

			for (int i = 0; i < 3; i++) {
				cout << pixels[x][y][i];
				if (i != 2) { cout << ", "; }
			}
			cout << " ) ";
		}
		cout << endl;
	}


	cin.get();

}

int randRGB() {
	return rand() % 256;
}*/ 

//All Turned off for testing