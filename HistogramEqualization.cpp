#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

Mat histogram(Mat src) {

	Mat des;
	des.create(300,255,CV_8UC1);

	for (int y = 0; y < des.rows; y++)
	{
		for (int x = 0; x < des.cols; x++)
		{
			des.at<uchar>(y, x) = 0;
		}
	}

	int array[256];
	for (int i = 0; i < 255; i++) {
		array[i] = 0;
	}

	int max = 0;
	
	for (int y = 0; y < src.rows; y++)
	{
		for (int x = 0; x < src.cols; x++)
		{
			int val = src.at<uchar>(y, x);
			array[val]++;
		}
	}

	for (int i = 0; i < 255; i++) {
		if (array[i] > max)max = array[i];
	}

	for (int i = 0; i < 255; i++) {
		array[i] = array[i] * 300;
		array[i] = array[i] / max;
	}

	for (int i = 0; i < 255; i++) {
		for (int j = 300-array[i]; j < 300; j++) {
			des.at<uchar>(j,i) = 255;
		}
	}

	//float a = (float)(7300 * 300) / 17718;
	//cout << ceil(a);

	return des;

}

Mat equalize(Mat src) {
	Mat des = src.clone();

	float array[256];
	for (int i = 0; i < 255; i++) {
		array[i] = 0;
	}


	for (int y = 0; y < des.rows; y++)
	{
		for (int x = 0; x < des.cols; x++)
		{
			int val = des.at<uchar>(y, x);
			array[val]++;
		}
	}
	
	int x = des.rows * des.cols;
	
	for (int i = 0; i < 255; i++) {
		array[i] = (float)array[i]/x;
	}
	
	float array2[256];
	float sum = 0.0;

	for (int i = 0; i < 255; i++) {
		sum = 0.0;
		for (int j = 0; j <= i; j++) {
			sum = sum + array[j];
		}
		array2[i] = sum;
	}

	for (int y = 0; y < des.rows; y++)
	{
		for (int x = 0; x < des.cols; x++)
		{
			int val = des.at<uchar>(y, x);
			float val2 = (float)255 * array2[val];
			val2 = ceil(val2);
			des.at<uchar>(y, x) = val2;
		}
	}

	
	return des;
}



int main() {

	Mat src = imread("h2.tif", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", src);
	waitKey();
	Mat output = histogram(src);
	imshow("Primary Histogram Processing", output);
	waitKey();
	Mat eqlimg = equalize(src);
	imshow("Equalized Image", eqlimg);
	waitKey();
	Mat output2 = histogram(eqlimg);
	imshow("Equalized Histogram", output2);
	waitKey();
	Mat e = equalize(eqlimg);
	imshow("Equalized Image", e);
	waitKey();
	Mat output3 = histogram(e);
	imshow("Equalized Histogram", output3);
	waitKey();
}