#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat hb_filter(Mat src) {

	Mat des,maskImg,boostImg;
	des.create(src.size(), src.type());
	maskImg.create(src.size(), src.type());
	boostImg.create(src.size(), src.type());
	float sigma;
	int k;
	cout << "Enter sigma : ";
	cin >> sigma;
	cout << "Enter value of k : ";
	cin >> k;

	int maskSize;
	maskSize = (int)sigma*5.0;
	if (maskSize % 2 == 0)maskSize++;
	int s;
	s = maskSize / 2;
	float value;
	float sigmaSq = sigma * sigma;
	float n = (1 / (2 * 3.1415*sigmaSq));

	Mat mask;
	mask.create(maskSize, maskSize, CV_32F);

	for (int y = -s, y1 = 0; y <= s; y++, y1++)
	{
		for (int x = -s, x1 = 0; x <= s; x++, x1++)
		{
			value = n*exp((-((x*x) + (y*y))) / (2 * sigmaSq));
			mask.at<float>(y1, x1) = value;
		}

	}

	float b = 0.0;

	for (int y = 0; y < src.rows - maskSize + 1; y++)
	{
		for (int x = 0; x < src.cols - maskSize + 1; x++)
		{
			b = 0.0;

			for (int y1 = 0; y1 < maskSize; y1++)
			{
				for (int x1 = 0; x1 < maskSize; x1++)
				{
					b += (float)(src.at<uchar>(y + y1, x + x1)*mask.at<float>(y1, x1));
				}
			}

			des.at<uchar>(y + s, x + s) = (uchar)b;

		}
	}


	float val,val2;
	float max = 0.0;
	
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			
			val = abs(src.at<uchar>(y, x) - des.at<uchar>(y, x));
			if (val > max)max = val;
			maskImg.at<uchar>(y, x) = val;

		}
	}


	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {

			val2 = src.at<uchar>(y, x) + (k*(maskImg.at<uchar>(y, x)));
			val2 *= 255;
			val2 /= (255+(max));

			boostImg.at<uchar>(y, x) = val2;

		}
	}


	imshow("Gaussian Blur", des);
	waitKey();
	imshow("Masked Image", maskImg);
	waitKey();
	return boostImg;

}



int main() {

	Mat src = imread("dip.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();
	Mat output = hb_filter(src);
	imshow("Output", output);
	waitKey();

}