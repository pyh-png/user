#include"line.h"

cv::Mat thinImage(const cv::Mat & src, const int maxIterations )
{
	assert(src.type() == CV_8UC1);
	cv::Mat dst;
	int width = src.cols;
	int height = src.rows;
	src.copyTo(dst);
	int count = 0;  //��¼��������    
	while (true)
	{
		count++;
		if (maxIterations != -1 && count > maxIterations) //���ƴ������ҵ�����������    
			break;
		std::vector<uchar *> mFlag; //���ڱ����Ҫɾ���ĵ�    
		//�Ե���    
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//��������ĸ����������б��    
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
						//���    
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//����ǵĵ�ɾ��    
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		//ֱ��û�е����㣬�㷨����    
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//��mFlag���    
		}

		//�Ե���    
		for (int i = 0; i < height; ++i)
		{
			uchar * p = dst.ptr<uchar>(i);
			for (int j = 0; j < width; ++j)
			{
				//��������ĸ����������б��    
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
						//���    
						mFlag.push_back(p + j);
					}
				}
			}
		}

		//����ǵĵ�ɾ��    
		for (std::vector<uchar *>::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
		{
			**i = 0;
		}

		//ֱ��û�е����㣬�㷨����    
		if (mFlag.empty())
		{
			break;
		}
		else
		{
			mFlag.clear();//��mFlag���    
		}
	}
	return dst;
}

/**
* @brief �Թ�����ͼ���ݽ��й��ˣ�ʵ��������֮�����ٸ�һ���հ�����
* @param thinSrcΪ����Ĺ�����ͼ��,8λ�Ҷ�ͼ���ʽ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
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
			// ʵ��������֮�����ٸ�һ������  
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
//����ֱ��б��
double gradient(Point2f pt1, Point2f pt2)
{
	if (pt1.x == pt2.x)
	{
		return 9999999.9;	//б�ʲ�����
	}
	else
	{
		return (pt2.y - pt1.y) / (pt2.x - pt1.x);
	}
}
//������ֱ�����ɽǶ�
double getAngle(Point &ArcCenter, Point &StartPoint, Point &EndPoint)
{

	//��ֱ��б��
	double k1 = gradient(StartPoint, ArcCenter);
	double k2 = gradient(EndPoint, ArcCenter);

	//����
	double theta = atan(abs((k2 - k1) / (1 + k1 * k2)));

	//�Ƕ�
	double Angle = theta * 180 / CV_PI;

	return Angle;
}
//�Ƿ�Ϊ�յ�
bool isturn(vector<Point> points, Point soure) {
	sort(points.begin(), points.end(), [](Point a, Point b) {return a.x > b.x; });//��x��С�Ľ�������
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
* @brief �����˵�ͼ��ȥ��̫���Ķ����
* @param ponintsΪȫ����
* @param raudis����뾶���Ե�ǰ���ص�λԲ�ģ���Բ��Χ���жϵ��Ƿ��ظ�
* @param image���������е�λ�ã������ж�
* @return �Ż���Ĺ�����
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
* @brief �ӹ��˺�Ĺ�����ͼ����Ѱ�Ҷ˵�ͽ����
* @param thinSrcΪ����Ĺ��˺������ͼ��,8λ�Ҷ�ͼ���ʽ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
* @param raudis����뾶���Ե�ǰ���ص�λԲ�ģ���Բ��Χ���жϵ��Ƿ�Ϊ�˵�򽻲��
* @param thresholdMax�������ֵ���������ֵΪ�����
* @param thresholdMin�˵���ֵ��С�����ֵΪ�˵�
* @return Ϊ��srcϸ��������ͼ��,��ʽ��src��ʽ��ͬ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
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