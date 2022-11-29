#pragma once
//�˲�������

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
	//�˲�
	class Filter
	{
	public:
		Filter() { cout << "Filter is being created" << endl; } // ���ǹ��캯������
		~Filter() { cout << "Filter is being deleted" << endl; } // ����������������
		int MeanFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize);//��ֵ�˲�
		int GaussFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize, int xValue, int yValue);//��˹�˲�
		int MedianFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize);//��ֵ�˲�
		int BilateralFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaRadio, int limitValue, int unuseValue);//˫���˲�
																												//��ͨ�˲�����Ե��ȡ����ǿ//��ͨ�˲�����Եƽ��
		int HighPassFilter(cv::Mat srcImage, cv::Mat &dstImage);//��ͨ�˲�
		int LowPassFilter(cv::Mat srcImage, cv::Mat &dstImage);//��ͨ�˲�
	};

}
