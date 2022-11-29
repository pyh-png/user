//�Ǽ���ȡ����



#include<opencv2\opencv.hpp>
#include<vector>
#include<iostream>



using namespace std;
using namespace cv;

/**
* @brief ������ͼ�����ϸ��,������
* @param srcΪ����ͼ��,��cvThreshold�����������8λ�Ҷ�ͼ���ʽ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
* @param maxIterations���Ƶ���������������������ƣ�Ĭ��Ϊ-1���������Ƶ���������ֱ��������ս��
* @return Ϊ��srcϸ��������ͼ��,��ʽ��src��ʽ��ͬ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
*/
cv::Mat thinImage(const cv::Mat & src, const int maxIterations = -1);

/**
* @brief �Թ�����ͼ���ݽ��й��ˣ�ʵ��������֮�����ٸ�һ���հ�����
* @param thinSrcΪ����Ĺ�����ͼ��,8λ�Ҷ�ͼ���ʽ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
*/
void filterOver(cv::Mat thinSrc);


//����ֱ��б��
double gradient(Point2f pt1, Point2f pt2);


//������ֱ�����ɽǶ�
double getAngle(Point &ArcCenter, Point &StartPoint, Point &EndPoint);


//�Ƿ�Ϊ�յ�
bool isturn(vector<Point> points, Point soure);


/**
* @brief �����˵�ͼ��ȥ��̫���Ķ����
* @param ponintsΪȫ����
* @param raudis����뾶���Ե�ǰ���ص�λԲ�ģ���Բ��Χ���жϵ��Ƿ��ظ�
* @param image���������е�λ�ã������ж�
* @return �Ż���Ĺ�����
*/
std::vector<cv::Point> point_near(std::vector<cv::Point> ponints, Mat image, int raudis);

/**
* @brief �ӹ��˺�Ĺ�����ͼ����Ѱ�Ҷ˵�ͽ����
* @param thinSrcΪ����Ĺ��˺������ͼ��,8λ�Ҷ�ͼ���ʽ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
* @param raudis����뾶���Ե�ǰ���ص�λԲ�ģ���Բ��Χ���жϵ��Ƿ�Ϊ�˵�򽻲��
* @param thresholdMax�������ֵ���������ֵΪ�����
* @param thresholdMin�˵���ֵ��С�����ֵΪ�˵�
* @return Ϊ��srcϸ��������ͼ��,��ʽ��src��ʽ��ͬ��Ԫ����ֻ��0��1,1������Ԫ�أ�0����Ϊ�հ�
*/
std::vector<cv::Point> getPoints(const cv::Mat &thinSrc, unsigned int raudis = 4, unsigned int thresholdMax = 10, unsigned int thresholdMin = 5);