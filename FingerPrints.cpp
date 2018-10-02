#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat erosion(Mat des, int maskSize,int s) {

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

Mat dilation(Mat des, int maskSize, int s) {

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

					if (des.at<uchar>(y + y1, x + x1) == 255) {
						flag = 1;
					}

				}
			}
			if (flag == 0)
				out.at<uchar>(y + s, x + s) = 0;
			else
				out.at<uchar>(y + s, x + s) = 255;

		}
	}

	return out;

}


int main() {

	Mat src = imread("sam3.tif", CV_LOAD_IMAGE_GRAYSCALE);
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

	imshow("(a) Noisy Image", src);
	waitKey();
	Mat output1 = erosion(des, maskSize,s);
	imshow("(b) Eroded Image", output1);
	waitKey();
	Mat output2 = dilation(output1, maskSize, s);
	imshow("(c) Opening of A", output2);
	waitKey();
	Mat output3 = dilation(output2, maskSize, s);
	imshow("(d) Dilation of the opening", output3);
	waitKey();
	Mat output4 = erosion(output3, maskSize, s);
	imshow("(e) Closing of the opening", output4);
	waitKey();

}