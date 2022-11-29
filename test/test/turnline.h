#pragma once
//������Ϻ���
#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>

using namespace std;
using namespace cv;



//�������
bool polynomial_curve_fit(std::vector<cv::Point>& key_point, int n, cv::Mat& A)
{
	//Number of key points
	int N = key_point.size();

	//�������X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<double>(i, j) = X.at<double>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}

	//�������Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<double>(i, 0) = Y.at<double>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}

	A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//������A
	cv::solve(X, Y, A, cv::DECOMP_LU);
	return true;
}
//ʹ��ʾ��
	//cv::Mat image = cv::Mat::zeros(src.size(), CV_8UC3);
	//image.setTo(cv::Scalar(100, 0, 0));
	////for (int i = 0; i < points.size(); i++)
	////{
	////	cv::circle(image, points[i], 5, cv::Scalar(0, 0, 255), 2, 8, 0);
	////}

	////��������
	//cv::polylines(image, points, false, cv::Scalar(0, 255, 0), 1, 8, 0);

	//cv::Mat A;

	//polynomial_curve_fit(points, 3, A);
	//std::cout << "A = " << A << std::endl;

	//std::vector<cv::Point> points_fitted;

	//for (int x = 0; x < 400; x++)
	//{
	//	double y = A.at<double>(0, 0) + A.at<double>(1, 0) * x +
	//		A.at<double>(2, 0)*std::pow(x, 2) + A.at<double>(3, 0)*std::pow(x, 3);

	//	points_fitted.push_back(cv::Point(x, y));
	//}
	//cv::polylines(image, points_fitted, false, cv::Scalar(0, 255, 255), 1, 8, 0);

	//cv::imshow("image", image);

	//cv::waitKey(0);