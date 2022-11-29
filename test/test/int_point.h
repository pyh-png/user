#pragma once
//∫∏µ„¿‡
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>

#include <iostream>
#include <random>
#include<vector>

using namespace std;
using namespace cv;

class handian {
public:
	Point2f points;
	Rect rect;
	void write();
};