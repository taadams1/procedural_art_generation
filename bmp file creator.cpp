//bitmap creation example taken from http://ricardolovelace.com/creating-bitmap-images-with-c-on-windows.html and adapted for use by Jesse Uchytil, 3-26-19

#include <fstream>
#include <cstdio>

using namespace std;

struct rgb_data { float r, g, b, a; };

void save_bitmap(const char * file_name, int width, int height, int dpi, rgb_data ** pixel_data)
{
	FILE *image;
	int image_size = width * height;
	int file_size = 54 + 4 * image_size;
	int ppm = dpi * 39.375;

	struct bitmap_file_header {
		unsigned char bitmap_type[2];
		int file_size;
		short reserved1;
		short reserved2;
		unsigned int offset_bits;
	} bfh;

	struct bitmap_image_header {
		unsigned int size_header;
		unsigned int width;
		unsigned int height;
		short int planes;
		short int bit_count;
		unsigned int compression;
		unsigned int image_size;
		unsigned int ppm_x;
		unsigned int ppm_y;
		unsigned int clr_used;
		unsigned int clr_important;
	} bih;

	memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size = file_size;
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

	image = fopen(file_name, "wb");

	fwrite(&bfh, 1, 14, image);
	fwrite(&bih, 1, sizeof(bih), image);

	for (int i = height; i > -1; i--) {
		for (int j = 0; j < width; j++) {
			rgb_data BGR = pixel_data[j][i];

			float red = (BGR.r);
			float green = (BGR.g);
			float blue = (BGR.b);
			float alpha = (BGR.a);

			unsigned char color[4] = {
			   blue, green, red, alpha
			};
			fwrite(color, 1, sizeof(color), image);
		}

	}

	fclose(image);
}

 rgb_data ** getBlankCanvas(int width, int height)
{
	struct rgb_data ** canvas = new rgb_data*[height];
	for (int i = 0; i < height; i++) {
		canvas[i] = new rgb_data[width];
	}

	return canvas;
}

int main() {
	int width = 255;
	int height = 256;
	int dpi = 96;

	struct rgb_data **pixels = getBlankCanvas(width, height);

	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			pixels[y][x].r = x;
			pixels[y][x].g = 255 - x;
			pixels[y][x].b = 255 - y;
			pixels[y][x].a = 128;
		}
	}

	save_bitmap("simple gradiant.bmp", width, height, dpi, pixels);
	return 0;
}
