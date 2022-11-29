#pragma once
//������ȡ����
#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>
#include"int_point.h"

using namespace std;
using namespace cv;

/**
* @brief ���뺸�����ɸѡ
* @param dst1Ϊ���뺸��ͼ��ͼ�������������ĺ���ͼ��small��mid,max
* @param th_areaΪmid��max����ֵ��th_area_minΪsmall��mid����ֵ
* @return ��ȡ���ֲ�ͬ����ĺ���ͼ��
*/
void image_tep(cv::Mat &dst1, cv::Mat &small, cv::Mat &mid, cv::Mat &max, int th_area, int th_area_min = 0);

/**
* @brief ��ȡ��������
* @param imageΪ����ͼ��8λ�Ҷ�ͼ��dstΪ���к���ͼ��rect_POIȥ��оƬ��Χ��Ӱ��
* @param ���������Χ������Ŀ��Ϊ��������
* @param hd_min�ٺ����Ϊ2-4����hd_midС������㣬hd_maxΪ��������㣬�����������ں����ֱ�����
* @return �������ṹ�壬����������������Ӿ���
*/
vector<handian> init_point(Mat image, Mat &dst, cv::Mat &hd_min, Mat &hd_mid, cv::Mat &hd_max, Rect &rect_POI);