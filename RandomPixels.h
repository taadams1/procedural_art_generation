#pragma once

#include <cstdio>
#include <chrono>

#include "Draw.h"

class RandomPixels
{
public:
	static rgb_data ** randomPixels(int size, rgb_data ** canvas) {

		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				canvas[x][y].r = randRBG();
				canvas[x][y].g = randRBG();
				canvas[x][y].b = randRBG();
				canvas[x][y].a = 255;
			}
		}

		return canvas;
	}

	/*int colorAvg1 = 1.0;

	function createImage2() {

		for (int x = 0; x < size; x++) {

			for (int y = 0; y < size; y++) {

				int pixelIndex = (y * size + x) * 4;

				int redVal = randomRGBVal() * colorAvg1; int greenVal = randomRGBVal() * colorAvg1;
				int blueVal = randomRGBVal() * colorAvg1;
				imageData2.data[pixelIndex] = redVal;
				imageData2.data[pixelIndex + 1] = greenVal;
				imageData2.data[pixelIndex + 2] = blueVal;
				imageData2.data[pixelIndex + 3] = 255;

				colorAvg1 = (redVal + greenVal + blueVal) / 3 / 127.5;
				if (colorAvg1 < 0.5) { colorAvg1 += 0.4; }
				else if (colorAvg1 > 1.5) { colorAvg1 -= 0.4; }
			}
		}

		context2.putImageData(imageData2, 0, 0);
	}

	function createImage3() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal();
				int greenVal = randomRGBVal();
				int blueVal = randomRGBVal();

				for (int a = x; a < x + 4; a++) {

					for (int b = y; b < y + 4; b++) {

						int pixelIndex = (a * size + b) * 4;

						imageData3.data[pixelIndex] = redVal;
						imageData3.data[pixelIndex + 1] = greenVal;
						imageData3.data[pixelIndex + 2] = blueVal;
						imageData3.data[pixelIndex + 3] = 255;

					}
				} y += 4;
			}x += 4;
		}

		context3.putImageData(imageData3, 0, 0);
	}

	int colorAvg2 = 0.0;

	function createImage4() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg2;
				int greenVal = randomRGBVal() * colorAvg2;
				int blueVal = randomRGBVal() * colorAvg2;

				for (int a = x; a < x + 4; a++) {

					for (int b = y; b < y + 4; b++) {

						int pixelIndex = (a * size + b) * 4;

						imageData4.data[pixelIndex] = redVal;
						imageData4.data[pixelIndex + 1] = greenVal;
						imageData4.data[pixelIndex + 2] = blueVal;
						imageData4.data[pixelIndex + 3] = 255;

						colorAvg2 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg2 < 0.5) {
							colorAvg2 += 0.4;
						}
						else if (colorAvg2 > 1.5) {
							colorAvg2 -= 0.4;
						}

					}
				} y += 4;
			}x += 4;
		}

		context4.putImageData(imageData4, 0, 0);
	}

	int colorAvg3 = 0.1;

	function createImage5() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg3;
				int greenVal = randomRGBVal() * colorAvg3;
				int blueVal = randomRGBVal() * colorAvg3;

				for (int a = x; a < x + 8; a++) {

					for (int b = y; b < y + 8; b++) {

						int pixelIndex = (a * size + b) * 4;

						imageData5.data[pixelIndex] = redVal;
						imageData5.data[pixelIndex + 1] = greenVal;
						imageData5.data[pixelIndex + 2] = blueVal;
						imageData5.data[pixelIndex + 3] = 255;

						colorAvg3 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg3 < 0.2) {
							colorAvg3 += 0.3;
						}
						else if (colorAvg3 > 1.6) {
							colorAvg3 -= 0.3;
						}

					}
				} y += 8;
			}x += 8;
		}

		context5.putImageData(imageData5, 0, 0);
	}

	int colorAvg4 = 0.1;

	function createImage6() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg4;
				int greenVal = randomRGBVal() * colorAvg4;
				int blueVal = randomRGBVal() * colorAvg4;

				for (int a = x; a < x + 8; a++) {

					for (int b = y; b < y + 8; b++) {

						int pixelIndex = (a * size + b) * 4;

						imageData6.data[pixelIndex] = redVal;
						imageData6.data[pixelIndex + 1] = greenVal;
						imageData6.data[pixelIndex + 2] = blueVal;
						imageData6.data[pixelIndex + 3] = 255;

						//colorAvg4 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg4 < 0.4) {
							colorAvg4 = 3;
						}
						if (colorAvg4 <= 3) {
							int rand = Math.random() * 1.2;
							colorAvg4 -= rand;
						}

					}
				} y += 8;
			}x += 8;
		}

		context6.putImageData(imageData6, 0, 0);
	}

	int colorAvg5 = 1.0;

	function createImage7() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg5;
				int greenVal = randomRGBVal() * colorAvg5;
				int blueVal = randomRGBVal() * colorAvg5;

				for (int a = x; a < x + 4; a++) {

					for (int b = y; b < y + 4; b++) {

						int pixelIndex = (a * size + b) * 4;

						imageData7.data[pixelIndex] = redVal;
						imageData7.data[pixelIndex + 1] = greenVal;
						imageData7.data[pixelIndex + 2] = blueVal;
						imageData7.data[pixelIndex + 3] = 255;

						colorAvg5 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg5 > 0) {
							colorAvg5 -= (Math.sin(colorAvg5));
						}
						else if (colorAvg5 <= 0) {
							colorAvg5 = 2.0;
						}

					}
				} y += 4;
			}x += 4;
		}

		context7.putImageData(imageData7, 0, 0);
	}

	int colorAvg6 = 1.0;

	function createImage8() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg6;
				int greenVal = randomRGBVal() * colorAvg6;
				int blueVal = randomRGBVal() * colorAvg6;

				for (int a = x; a < x + 2; a++) {

					for (int b = y; b < y + 2; b++) {

						int pixelIndex = (b * size + a) * 4;

						imageData8.data[pixelIndex] = redVal;
						imageData8.data[pixelIndex + 1] = greenVal;
						imageData8.data[pixelIndex + 2] = blueVal;
						imageData8.data[pixelIndex + 3] = 255;

						colorAvg6 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg6 > 0) {
							colorAvg6 -= (Math.sin(colorAvg6));
						}
						else if (colorAvg6 <= 0) {
							colorAvg6 = 2.0;
						}

					}
				} y += 2;
			}x += 2;
		}

		context8.putImageData(imageData8, 0, 0);
	}

	int colorAvg7 = 1.0;

	function createImage9() {

		for (int x = 0; x < size;) {

			for (int y = 0; y < size;) {

				int redVal = randomRGBVal() * colorAvg7;
				int greenVal = randomRGBVal() * colorAvg7;
				int blueVal = randomRGBVal() * colorAvg7;

				for (int a = x; a < x + 2; a++) {

					for (int b = y; b < y + 2; b++) {

						int pixelIndex = (b * size + a) * 4;

						imageData9.data[pixelIndex] = redVal;
						imageData9.data[pixelIndex + 1] = greenVal;
						imageData9.data[pixelIndex + 2] = blueVal;
						imageData9.data[pixelIndex + 3] = 255;

						colorAvg7 = (redVal + greenVal + blueVal) / 3 / 127.5;
						if (colorAvg7 < 2.2) {
							colorAvg7 += (Math.cos(colorAvg7));
						}
						else if (colorAvg7 >= 2.2) {
							colorAvg7 = 0.1;
						}

					}
				} y += 2;
			}x += 2;
		}

		context9.putImageData(imageData9, 0, 0);
	}*/

static int randRBG() {
	return rand() % 256;
}
};
