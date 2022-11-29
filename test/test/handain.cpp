#include"handian.h"

/**
* @brief ���뺸�����ɸѡ
* @param dst1Ϊ���뺸��ͼ��ͼ�������������ĺ���ͼ��small��mid,max
* @param th_areaΪmid��max����ֵ��th_area_minΪsmall��mid����ֵ
* @return ��ȡ���ֲ�ͬ����ĺ���ͼ��
*/
void image_tep(cv::Mat &dst1, cv::Mat &small, cv::Mat &mid, cv::Mat &max, int th_area, int th_area_min ) {
	Mat dst;
	dst1.copyTo(dst);
	mid = Mat::zeros(dst.size(), CV_8UC1);
	small = Mat::zeros(dst.size(), CV_8UC1);
	Mat se1 = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(17, 17));
	dilate(dst, dst, se1, cv::Point(-1, -1)); //ִ�����Ͳ�����������
	Mat labels;      //CV_32Sͨ���ı�ǩ���󣬲�ͬ����ͨ�򱻸��費ͬ�ı�ǩֵ��int���ͣ�
	Mat stats;       //������ͨ��ͳ����Ϣ�ľ���
	Mat centroids;   //��ͨ��������������
	int num_labels = connectedComponentsWithStats(dst, labels, stats, centroids, 8, CV_32S);
	vector<int> nums(num_labels);
	for (int i = 1; i < num_labels; i++) {
		vector<Point> polygonPoint;
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		//�ָ�mid��max����
		if (area < th_area&&area>th_area_min) {
			polygonPoint.push_back(Point(x, y));
			polygonPoint.push_back(Point(x, y + height));
			polygonPoint.push_back(Point(x + width, y + height));
			polygonPoint.push_back(Point(x + width, y));
			fillConvexPoly(mid, polygonPoint, 255, 8);
			//contours.push_back(polygonPoint);
		}
		//�ָ�small����
		if (area < th_area_min) {
			polygonPoint.push_back(Point(x, y));
			polygonPoint.push_back(Point(x, y + height));
			polygonPoint.push_back(Point(x + width, y + height));
			polygonPoint.push_back(Point(x + width, y));
			fillConvexPoly(small, polygonPoint, 255, 8);
			//contours.push_back(polygonPoint);
		}

	}
	bitwise_and(dst1, small, small);
	bitwise_and(dst1, mid, mid);
	max = dst1 - small - mid;
}

/**
* @brief ��ȡ��������
* @param imageΪ����ͼ��8λ�Ҷ�ͼ��dstΪ���к���ͼ��rect_POIȥ��оƬ��Χ��Ӱ��
* @param ���������Χ������Ŀ��Ϊ��������
* @param hd_min�ٺ����Ϊ2-4����hd_midС������㣬hd_maxΪ��������㣬�����������ں����ֱ�����
* @return �������ṹ�壬����������������Ӿ���
*/
vector<handian> init_point(Mat image, Mat &dst, cv::Mat &hd_min, Mat &hd_mid, cv::Mat &hd_max, Rect &rect_POI) {

	vector<handian> res_han;
	Mat res;
	cv::threshold(image, res, 200, 255, cv::THRESH_BINARY);

	Mat labels;      //CV_32Sͨ���ı�ǩ���󣬲�ͬ����ͨ�򱻸��費ͬ�ı�ǩֵ��int���ͣ�
	Mat stats;       //������ͨ��ͳ����Ϣ�ľ���
	Mat centroids;   //��ͨ��������������
	int num_labels = connectedComponentsWithStats(res, labels, stats, centroids, 8, CV_32S);

	dst = Mat::zeros(res.size(), CV_8UC1);
	Mat dst_tem = Mat::zeros(res.size(), CV_8UC1);
	int w = res.cols;
	int h = res.rows;
	//for (size_t row = 0; row < h; row++) {
	//	for (size_t col = 0; col < w; col++) {
	//		int label = labels.at<int>(row, col);
	//		if (label == 0) continue;
	//		dst.at<uchar>(row, col) = 255;
	//	}
	//}
	int max_i = 0;
	int max_area = 0;
	for (int i = 1; i < num_labels; i++) {
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		if (area > 20000) {
			max_i = i;
			max_area = area;
			break;
		}
	}
	Vec2d max_point = centroids.at<Vec2d>(max_i, 0);
	int max_x = stats.at<int>(max_i, CC_STAT_LEFT);
	int max_y = stats.at<int>(max_i, CC_STAT_TOP);
	int max_width = stats.at<int>(max_i, CC_STAT_WIDTH);
	int max_height = stats.at<int>(max_i, CC_STAT_HEIGHT);
	rect_POI = Rect(max_x, max_y, max_width, max_height);
	for (int i = 1; i < num_labels; i++) {
		Vec2d pt = centroids.at<Vec2d>(i, 0);
		int x = stats.at<int>(i, CC_STAT_LEFT);
		int y = stats.at<int>(i, CC_STAT_TOP);
		int width = stats.at<int>(i, CC_STAT_WIDTH);
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int area = stats.at<int>(i, CC_STAT_AREA);
		handian temp_po;
		vector<Point> polygonPoint;
		if (pt[0] > max_x&&pt[1] > max_y&&pt[0] < max_x + max_width && pt[1] < max_y + max_height && area < 2000) {
			//circle(dst, Point(pt[0], pt[1]), 2, Scalar(0, 0, 255), -1, 8, 0);//���ĵ�����
			dst_tem.at<uchar>(Point(pt[0], pt[1])) == 255;
			polygonPoint.push_back(Point(x, y));
			polygonPoint.push_back(Point(x, y + height));
			polygonPoint.push_back(Point(x + width, y + height));
			polygonPoint.push_back(Point(x + width, y));
			fillConvexPoly(dst, polygonPoint, 255, 8);
			//rectangle(dst, Rect(x, y, width, height), 255, 1, 8, 0);//��Ӿ���
			temp_po.points = Point2f(pt[0], pt[1]);
			temp_po.rect = Rect(x, y, width, height);
			res_han.push_back(temp_po);
		}
	}
	image_tep(dst, hd_min, hd_mid, hd_max, 300000, 10000);
	return res_han;
}