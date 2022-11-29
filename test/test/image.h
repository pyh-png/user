#pragma once
//一般图像处理函数

#include <iostream>
#include <random>
#include "threadpool.h"
#include<vector>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;


/**
* @brief 图像预处理并反向
* @param res_th为输入的反二值图图像，mask_handian1,2,3为三种膨胀处理后的焊点图像
* @param th_area阈值，小于阈值的区域进行填充
* @param  res_th为最后输出的前景图像
*/

void polyimage(Mat &res_th, Mat mask_handian1, Mat mask_handian2, Mat mask_handian3, int th_area);