#pragma once
//һ��ͼ������

#include <iostream>
#include <random>
#include "threadpool.h"
#include<vector>
#include<opencv2\opencv.hpp>

using namespace std;
using namespace cv;


/**
* @brief ͼ��Ԥ��������
* @param res_thΪ����ķ���ֵͼͼ��mask_handian1,2,3Ϊ�������ʹ����ĺ���ͼ��
* @param th_area��ֵ��С����ֵ������������
* @param  res_thΪ��������ǰ��ͼ��
*/

void polyimage(Mat &res_th, Mat mask_handian1, Mat mask_handian2, Mat mask_handian3, int th_area);