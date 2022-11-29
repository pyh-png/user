#pragma once
#include<iostream>
#include<opencv2\opencv.hpp>
#include<vector>
#include <iostream>
#include <math.h>
#include <string>
#include "threadpool.h"

using namespace std;
using namespace cv;

//将文件夹中图像拼接获取芯片图像

/**
* @brief 利用坐标进行图像拼接
* @param dst为最终芯片图像，a，b为图像坐标，与beginrow和begincol进行计算准确图像
* @param scale为缩放比例默认为3，path1为父路径。
*/
void fix(cv::Mat &dst, const int beginrow, const int begincol, const int a, const int b, int scale, std::string pathf);


/**
* @brief 利用线程池进行各个位置的分别拼接
* @param scale为设置的缩放比例，maxrow,maxcol为最大长宽，beginrow，begincol默认为0，可以设置值进行区域调试
* @param path图片父路径容易进行拼接。
* @return 线程池拼接图像
*/
Mat splic(int maxrow, int maxcol, int scale, std::string path, int beginrow=0, int begincol=0);

/**
* @brief 对string进行分离存入数组，与路径结合使用
* @param str为输入字符串
* @param split为分割字符
* @return 以split为分割依据的string元素
*/
vector<string> Stringsplit(string str, const const char split);

/**
* @brief 将路径中芯片图像进行拼接
* @param floder子路径全局	示例folder_path = "。。。\\22041504_S51_jpg\\m2\\*.*";  
* @param path为父路径 path = "。。。\\22041504_S51_jpg\\m2\\";scale为缩放比例
* @return 芯片图像
*/
Mat get_image(std::string folder_path, std::string path,int scale=3);