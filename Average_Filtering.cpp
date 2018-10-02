#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat avg_filter(Mat src) {

	Mat des;
	des.create(src.size(), src.type());
	int maskSize;
	cout << "Enter mask size : ";
	cin >> maskSize;
	int s;
	s = maskSize / 2;
	Mat mask;
	mask.create(maskSize, maskSize, CV_32F);
	float sum = 0.0;
	float value;

	for (int y = -s, y1 = 0; y <= s; y++, y1++)
	{
		for (int x = -s, x1 = 0; x <= s; x++, x1++)
		{
			cout << "Input for mask index " << y << ", " << x << ": ";
			cin >> value;
			mask.at<float>(y1, x1) = value;
			sum = sum + value;
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
					b += (float)(src.at<uchar>(y + y1, x + x1)*mask.at<float>(y1, x1))*(1 / sum);
				}
			}

			des.at<uchar>(y + s, x + s) = (uchar)b;

		}
	}
		return des;

}



int main() {

	Mat src = imread("lena.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input",src);
	waitKey();
	Mat output = avg_filter(src);
	imshow("Output", output);
	waitKey();
	//des.create(src.size(),src.type());

}