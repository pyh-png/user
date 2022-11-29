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



using namespace std;
using namespace cv;
using namespace ImgEnhance;


// 创建线程池
threadpool executor{ 50 };

void fix(cv::Mat &dst, const int beginrow, const int begincol, const int a, const int b, int scale, std::string path1) {
	//simulate_hard_computation();
	std::string path = path1 + std::to_string(a) + "_" + std::to_string(b) + ".jpg";
	Mat ROI_1 = dst(Rect((b - begincol) * (1024 / scale), (a - beginrow) * (1024 / scale), (1024 / scale), (1024 / scale)));
	std::cout << path << std::endl;
	Mat image_tem = cv::imread(path);

	resize(image_tem, image_tem, Size(1024 / scale, 1024 / scale));
	

	image_tem.copyTo(ROI_1);
}
void stop() {
	std::this_thread::sleep_for(std::chrono::microseconds(5000));
	cout << "end..." << endl;
}
Mat example1(int maxrow, int maxcol, int scale, std::string path,int dst_type= CV_8UC1, int beginrow = 0, int begincol = 0)
{
	// 初始化线程池
	//pool.init();
	cv::Mat dst = cv::Mat::zeros(1024 * (maxrow - beginrow + 1) / scale, 1024 * (maxcol - begincol + 1) / scale, dst_type);
	//std::vector< std::future<int> > results;
	// 提交乘法操作，总共30个
	for (int i = beginrow; i <= maxrow; ++i)
		for (int j = begincol; j <= maxcol; ++j)
		{
			//results.emplace_back(executor.commit(fix, std::ref(dst), i, j, scale, path));

			if (i == maxrow && j == maxcol) {
				executor.commit(fix, std::ref(dst), beginrow, begincol, i, j, scale, path).get();
			}
			else
			{
				executor.commit(fix, std::ref(dst), beginrow, begincol, i, j, scale, path);
			}
			//future.get();
		}
	//auto future=executor.commit(fix, std::ref(dst), maxrow, maxcol, maxrow, maxcol, scale, path);

	//future.get();
	//auto future1 = executor.commit(stop);
	//future1.get();
   //for (auto && result : results)
   //	std::cout << result.get() << ' ';
//   std::cout << std::endl;
   // 关闭线程池
	return dst;
}
vector<string> Stringsplit(string str, const const char split)
{
	istringstream iss(str);	// 输入流
	string token;// 接收缓冲区
	vector<string> res;
	while (getline(iss, token, split))	// 以split为分隔符
	{
		res.push_back(token);
		//cout << token << endl; // 输出
	}
	return res;
}
Mat get_image(std::string folder_path, std::string path,int TYPE=CV_8UC1) {
	std::vector<cv::String> file_names;
	cv::glob(folder_path, file_names);   //get file names
	pair<int, int> res1;
	pair<pair<int, int>, string> image;
	vector<pair<pair<int, int>, string>> image_res;
	int maxcol = 0;
	int maxrow = 0;
	//vector<string> res1(2);
	for (int i = 0; i < file_names.size(); i++) {
		//std::cout << file_names[i] << std::endl;
		vector<string> res = Stringsplit(file_names[i], '\\');

		res1.first = atoi(Stringsplit(res[5], '_')[0].c_str());
		res1.second = atoi(Stringsplit(Stringsplit(res[5], '_')[1], '.')[0].c_str());
		if (res1.first > maxrow) {
			maxrow = res1.first;
		}
		if (res1.second > maxcol) {
			maxcol = res1.second;
		}
		//img = cv::imread(file_names[i]);
		image.first = res1;
		image.second = file_names[i];
		image_res.push_back(image);
	}
	//cv::Mat dst1=cv::Mat::zeros(1024 * maxrow, 1024 * maxcol, CV_8UC1);
	double same = 4030;
	int scale = maxrow * maxcol > same ? 2 : 1;
	//Mat res = example1(5, 5, scale, path);
	//Mat res = example1(13, 64, scale, path, 8, 60);
	//Mat res = example1(63,15,scale, path,60, 13);
	//Mat res = example1(35, 35, scale, path);
	Mat res = example1(maxrow, maxcol, scale, path, TYPE);
	return res;
}
int main() {

	std::string folder_path = "F:\\dariy\\handian\\22070110_LN7_jpg\\m3\\*.*"; //path of folder, you can replace "*.*" by "*.jpg" or "*.png"
	std::string path = "F:\\dariy\\handian\\22070110_LN7_jpg\\m3\\";
	//22041504_S51_jpg,22070110_LN7_jpg
	Mat res = get_image(folder_path, path, CV_8UC3);//合并并转化为灰度图
	int h_max = 45;
	int h_min = 25;
	int s_max = 75;
	int s_min = 40;
	int v_max = 200;
	int v_min = 150;
	Mat res_mask;
	cvtColor(res, res, COLOR_BGR2HSV);
	inRange(res, Scalar(h_min, s_min, v_min),
		Scalar(h_max, s_max, v_max), res_mask);
	//imwrite("22070110_LN7_m2.jpg", res);
	return 0;
}