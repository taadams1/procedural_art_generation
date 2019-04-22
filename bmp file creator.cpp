//bitmap creation example taken from http://ricardolovelace.com/creating-bitmap-images-with-c-on-windows.html and adapted for use by Jesse Uchytil, 3-26-19


#include <fstream>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <cmath>

#include "Draw.h"
#include "FractalSquare.h"
#include "RandomLines.h"
#include "RandomPixels.h"
#include "LineWalk.h"
#include "CirclePacking.h"

const rgb_data WHITE{ 255, 255, 255, 255 };
const rgb_data BLACK = { 0, 0, 0, 0 };
const rgb_data RED = { 255, 0, 0, 255 };
const rgb_data GREEN = { 0, 255, 0, 255 };
const rgb_data BLUE = { 0, 0, 255, 255 };
const rgb_data YELLOW = { 255, 255, 0, 255 };
const rgb_data MAGENTA = { 255, 0, 255, 255 };
const rgb_data CYAN = { 0, 255, 255, 255 };

using namespace std;

std::vector<circle> CirclePacking::circles; //pre-declaration of vector for circle pack functions

//A function that saves a bitmap based on given parameters
void save_bitmap(const char * file_name, int width, int height, rgb_data ** pixel_data)
{
	FILE *image;//create a file that will be written to later
	int image_size = width * height;//Find the size of the image
	int file_size = 54 + 4 * image_size;//find the size of the file
	int ppm = 96 * 39.375;//find the pixels per meter (multiply dpi by a constant)

	//The basic file header for a file.  Determines what kind of file it is and how large it is.  Is 14 bytes large.
	struct bitmap_file_header {
		unsigned char bitmap_type[2];
		int file_size;
		short reserved1;
		short reserved2;
		unsigned int offset_bits;
	} bfh;

	//The file header specific to a bitmap.  Is 40 bytes large.
	struct bitmap_image_header {
		unsigned int size_header;//the size of this header
		unsigned int width;//the width of the image
		unsigned int height;//the height of the image
		short int planes;//how many planes the image has
		short int bit_count;//how large each pixel is in bits (32 in this case due to 4 channel unsigned chars (0-255 range times 4))
		unsigned int compression;//different compression modes, leaving it at 0 because I don't want to mess with that.
		unsigned int image_size;//how large the file is
		unsigned int ppm_x;//pixels per meter on the x scale
		unsigned int ppm_y;//pixels per meter on the y scale
		unsigned int clr_used;//color table, used to decrease file size
		unsigned int clr_important;//same as above.  Not messing with this.
	} bih;

	memcpy(&bfh.bitmap_type, "BM", 2);//populate the appropriate values to the appropriate slots in the structs.
	bfh.file_size = file_size;//don't mess with these unless you know exactly what you're doing.
	bfh.reserved1 = 0;
	bfh.reserved2 = 0;
	bfh.offset_bits = 0;

	bih.size_header = sizeof(bih);
	bih.width = width;
	bih.height = height;
	bih.planes = 1;
	bih.bit_count = 32;
	bih.compression = 0;
	bih.image_size = file_size;
	bih.ppm_x = ppm;
	bih.ppm_y = ppm;
	bih.clr_used = 0;
	bih.clr_important = 0;

	image = fopen(file_name, "wb");//open the file.

	fwrite(&bfh, 1, 14, image);//write both headers into the file
	fwrite(&bih, 1, sizeof(bih), image);

	for (int i = height - 1; i > -1; i--) {//for each pixel in the height of the canvas (starting from end of array to allow for standard upper-right-corner origin in computer graphics, something bitmaps don't do normally.)
		for (int j = 0; j < width; j++) {//for each pixel in the width of the canvas
			rgb_data BGR = pixel_data[j][i];//copy the color channels from the pixel array for easier logic

			float red = (BGR.r);//convert to raw values (bitmaps take bgra, not rgba).
			float green = (BGR.g);
			float blue = (BGR.b);
			float alpha = (BGR.a);

			unsigned char color[4] = {//convert to an array of unsigned chars in the format of BGRA
			   blue, green, red, alpha
			};
			fwrite(color, 1, sizeof(color), image);//write pixel into file
		}

	}

	fclose(image);//finish image
}

//This function creates a blank canvas of structs based on a given height and width
rgb_data ** getBlankCanvas(int width, int height) {
	struct rgb_data ** canvas = new rgb_data*[height];
	for (int i = 0; i < height; i++) {
		canvas[i] = new rgb_data[width];
	}

	return canvas;
}

int randRBG() {
	return rand() % 256;
}

