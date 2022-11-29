#include"filter.h"

int ImgEnhance::Filter::MeanFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	blur(srcImage, dstImage, Size(areaSize, areaSize), Point(-1, -1));
	return 0;
}

int ImgEnhance::Filter::GaussFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize, int xValue, int yValue)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	GaussianBlur(srcImage, dstImage, Size(areaSize, areaSize), xValue, yValue);
	return 0;
}

int ImgEnhance::Filter::MedianFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaSize)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	medianBlur(srcImage, dstImage, areaSize);
	return 0;
}

int ImgEnhance::Filter::BilateralFilter(cv::Mat srcImage, cv::Mat &dstImage, int areaRadio, int limitValue, int unuseValue)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	bilateralFilter(srcImage, dstImage, areaRadio, limitValue, unuseValue);
	return 0;
}

int ImgEnhance::Filter::HighPassFilter(cv::Mat srcImage, cv::Mat &dstImage)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	Mat highKernel;
	highKernel = (Mat_<double>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);//¸ßÍ¨ÂË²¨ºË

	Mat grad;

	filter2D(srcImage, grad, CV_16S, highKernel, Point(-1, -1));
	convertScaleAbs(grad, dstImage);

	return 0;
}

int ImgEnhance::Filter::LowPassFilter(cv::Mat srcImage, cv::Mat &dstImage)
{
	if (srcImage.empty())
	{
		printf("cannot load!!\n");
		return 1;
	}
	Mat lowKernel;
	lowKernel = (Mat_<double>(3, 3) << 1.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 4.0 / 16, 2.0 / 16, 1.0 / 16, 2.0 / 16, 1.0 / 16);//µÍÍ¨ÂË²¨ºË

	Mat grad;

	filter2D(srcImage, grad, CV_16S, lowKernel, Point(-1, -1));
	convertScaleAbs(grad, dstImage);

	return 0;
}
