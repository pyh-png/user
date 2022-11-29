#include"image.h"


/**
* @brief ͼ��Ԥ��������
* @param res_thΪ����ķ���ֵͼͼ��mask_handian1,2,3Ϊ�������ʹ����ĺ���ͼ��
* @param th_area��ֵ��С����ֵ������������
* @param  res_thΪ��������ǰ��ͼ��
*/
void polyimage(Mat &res_th, Mat mask_handian1, Mat mask_handian2, Mat mask_handian3, int th_area) {
	res_th = res_th - mask_handian1 - mask_handian2 - mask_handian3;
	//Mat se = cv::getStructuringElement(MORPH_ELLIPSE, cv::Size(5, 5));
	//erode(res_th, res_th, se, cv::Point(-1, -1), 2); //ִ�и�ʴ����
	Mat labels;      //CV_32Sͨ���ı�ǩ���󣬲�ͬ����ͨ�򱻸��費ͬ�ı�ǩֵ��int���ͣ�
	Mat stats;       //������ͨ��ͳ����Ϣ�ľ���
	Mat centroids;   //��ͨ��������������
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