void runTest() {
	int width = 256;
	int height = 256;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y].r = x;
			pixels[x][y].g = 255 - x;
			pixels[x][y].b = 255 - y;
			pixels[x][y].a = 128;
		}
	}

	rgb_data color;
	color.a = 255;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	Draw::drawLine(color, 0, 0, 255, 255, pixels);
	Draw::drawLine(color, 0, 128, 256, 128, pixels);
	Draw::drawLine(color, 0, 256, 256, 0, pixels);
	Draw::drawLine(color, 128, 0, 128, 256, pixels);
	Draw::drawCircle(color, 128, 128, 5, pixels);
	Draw::drawCircle(color, 128, 128, 10, pixels);
	Draw::drawCircle(color, 128, 128, 15, pixels);
	Draw::drawCircle(color, 128, 128, 20, pixels);
	Draw::drawCircle(color, 128, 128, 25, pixels);
	Draw::drawCircle(color, 128, 128, 30, pixels);
	Draw::drawCircle(color, 128, 128, 35, pixels);
	Draw::drawRectangle(color, 0, 0, 64, 64, true, pixels);
	Draw::drawRectangle(color, 0, 255, 64, 192, true, pixels);
	Draw::drawRectangle(color, 255, 0, 192, 64, true, pixels);
	Draw::drawRectangle(color, 255, 255, 192, 192, true, pixels);
	Draw::drawRectangle(color, 64, 64, 192, 192, false, pixels);

	save_bitmap("Test Image.bmp", width, height, pixels);
}

void runTest2() {
	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y].r = 255;
			pixels[x][y].g = 255;
			pixels[x][y].b = 255;
			pixels[x][y].a = 255;
		}
	}

	rgb_data color;
	color.a = 64;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	pixels = FractalSquare::drawFractalSquare(width, color, pixels);

	save_bitmap("Test Fractal.bmp", width, height, pixels);
}

void runTest3() {
	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y].r = 255;
			pixels[x][y].g = 255;
			pixels[x][y].b = 255;
			pixels[x][y].a = 255;
		}
	}

	
	pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

	save_bitmap("Test Fractal x 3 1st.bmp", width, height, pixels);

	pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

	save_bitmap("Test Fractal x 3 2nd.bmp", width, height, pixels);

	pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

	save_bitmap("Test Fractal x 3 3rd.bmp", width, height, pixels);
}

void runTest4() {

	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y].r = 255;
			pixels[x][y].g = 255;
			pixels[x][y].b = 255;
			pixels[x][y].a = 255;
		}
	}

	rgb_data color;
	color.a = 255;
	color.r = 0;
	color.g = 0;
	color.b = 0;

	pixels = RandomLines::randomLines(width, 10000, color, pixels);

	save_bitmap("Test RndmLines 1k.bmp", width, height, pixels);

}

void runTest5() {

	int width = 256;
	int height = 256;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	pixels = RandomPixels::randomPixels(width,pixels);

	save_bitmap("RandomPixels.bmp", width, height, pixels);

	pixels = getBlankCanvas(width, height);

	pixels = RandomPixels::randomPixels2(width, pixels);

	save_bitmap("RandomPixels2.bmp", width, height, pixels);

	pixels = getBlankCanvas(width, height);

	pixels = RandomPixels::randomPixels3(width, pixels);

	save_bitmap("RandomPixels3.bmp", width, height, pixels);

}

void runTest6() {

	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	pixels = RandomPixels::randomPixels(width, pixels);
	rgb_data color;
	color.a = 255;
	color.r = 64;
	color.g = 64;
	color.b = 64;
	pixels = FractalSquare::drawFractalSquare(width, color, pixels);

	save_bitmap("RandomPixelsFractalSquare.bmp", width, height, pixels);

}

void runTest7() {

	int width = 1024;
	int height = 1024;

	int shift = 2;
	int iterations = 500;

	for (int i = 0; i < 5; i++) {

		struct rgb_data ** pixels = getBlankCanvas(width, height);

		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				pixels[x][y].r = 255;
				pixels[x][y].g = 255;
				pixels[x][y].b = 255;
				pixels[x][y].a = 255;
			}
		}

		int lines[2][4] = { {500,64,500,960},{524,64,524,960} };

		pixels = LineWalk::lineWalk(lines, width, shift, iterations, pixels);

		std::string filestring = "Line_Walk_" + to_string(i + 1) + ".bmp";

		const char *filename = filestring.c_str();

		save_bitmap(filename, width, height, pixels);

		shift *= 2;
		iterations *= 2;
	}

}

//fractal square with alpha test
void runTest8() {
	int width = 1024;
	int height = 1024;

	for (int i = 1; i <= 5; i++) {
		struct rgb_data ** pixels = getBlankCanvas(width, height);

		rgb_data color = Color::lessRandom();

		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				pixels[x][y] = color;
			}
		}

		std::string filestring = "Fractal_Alpha_" + to_string(i) + "_1st.bmp";

		const char *filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandomTransparent(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_Alpha_" + to_string(i) + "_2nd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandomTransparent(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_Alpha_" + to_string(i) + "_3rd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandomTransparent(), pixels);

		save_bitmap(filename, width, height, pixels);

	}
}

