#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat gaus_filter(Mat src) {

	Mat des;
	des.create(src.size(), src.type());
	float sigma;
	cout << "Enter sigma : ";
	cin >> sigma;

	int maskSize;
	maskSize = (int) sigma*5.0;
	if (maskSize % 2 == 0)maskSize++;
	int s;
	s = maskSize / 2;
	float value;
	float sigmaSq = sigma * sigma;
	float n = (1 / (2*3.1415*sigmaSq));

	Mat mask;
	mask.create(maskSize, maskSize, CV_32F);

	for (int y = -s, y1 = 0; y <= s; y++, y1++)
	{
		for (int x = -s, x1 = 0; x <= s; x++, x1++)
		{
			value = n*exp((-((x*x)+(y*y)))/(2*sigmaSq));
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
	return des;

}



int main() {

	Mat src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();
	Mat output = gaus_filter(src);
	imshow("Output", output);
	waitKey();
	//des.create(src.size(),src.type());

}