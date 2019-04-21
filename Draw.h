#pragma once

#include "Color.h"

class Draw
{
public:
	//Base sourced from https://www.thecrazyprogrammer.com/2017/01/dda-line-drawing-algorithm-c-c.html
	static void drawLine(rgb_data color, int x1, int y1, int x2, int y2, rgb_data ** canvas) {
		int swap = 0;
		if (x1 > x2) {
			swap = x1;
			x1 = x2;
			x2 = swap;
			swap = y1;
			y1 = y2;
			y2 = swap;
		}
		if (x1 == x2 && y1 > y2) {
			swap = y1;
			y1 = y2;
			y2 = swap;
		}
		float dx = 1.0*(x2 - x1);
		float dy = 1.0*(y2 - y1);
		float length = 0;
		int i = 0;

		if (dx >= dy) {
			length = dx;
		}
		else {
			length = dy;
		}

		dx = dx / length;
		dy = dy / length;

		float x = x1;
		float y = y1;

		for (int i = 0; i < length; i++) {
			canvas[(int)x][(int)y] = Color::mixAlpha(canvas[(int)x][(int)y], color);
			x += dx;
			y += dy;
		}
	}

	//base sourced from https://www.thecrazyprogrammer.com/2016/12/bresenhams-midpoint-circle-algorithm-c-c.html
	static void drawCircle(rgb_data color, int xCenter, int yCenter, int radius, rgb_data ** canvas) {
		int x = radius;
		int y = 0;
		int err = 0;
		while (x >= y) {
			canvas[xCenter + x][yCenter + y] = color;
			canvas[xCenter + y][yCenter + x] = color;
			canvas[xCenter - x][yCenter + y] = color;
			canvas[xCenter - y][yCenter + x] = color;
			canvas[xCenter - x][yCenter - y] = color;
			canvas[xCenter - y][yCenter - x] = color;
			canvas[xCenter + x][yCenter - y] = color;
			canvas[xCenter + y][yCenter - x] = color;

			if (err <= 0) {
				y += 1;
				err += 2 * y + 1;
			}

			if (err > 0) {
				x -= 1;
				err -= 2 * x + 1;
			}
		}
	}

	static void drawRectangle(rgb_data color, int x1, int y1, int x2, int y2, bool fill, rgb_data ** canvas) {
		int swap = 0;
		if (x1 < x2 && y1 > y2) {
			swap = y1;
			y1 = y2;
			y2 = swap;
		}
		if (x1 > x2 && y1 < y2) {
			swap = y1;
			y1 = y2;
			y2 = swap;
		}
		if (x1 > x2 && y1 > y2) {
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
		if (fill) {
			for (int i = 0; i < (y2 - y1); i++) {
				drawLine(color, x1, y1 + i, x2, y1 + i, canvas);
			}
		}
	}
};

