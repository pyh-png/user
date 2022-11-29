#pragma once
//焊点提取函数
#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>
#include"int_point.h"

using namespace std;
using namespace cv;

/**
* @brief 输入焊点进行筛选
* @param dst1为输入焊点图像图像输出三种面积的焊点图像small，mid,max
* @param th_area为mid与max的阈值，th_area_min为small与mid的阈值
* @return 获取三种不同处理的焊点图像
*/
void image_tep(cv::Mat &dst1, cv::Mat &small, cv::Mat &mid, cv::Mat &max, int th_area, int th_area_min = 0);

/**
* @brief 提取焊点区域
* @param image为输入图像，8位灰度图，dst为所有焊点图，rect_POI去除芯片外围的影响
* @param 焊点根据周围焊点数目分为三种区域：
* @param hd_min少焊点多为2-4个，hd_mid小面积焊点，hd_max为大面积焊点，三种区域利于后续分别膨胀
* @return 输出焊点结构体，包含中心坐标与外接矩形
*/
vector<handian> init_point(Mat image, Mat &dst, cv::Mat &hd_min, Mat &hd_mid, cv::Mat &hd_max, Rect &rect_POI);