//fractal square with "less random" colors
void runTest9() {
	int width = 1024;
	int height = 1024;

	for (int i = 1; i <= 5; i++) {
		struct rgb_data ** pixels = getBlankCanvas(width, height);

		rgb_data color = Color::lessRandom();

		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				pixels[x][y] = color;
			}
		}

		std::string filestring = "Fractal_LessRndm_" + to_string(i) + "_1st.bmp";

		const char *filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_LessRndm_" + to_string(i) + "_2nd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_LessRndm_" + to_string(i) + "_3rd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

	}
}


void runTest10() {
	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y] = WHITE;
		}
	}

	pixels = CirclePacking::packCircles(width, BLACK, pixels);

	save_bitmap("CirclePackTest.bmp", width, height, pixels);
}

void runTest11() {
	int width = 1024;
	int height = 1024;

	struct rgb_data ** pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[x][y] = WHITE;
		}
	}

	pixels = CirclePacking::packFilledCircles(width, BLACK, pixels);

	save_bitmap("FilledCirclePackTest.bmp", width, height, pixels);
}

//fractal square with circles test
void runTest12() {
	int width = 1024;
	int height = 1024;

	for (int i = 1; i <= 5; i++) {
		struct rgb_data ** pixels = getBlankCanvas(width, height);

		rgb_data color = Color::lessRandom();

		for (int y = 0; y < width; y++) {
			for (int x = 0; x < height; x++) {
				pixels[x][y] = color;
			}
		}

		std::string filestring = "Fractal_Circles_" + to_string(i) + "_1st.bmp";

		const char *filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_Circles_" + to_string(i) + "_2nd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquare(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

		filestring = "Fractal_Circles_" + to_string(i) + "_3rd.bmp";

		filename = filestring.c_str();

		pixels = FractalSquare::drawFractalSquareWithCircles(width, Color::lessRandom(), pixels);

		save_bitmap(filename, width, height, pixels);

	}
}

//The main function; used for manipulating the canvas and directing the program.
int main() {

	bool quits = false;
	int input = -1;

	while (!quits) {
		input = -1;
		cout << endl << "Main Menu: " << endl;
		cout << "\t[0]: Quit" << endl;
		cout << "\t[1]: Run Test" << endl;
		cout << "\t[2]: Fractal Squares" << endl;
		cout << "\t[3]: Fractal Squares * 3" << endl;
		cout << "\t[4]: Random Lines" << endl;
		cout << "\t[5]: Random Pixels" << endl;
		cout << "\t[6]: Random Pixels + Fractal Squares" << endl;
		cout << "\t[7]: Line Walk" << endl;
		cout << "\t[8]: Fractal With Alpha Test" << endl;
		cout << "\t[9]: Fractal With Less Random Colors" << endl;
		cout << "\t[10]: Circle Packing Test" << endl;
		cout << "\t[11]: Filled Circle Packing Test" << endl << "\t\t^^^Warning: Very Slow!" << endl;
		cout << "\t[12]: Fractal Squares With Circles" << endl;

		cout << endl << "Please enter the number of a choice above: ";
		cin >> input;
		if (input > 12 || input < 0) {
			cout << "Invalid input; please try again.";
			input = -1;
		}

		switch (input) {
		case 0:
			quits = true;
			break;
		case 1:
			cout << endl << "Running test" << endl;
			runTest();
			cout << "Test image completed; saved as 'TestImage.bmp'" << endl;
			break;
		case 2:
			cout << endl << "Running Fractal Squares" << endl;
			runTest2();
			break;
		case 3:
			cout << endl << "Running Fractal Squares * 3" << endl;
			runTest3();
			break;
		case 4:
			cout << endl << "Running Random Lines" << endl;
			runTest4();
			break;
		case 5:
			cout << endl << "Running Random Pixels" << endl;
			runTest5();
			break;
		case 6:
			cout << endl << "Random Pixels + Fractal Squares" << endl;
			runTest6();
			break;
		case 7:
			cout << endl << "Running Line Walk" << endl;
			runTest7();
			break;
		case 8:
			cout << endl << "Running Fractal with Alpha test" << endl;
			runTest8();
			break;
		case 9:
			cout << endl << "Running Fractal with Less Random Colors" << endl;
			runTest9();
			break;
		case 10:
			cout << endl << "Running Circle Packing test" << endl;
			runTest10();
			break;
		case 11:
			cout << endl << "Running Filled Circle Packing test" << endl;
			runTest11();
			break;
		case 12:
			cout << endl << "Running Fractal with Circle test" << endl;
			runTest12();
			break;
		default:
			break;
		}
	}

	//runTest();
	return 0;
}