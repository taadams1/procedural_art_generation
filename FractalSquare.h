#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <cwchar>

#include "Draw.h"

using namespace std;

class FractalSquare
{
private:
	static wstring generateString(int);
public:
	static rgb_data ** drawFractalSquare(int, rgb_data, rgb_data **);
	static rgb_data ** drawFractalSquareWithCircles(int, rgb_data, rgb_data **);
};

