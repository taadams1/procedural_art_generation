#pragma once

#include <iostream>
#include<vector>
#include <array>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <chrono>
#include <io.h>
#include <fcntl.h>
#include <fstream>
#include <cwchar>

using namespace std;

class FractalSquare
{
private:
	static wstring generateString(int);
	static void drawFS(vector<vector<wchar_t>> &,int, int, int, int);
public:
	FractalSquare();
	~FractalSquare();
	static void drawFractalSquare(int, vector<vector<wchar_t>> &);
	static void print(vector<vector<wchar_t>> &, int, int);
};

