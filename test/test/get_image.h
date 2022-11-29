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

//���ļ�����ͼ��ƴ�ӻ�ȡоƬͼ��

/**
* @brief �����������ͼ��ƴ��
* @param dstΪ����оƬͼ��a��bΪͼ�����꣬��beginrow��begincol���м���׼ȷͼ��
* @param scaleΪ���ű���Ĭ��Ϊ3��path1Ϊ��·����
*/
void fix(cv::Mat &dst, const int beginrow, const int begincol, const int a, const int b, int scale, std::string pathf);


/**
* @brief �����̳߳ؽ��и���λ�õķֱ�ƴ��
* @param scaleΪ���õ����ű�����maxrow,maxcolΪ��󳤿�beginrow��begincolĬ��Ϊ0����������ֵ�����������
* @param pathͼƬ��·�����׽���ƴ�ӡ�
* @return �̳߳�ƴ��ͼ��
*/
Mat splic(int maxrow, int maxcol, int scale, std::string path, int beginrow=0, int begincol=0);

/**
* @brief ��string���з���������飬��·�����ʹ��
* @param strΪ�����ַ���
* @param splitΪ�ָ��ַ�
* @return ��splitΪ�ָ����ݵ�stringԪ��
*/
vector<string> Stringsplit(string str, const const char split);

/**
* @brief ��·����оƬͼ�����ƴ��
* @param floder��·��ȫ��	ʾ��folder_path = "������\\22041504_S51_jpg\\m2\\*.*";  
* @param pathΪ��·�� path = "������\\22041504_S51_jpg\\m2\\";scaleΪ���ű���
* @return оƬͼ��
*/
Mat get_image(std::string folder_path, std::string path,int scale=3);