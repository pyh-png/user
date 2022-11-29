#include"image.h"


/**
* @brief 图像预处理并反向
* @param res_th为输入的反二值图图像，mask_handian1,2,3为三种膨胀处理后的焊点图像
* @param th_area阈值，小于阈值的区域进行填充
* @param  res_th为最后输出的前景图像
*/
void polyimage(Mat &res_th, Mat mask_handian1, Mat mask_handian2, Mat mask_handian3, int th_area) {
	res_th = res_th - mask_handian1 - mask_handian2 - mask_handian3;
	//Mat se = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5));
	//erode(res_th, res_th, se, cv::Point(-1, -1), 2); //执行腐蚀操作
	Mat labels;      //CV_32S通道的标签矩阵，不同的连通域被赋予不同的标签值（int类型）
	Mat stats;       //包含连通域统计信息的矩阵
	Mat centroids;   //连通域的质心坐标矩阵
	int num_labels = connectedComponentsWithStats(res_th, labels, stats, centroids, 8, CV_32S);

	for (int i = 1; i < num_labels; i++) {
		vector<Point> polygonPoint;
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		if (area < th_area) {
			polygonPoint.push_back(Point(x, y));
			polygonPoint.push_back(Point(x, y + height));
			polygonPoint.push_back(Point(x + width, y + height));
			polygonPoint.push_back(Point(x + width, y));
			fillConvexPoly(res_th, polygonPoint, 0, 8);
		}
	}
	res_th = 255 - res_th;
}