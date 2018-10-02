#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat erosion(Mat des, int maskSize) {

	int s;
	s = maskSize / 2;
	Mat mask;
	mask.create(maskSize, maskSize, CV_32S);
	Mat out;
	out.create(des.size(), des.type());

	int flag = 0;

	for (int y = 0; y < des.rows - maskSize + 1; y++)
	{
		for (int x = 0; x < des.cols - maskSize + 1; x++)
		{
			flag = 0;

			for (int y1 = 0; y1 < maskSize; y1++)
			{
				for (int x1 = 0; x1 < maskSize; x1++)
				{

					if (des.at<uchar>(y + y1, x + x1) != 255) {
						flag = 1;
					}

				}
			}
			if (flag == 1)
				out.at<uchar>(y + s, x + s) = 0;
			else
				out.at<uchar>(y + s, x + s) = des.at<uchar>(y + s, x + s);

		}
	}

	return out;

}


int main() {

	Mat src = imread("sam1.tif", CV_LOAD_IMAGE_GRAYSCALE);
	int maskSize;
	cout << "Enter mask size : ";
	cin >> maskSize;
	Mat des;
	int s;
	s = maskSize / 2;
	copyMakeBorder(src, des, s, s, s, s, 0, 0);
	for (int y = 0; y < des.rows; y++)
	{
		for (int x = 0; x < des.cols; x++)
		{
			if (des.at<uchar>(y, x) >= 0 && des.at<uchar>(y, x) <= 127)des.at<uchar>(y, x) = 0;
			else if (des.at<uchar>(y, x) >127 && des.at<uchar>(y, x) <= 255) des.at<uchar>(y, x) = 255;

		}
	}

	imshow("Input", src);
	waitKey();
	Mat output = erosion(des, maskSize);
	imshow("After Erosion", output);
	waitKey();

}