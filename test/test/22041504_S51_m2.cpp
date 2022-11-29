// 01_Combine_Two_Images.cpp 
// ���� VS2017 + OpenCV4.4.0
// ���ܽ��ܣ����ڽ�����ͼƬƴ�ӳ�һ�Ŵ�ͼ(������ƴ��Ϊ��)���׳Ƶ�Ӳƴ����
// �ص㣺�򵥴ֱ�����ʵӦ�ö���������Ҫ����̣������Բ�
#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <string>

#include <iostream>
#include <random>
#include "threadpool.h"
#include<vector>
#include"int_point.h"
#include"filter.h"
#include"line.h"
#include"image.h"
#include"get_image.h"
#include"handian.h"


using namespace std;
using namespace cv;
using namespace ImgEnhance;


int main()
{
	std::string folder_path = "F:\\dariy\\handian\\22041504_S51_jpg\\m2\\*.*"; //path of folder, you can replace "*.*" by "*.jpg" or "*.png"
	std::string path = "F:\\dariy\\handian\\22041504_S51_jpg\\m2\\";
	//22041504_S51_jpg,22070110_LN7_jpg
	Mat res = get_image(folder_path, path);//�ϲ���ת��Ϊ�Ҷ�ͼ
	
	Rect rect_ROI; //�ü�
	
	Mat mask_handian; //�ܺ����ͼ

	Mat res_th; 
	Mat mask_handian_min, mask_handian_mid, mask_handian_max;//�����������ͼ
	
	vector<handian> dst = init_point(res, mask_handian, mask_handian_min, mask_handian_mid, mask_handian_max, rect_ROI);

	//Mat temp = res(rect_ROI1);
	Mat res_fliter;
	Filter I;

	I.MeanFilter(res, res_fliter, 7);

	cv::threshold(res_fliter, res_th, 90, 255, cv::THRESH_BINARY_INV);
	//�ֱ����Ͳ���
	Mat se1 = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(17, 17));
	dilate(mask_handian_max, mask_handian_max, se1, cv::Point(-1, -1), 2); //ִ�����Ͳ���


	Mat se2 = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(15, 15));
	dilate(mask_handian_mid, mask_handian_mid, se2, cv::Point(-1, -1), 2); //ִ�����Ͳ���

	Mat se3 = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5));
	dilate(mask_handian_min, mask_handian_min, se3, cv::Point(-1, -1), 2); //ִ�����Ͳ���

	polyimage(res_th, mask_handian_min, mask_handian_mid, mask_handian_max, 5000);
	
	Mat se = cv::getStructuringElement(MORPH_RECT, cv::Size(5, 5));
	erode(res_th, res_th, se, cv::Point(-1, -1));

	Mat res_th1 = res_th / 255;

	Mat dst1 = thinImage(res_th1, -1);
	//����ϸ�����ͼ�� 
	filterOver(dst1);

	//���Ҷ˵�,�����    
	std::vector<cv::Point> points = getPoints(dst1, 6, 9, 5);


	dst1 = dst1 * 255;
	res_th = res_th - dst1;


	imwrite("res_th.jpg", res_th);
	//waitKey(0);
	return 0;
}