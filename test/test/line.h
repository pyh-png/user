//骨架提取函数



#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>



using namespace std;
using namespace cv;

/**
* @brief 对输入图像进行细化,骨骼化
* @param src为输入图像,用cvThreshold函数处理过的8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
* @param maxIterations限制迭代次数，如果不进行限制，默认为-1，代表不限制迭代次数，直到获得最终结果
* @return 为对src细化后的输出图像,格式与src格式相同，元素中只有0与1,1代表有元素，0代表为空白
*/
cv::Mat thinImage(const cv::Mat & src, const int maxIterations = -1);

/**
* @brief 对骨骼化图数据进行过滤，实现两个点之间至少隔一个空白像素
* @param thinSrc为输入的骨骼化图像,8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
*/
void filterOver(cv::Mat thinSrc);


//计算直线斜率
double gradient(Point2f pt1, Point2f pt2);


//计算两直线所成角度
double getAngle(Point &ArcCenter, Point &StartPoint, Point &EndPoint);


//是否为拐点
bool isturn(vector<Point> points, Point soure);


/**
* @brief 骨骼端点图中去除太近的多余点
* @param ponints为全部点
* @param raudis卷积半径，以当前像素点位圆心，在圆范围内判断点是否重复
* @param image绘制了所有点位置，进行判断
* @return 优化后的骨骼点
*/
std::vector<cv::Point> point_near(std::vector<cv::Point> ponints, Mat image, int raudis);

/**
* @brief 从过滤后的骨骼化图像中寻找端点和交叉点
* @param thinSrc为输入的过滤后骨骼化图像,8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
* @param raudis卷积半径，以当前像素点位圆心，在圆范围内判断点是否为端点或交叉点
* @param thresholdMax交叉点阈值，大于这个值为交叉点
* @param thresholdMin端点阈值，小于这个值为端点
* @return 为对src细化后的输出图像,格式与src格式相同，元素中只有0与1,1代表有元素，0代表为空白
*/
std::vector<cv::Point> getPoints(const cv::Mat &thinSrc, unsigned int raudis = 4, unsigned int thresholdMax = 10, unsigned int thresholdMin = 5);