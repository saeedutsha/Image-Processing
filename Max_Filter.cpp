#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat max_filter(Mat src) {

	int maskSize;
	cout << "Enter Mask Size : ";
	cin >> maskSize;
	int s;
	s = maskSize / 2;
	Mat des;
	Mat out;
	copyMakeBorder(src, des, s, s, s, s, 0, 0);
	out.create(des.size(),des.type());
	int max = 0;
	int val;

	for (int y = 0; y < des.rows - maskSize + 1; y++)
	{
		for (int x = 0; x < des.cols - maskSize + 1; x++)
		{
			max=0;
			for (int y1 = 0; y1 < maskSize; y1++)
			{
				for (int x1 = 0; x1 < maskSize; x1++)
				{
					
					val = des.at<uchar>(y+y1, x+x1);
					if (val > max)max = val;

				}
			}
			out.at<uchar>(y + s, x + s) = max;
		}
	}
	return out;

}



int main() {

	Mat src = imread("m.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();
	Mat output = max_filter(src);
	imshow("Output", output);
	waitKey();

}