#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>


using namespace std;
using namespace cv;

Mat max_filter(Mat src) {

	int maskSize;
	cout << "Enter Mask Size : ";
	cin >> maskSize;
	int s,n,val;
	float x;
	s = maskSize / 2;
	int size = maskSize*maskSize;
	n = size / 2;
	int array[999];


	int i = 0;
	Mat des;
	Mat out;
	copyMakeBorder(src, des, s, s, s, s, 0, 0);
	out.create(des.size(), des.type());
	

	for (int y = 0; y < des.rows - maskSize + 1; y++)
	{
		for (int x = 0; x < des.cols - maskSize + 1; x++)
		{
			i = 0;
			for (int y1 = 0; y1 < maskSize; y1++)
			{
				for (int x1 = 0; x1 < maskSize; x1++)
				{

					val = des.at<uchar>(y+y1,x+x1);
					array[i++] = val;

				}
			}
			sort(array, array + size);
			if (size % 2 != 0) {
				out.at<uchar>(y+s,x+s) = array[n];
			}
			else {
				x = (array[n] + array[n + 1]) / 2;
				out.at<uchar>(y + s, x + s) = x;
			}

		}
	}
	return out;

}



int main() {

	Mat src = imread("salt.png", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();
	Mat output = max_filter(src);
	imshow("Output", output);
	waitKey();
	
	
}