#include"line.h"

cv::Mat thinImage(const cv::Mat & src, const int maxIterations )
{
	assert(src.type() == CV_8UC1);
	cv::Mat dst;
	int width = src.cols;
	int height = src.rows;
	src.copyTo(dst);
	int count = 0;  //记录迭代次数    
	while (true)
	{
		count++;
		if (maxIterations != -1 && count > maxIterations) //限制次数并且迭代次数到达    
			break;
		std::vector<uchar *> mFlag; //用于标记需要删除的点    
		//对点标记    
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//如果满足四个条件，进行标记    
				//  p9 p2 p3    
				//  p8 p1 p4    
				//  p7 p6 p5    
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);
				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p6 == 0 && p4 * p6 * p8 == 0)
					{
						//标记    
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//将标记的点删除    
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		//直到没有点满足，算法结束    
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//将mFlag清空    
		}

		//对点标记    
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//如果满足四个条件，进行标记    
				//  p9 p2 p3    
				//  p8 p1 p4    
				//  p7 p6 p5    
				uchar p1 = p[j];
				if (p1 != 1) continue;
				uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
				uchar p8 = (j == 0) ? 0 : *(p + j - 1);
				uchar p2 = (i == 0) ? 0 : *(p - dst.step + j);
				uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - dst.step + j + 1);
				uchar p9 = (i == 0 || j == 0) ? 0 : *(p - dst.step + j - 1);
				uchar p6 = (i == height - 1) ? 0 : *(p + dst.step + j);
				uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + dst.step + j + 1);
				uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + dst.step + j - 1);

				if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
				{
					int ap = 0;
					if (p2 == 0 && p3 == 1) ++ap;
					if (p3 == 0 && p4 == 1) ++ap;
					if (p4 == 0 && p5 == 1) ++ap;
					if (p5 == 0 && p6 == 1) ++ap;
					if (p6 == 0 && p7 == 1) ++ap;
					if (p7 == 0 && p8 == 1) ++ap;
					if (p8 == 0 && p9 == 1) ++ap;
					if (p9 == 0 && p2 == 1) ++ap;

					if (ap == 1 && p2 * p4 * p8 == 0 && p2 * p6 * p8 == 0)
					{
						//标记    
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//将标记的点删除    
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		//直到没有点满足，算法结束    
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//将mFlag清空    
		}
	}
	return dst;
}

/**
* @brief 对骨骼化图数据进行过滤，实现两个点之间至少隔一个空白像素
* @param thinSrc为输入的骨骼化图像,8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
*/
void filterOver(cv::Mat thinSrc)
{
	assert(thinSrc.type() == CV_8UC1);
	int width = thinSrc.cols;
	int height = thinSrc.rows;
	for (int i = 0; i < height; ++i)
	{
		uchar * p = thinSrc.ptr<uchar>(i);
		for (int j = 0; j < width; ++j)
		{
			// 实现两个点之间至少隔一个像素  
			//  p9 p2 p3    
			//  p8 p1 p4    
			//  p7 p6 p5    
			uchar p1 = p[j];
			if (p1 != 1) continue;
			uchar p4 = (j == width - 1) ? 0 : *(p + j + 1);
			uchar p8 = (j == 0) ? 0 : *(p + j - 1);
			uchar p2 = (i == 0) ? 0 : *(p - thinSrc.step + j);
			uchar p3 = (i == 0 || j == width - 1) ? 0 : *(p - thinSrc.step + j + 1);
			uchar p9 = (i == 0 || j == 0) ? 0 : *(p - thinSrc.step + j - 1);
			uchar p6 = (i == height - 1) ? 0 : *(p + thinSrc.step + j);
			uchar p5 = (i == height - 1 || j == width - 1) ? 0 : *(p + thinSrc.step + j + 1);
			uchar p7 = (i == height - 1 || j == 0) ? 0 : *(p + thinSrc.step + j - 1);
			if (p2 + p3 + p8 + p9 >= 1)
			{
				p[j] = 0;
			}
		}
	}
}
//计算直线斜率
double gradient(Point2f pt1, Point2f pt2)
{
	if (pt1.x == pt2.x)
	{
		return 9999999.9;	//斜率不存在
	}
	else
	{
		return (pt2.y - pt1.y) / (pt2.x - pt1.x);
	}
}
//计算两直线所成角度
double getAngle(Point &ArcCenter, Point &StartPoint, Point &EndPoint)
{

	//两直线斜率
	double k1 = gradient(StartPoint, ArcCenter);
	double k2 = gradient(EndPoint, ArcCenter);

	//弧度
	double theta = atan(abs((k2 - k1) / (1 + k1 * k2)));

	//角度
	double Angle = theta * 180 / CV_PI;

	return Angle;
}
//是否为拐点
bool isturn(vector<Point> points, Point soure) {
	sort(points.begin(), points.end(), [](Point a, Point b) {return a.x > b.x; });//按x大小的降序排列
	Point neight1, neight2;
	neight1 = points[0];
	neight2 = points[points.size() - 1];
	double an = getAngle(soure, neight1, neight2);
	//cout << an << endl;
	if (an > 0) {
		//cout << abs(an - 180) << endl;
		return true;
	}
	else
		return false;
}

