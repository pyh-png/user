#pragma once
//滤波器函数

#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace std;
using namespace cv;
#define PROCESS_IMG_SUCESS 0
#define PROCESS_IMG_FAIL 1


namespace ImgEnhance
{
	//滤波
	class Filter
	{
	public:
		Filter() { cout << "Filter is being created" << endl; } // 这是构造函数声明
		~Filter() { cout << "Filter is being deleted" << endl; } // 这是析构函数声明
		int MeanFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize);//均值滤波
		int GaussFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize, int xValue, int yValue);//高斯滤波
		int MedianFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize);//中值滤波
		int BilateralFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaRadio, int limitValue, int unuseValue);//双边滤波
																												//高通滤波：边缘提取与增强//低通滤波：边缘平滑
		int HighPassFilter(cv::Mat srcImage, cv::Mat &dstImage);//高通滤波
		int LowPassFilter(cv::Mat srcImage, cv::Mat &dstImage);//低通滤波
	};

}
