//bitmap creation example taken from http://ricardolovelace.com/creating-bitmap-images-with-c-on-windows.html and adapted for use by Jesse Uchytil, 3-26-19


#include <fstream>
#include <iostream>
#include <cstdio>

using namespace std;

//A struct containing each color channel, used as part of a canvas to be saved into a bitmap.
struct rgb_data { float r, g, b, a; };

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

	for (int i = height; i > -1; i--) {//for each pixel in the height of the canvas (starting from end of array to allow for standard upper-right-corner origin in computer graphics, something bitmaps don't do normally.)
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

//Base sourced from https://www.thecrazyprogrammer.com/2017/01/dda-line-drawing-algorithm-c-c.html
void drawLine(rgb_data color, int x1, int y1, int x2, int y2, rgb_data ** canvas){
	int swap = 0;
	if(x1 > x2){
		swap = x1;
		x1 = x2;
		x2 = swap;
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	if(x1 == x2 && y1 > y2){
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	float dx = 1.0*(x2 - x1);
	float dy = 1.0*(y2 - y1);
	float length = 0;
	int i = 0;
	
	if(dx >= dy){
		length = dx;
	}else{
		length = dy;
	}
	
	dx = dx/length;
	dy = dy/length;
	
	float x = x1;
	float y = y1;
	
	for(int i = 0; i < length; i++){
		canvas[(int)x][(int)y] = color;
		x += dx;
		y += dy;
	}
}

//base sourced from https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html
void drawCircle(rgb_data color, int xCenter, int yCenter, int radius, rgb_data ** canvas){
	int x = radius;
	int y = 0;
	int err = 0;
	while(x >= y){
		canvas[xCenter + x][yCenter + y] = color;
		canvas[xCenter + y][yCenter + x] = color;
		canvas[xCenter - x][yCenter + y] = color;
		canvas[xCenter - y][yCenter + x] = color;
		canvas[xCenter - x][yCenter - y] = color;
		canvas[xCenter - y][yCenter - x] = color;
		canvas[xCenter + x][yCenter - y] = color;
		canvas[xCenter + y][yCenter - x] = color;
		
		if(err <= 0){
			y+= 1;
			err += 2*y + 1;
		}
		
		if(err > 0){
			x -= 1;
			err -= 2*x + 1;
		}
	}
}

void drawRectangle(rgb_data color, int x1, int y1, int x2, int y2, bool fill, rgb_data ** canvas){
	int swap = 0;
	if(x1 < x2 && y1 > y2){
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	if(x1 > x2 && y1 < y2){
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	if(x1 > x2 && y1 > y2){
		swap = x1;
		x1 = x2;
		x2 = swap;
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	drawLine(color, x1, y1, x2, y1, canvas);
	drawLine(color, x2, y1, x2, y2, canvas);
	drawLine(color, x2, y2, x1, y2, canvas);
	drawLine(color, x1, y2, x1, y1, canvas);
	if(fill){
		for(int i = 0; i < (y2 - y1); i++){
			drawLine(color, x1, y1+i, x2, y1+i, canvas);
		}
	}
}

//This function creates a blank canvas of structs based on a given height and width
rgb_data ** getBlankCanvas(int width, int height) {
	struct rgb_data ** canvas = new rgb_data*[height];
	for (int i = 0; i < height; i++) {
		canvas[i] = new rgb_data[width];
	}

	return canvas;
}

void runTest(){
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
	
	drawLine(color, 0, 0, 255, 255, pixels);
	drawLine(color, 0, 128, 256, 128, pixels);
	drawLine(color, 0, 256, 256, 0, pixels);
	drawLine(color, 128, 0, 128, 256, pixels);
	drawCircle(color, 128, 128, 5, pixels);
	drawCircle(color, 128, 128, 10, pixels);
	drawCircle(color, 128, 128, 15, pixels);
	drawCircle(color, 128, 128, 20, pixels);
	drawCircle(color, 128, 128, 25, pixels);
	drawCircle(color, 128, 128, 30, pixels);
	drawCircle(color, 128, 128, 35, pixels);
	drawRectangle(color, 0, 0, 64, 64, true, pixels);
	drawRectangle(color, 0, 255, 64, 192, true, pixels);
	drawRectangle(color, 255, 0, 192, 64, true, pixels);
	drawRectangle(color, 255, 255, 192, 192, true, pixels);
	drawRectangle(color, 64, 64, 192, 192, false, pixels);

	save_bitmap("Test Image.bmp", width, height, pixels);
}

//The main function; used for manipulating the canvas and directing the program.
int main() {
	bool quits = false;
	int input = -1;
	
	while(!quits){
		input = -1;
		cout << endl << "Main Menu: " << endl;
		cout << "\t[0]: Quit" << endl;
		cout << "\t[1]: Run Test" << endl;
		
		cout << endl << "Please enter the number of a choice above: ";
		cin >> input;
		if(input > 1 || input < 0){
			cout << "Invalid input; please try again.";
			input = -1;
		}
		
		switch(input){
			case 0: 
				quits = true;
				break;
			case 1:
				cout << endl << "Running test" << endl;
				runTest();
				cout << "Test image completed; saved as 'TestImage.bmp'" << endl;
				break;
			default:
				break;
		}
	}
	
	runTest();
	return 0;
}