/**
* @brief 骨骼端点图中去除太近的多余点
* @param ponints为全部点
* @param raudis卷积半径，以当前像素点位圆心，在圆范围内判断点是否重复
* @param image绘制了所有点位置，进行判断
* @return 优化后的骨骼点
*/
std::vector<cv::Point> point_near(std::vector<cv::Point> ponints, Mat image, int raudis) {
	std::vector<cv::Point> points;
	int width = image.cols;
	int height = image.rows;
	for (auto point1 : ponints) {
		int i = point1.x;
		int j = point1.y;
		int near = 0;
		for (int k = i - raudis; k < i + raudis + 1; k++)
		{
			for (int l = j - raudis; l < j + raudis + 1; l++)
			{

				if (k < 0 || l < 0 || k>width - 1 || l>height - 1)
				{
					continue;

				}
				else  if (image.at<uchar>(Point(k, l)) == 255)
				{
					near = 1;
				}
			}
		}
		if (near == 0) {
			points.push_back(point1);
			image.at<uchar>(point1) = 255;
		}
	}
	return points;
}

/**
* @brief 从过滤后的骨骼化图像中寻找端点和交叉点
* @param thinSrc为输入的过滤后骨骼化图像,8位灰度图像格式，元素中只有0与1,1代表有元素，0代表为空白
* @param raudis卷积半径，以当前像素点位圆心，在圆范围内判断点是否为端点或交叉点
* @param thresholdMax交叉点阈值，大于这个值为交叉点
* @param thresholdMin端点阈值，小于这个值为端点
* @return 为对src细化后的输出图像,格式与src格式相同，元素中只有0与1,1代表有元素，0代表为空白
*/
std::vector<cv::Point> getPoints(const cv::Mat &thinSrc, unsigned int raudis , unsigned int thresholdMax , unsigned int thresholdMin )
{
	assert(thinSrc.type() == CV_8UC1);
	int width = thinSrc.cols;
	int height = thinSrc.rows;
	cv::Mat tmp;
	thinSrc.copyTo(tmp);
	std::vector<cv::Point> points;
	cv::Mat image = cv::Mat::zeros(thinSrc.size(), CV_8UC1);
	int near = 0;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (*(tmp.data + tmp.step * i + j) == 0)
			{
				continue;
			}
			int count = 0;
			std::vector<cv::Point> points_temp;
			for (int k = i - raudis; k < i + raudis + 1; k++)
			{
				for (int l = j - raudis; l < j + raudis + 1; l++)
				{
					if (k < 0 || l < 0 || k>height - 1 || l>width - 1)
					{
						continue;

					}
					else if (*(tmp.data + tmp.step * k + l) == 1)
					{
						points_temp.push_back(Point(l, k));
						count++;
					}
				}
			}
			if (isturn(points_temp, Point(j, i))) {
				points.push_back(Point(j, i));
			}
			if (count > thresholdMax || count < thresholdMin)
			{

				//cout << count << endl;
				Point point(j, i);
				points.push_back(point);
			}

		}
	}
	std::vector<cv::Point> points1 = point_near(points, image, 10);
	return points1;
}