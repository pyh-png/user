#include "get_image.h"

threadpool executor{ 50 };

void fix(cv::Mat &dst, const int beginrow, const int begincol, const int a, const int b, int scale, std::string pathf) {

	std::string path = pathf + std::to_string(a) + "_" + std::to_string(b) + ".jpg";//单个图片的路径
	Mat ROI_1 = dst(Rect((b - begincol) * (1024 / scale), (a - beginrow) * (1024 / scale), (1024 / scale), (1024 / scale)));
	std::cout << path << std::endl;
	Mat image_tem = cv::imread(path, 0); //灰度图

	resize(image_tem, image_tem, Size(1024 / scale, 1024 / scale));//缩放scale倍
	image_tem.copyTo(ROI_1);
}

Mat splic(int maxrow, int maxcol, int scale, std::string path, int beginrow, int begincol )
{
	// 初始化线程池

	cv::Mat dst = cv::Mat::zeros(1024 * (maxrow - beginrow + 1) / scale, 1024 * (maxcol - begincol + 1) / scale, CV_8UC1);
	// 提交操作，总共maxrow*maxcol个
	for (int i = beginrow; i <= maxrow; ++i)
		for (int j = begincol; j <= maxcol; ++j)
		{

			if (i == maxrow && j == maxcol) {
				executor.commit(fix, std::ref(dst), beginrow, begincol, i, j, scale, path).get();
			}
			else
			{
				executor.commit(fix, std::ref(dst), beginrow, begincol, i, j, scale, path);
			}
		}
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
Mat get_image(std::string folder_path, std::string path,int scale) {
	std::vector<cv::String> file_names;
	cv::glob(folder_path, file_names);   //获取文件夹下全部文件
	int maxcol = 0;
	int maxrow = 0;
	//获取总数的图片
	for (int i = 0; i < file_names.size(); i++) {
		//std::cout << file_names[i] << std::endl;

		vector<string> res = Stringsplit(file_names[i], '\\');

		maxcol = max(atoi(Stringsplit(res[res.size()-1], '_')[1].c_str()), maxcol);
		maxrow = max(atoi(Stringsplit(res[res.size() - 1], '_')[0].c_str()), maxrow);

	}
	Mat res = splic(maxrow, maxcol, scale, path);//图像拼接
	return res;
}