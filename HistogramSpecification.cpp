#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

float array2[256];

Mat histogram(Mat src) {

	Mat des;
	des.create(300, 255, CV_8UC1);

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
		for (int j = 300 - array[i]; j < 300; j++) {
			des.at<uchar>(j, i) = 255;
		}
	}


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
		array[i] = (float)array[i] / x;
	}

	float sum = 0.0;

	for (int i = 0; i < 255; i++) {
		sum = 0.0;
		for (int j = 0; j <= i; j++) {
			sum = sum + array[j];
		}
		array2[i] = sum;
		array2[i] = array2[i] * 255;
		array2[i] = cvRound(array2[i]);
	}

	for (int y = 0; y < des.rows; y++)
	{
		for (int x = 0; x < des.cols; x++)
		{
			int val = des.at<uchar>(y, x);
			des.at<uchar>(y, x) = array2[val];
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

	/* Start : Histogram of Gaussian Function */

	float sigma;
	float meu;
	cout << "Enter The value of Sigma : ";
	cin >> sigma;
	cout << "Enter The value of Meu : ";
	cin >> meu;

	float gaus[256];
	float cgaus[256];
	float max = 0;

	for (int i = 0; i < 255; i++) {
		gaus[i] = sqrt(2 * acos(-1));
		gaus[i] *= sigma;
		gaus[i] = 1 / gaus[i];
		gaus[i] *= exp((-(i - meu)*(i - meu)) / (2 * sigma*sigma));
		if (gaus[i] > max)max = gaus[i];
	}

	float sum = 0.0;

	for (int i = 0; i < 255; i++) {
		sum = 0.0;
		for (int j = 0; j <= i; j++) {
			sum = sum + gaus[j];
		}
		cgaus[i] = sum;
		cgaus[i] = 255 * cgaus[i];
		cgaus[i] = cvRound(cgaus[i]);
	}

	Mat gausout;
	gausout.create(300, 255, CV_8UC1);

	for (int y = 0; y < gausout.rows; y++)
	{
		for (int x = 0; x < gausout.cols; x++)
		{
			gausout.at<uchar>(y, x) = 0;
		}
	}

	for (int i = 0; i < 255; i++) {
		gaus[i] = gaus[i] * 300;
		gaus[i] = gaus[i] / max;
	}

	for (int i = 0; i < 255; i++) {
		for (int j = 300 - gaus[i]; j < 300; j++) {
			gausout.at<uchar>(j, i) = 255;
		}
	}

	imshow("Gaussian Histogram", gausout);
	waitKey();


	/* End : Histogram of Gaussian Function */


	Mat eqlimg = equalize(src);
	imshow("Equalized Image", eqlimg);
	waitKey();
	Mat output2 = histogram(eqlimg);
	imshow("Equalized Histogram", output2);
	waitKey();

	int finalarray[256];

	/* Start: Mapping of s and z */
	int k;
	int min = 99999;

	for (int i = 0; i < 255; i++) {
		min = 99999;
		for (int j = 0; j < 255; j++) {
			int val = abs(array2[i] - cgaus[j]);
			if (val < min) {
				min = val;
				k = j;
			}
		}
		finalarray[i] = k;
	}

	Mat matchOut = src.clone();

	for (int y = 0; y < matchOut.rows; y++)
	{
		for (int x = 0; x < matchOut.cols; x++)
		{
			int val = matchOut.at<uchar>(y, x);
			matchOut.at<uchar>(y, x) = finalarray[val];
		}
	}
	
	imshow("Histogram matching output",matchOut);
	waitKey();

	Mat matchHis = histogram(matchOut);
	imshow("Matched Histogram", matchHis);
	waitKey();
	/* End: Mapping of s and z */


}