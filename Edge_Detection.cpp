#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <math.h>


using namespace std;
using namespace cv;

void edge_detect(Mat srcx, Mat srcy) {

	Mat desx,desy,des,ix,iy,mag,ang;

	desx.create(srcx.size(), srcx.type());
	desy.create(srcx.size(), srcx.type());
	ix.create(srcx.size(), srcx.type());
	iy.create(srcx.size(), srcx.type());
	mag.create(srcx.size(), srcx.type());
	ang.create(srcx.size(), srcx.type());
	des.create(srcx.size(), srcx.type());

	float sigma;
	int t;
	cout<<"Enter Threshold value : ";
	cin>>t;
	cout << "Enter sigma : ";
	cin >> sigma;

	int maskSize;
	maskSize = (int) sigma*5.0;
	if (maskSize % 2 == 0)maskSize++;
	int s;
	s = maskSize / 2;
	float value,value2;
	float sigmaSq = sigma * sigma;
	


	Mat maskx,masky;
	maskx.create(maskSize, maskSize, CV_32F);
	masky.create(maskSize, maskSize, CV_32F);

	for (int y = -s, y1 = 0; y <= s; y++, y1++)
	{
		for (int x = -s, x1 = 0; x <= s; x++, x1++)
		{
			value = (-x)*exp((-((x*x)+(y*y)))/(2*sigmaSq));
			maskx.at<float>(y1, x1) = value;
		}

	}

	for (int y = -s, y1 = 0; y <= s; y++, y1++)
	{
		for (int x = -s, x1 = 0; x <= s; x++, x1++)
		{
			value2 = (-y)*exp((-((x*x)+(y*y)))/(2*sigmaSq));
			masky.at<float>(y1, x1) = value2;
		}

	}

	filter2D(srcx, desx, CV_32F, maskx, Point(-1, -1));
	filter2D(srcy, desy, CV_32F, masky, Point(-1, -1));
	normalize(desx, ix, 0, 255, NORM_MINMAX, CV_8U);
	normalize(desy, iy, 0, 255, NORM_MINMAX, CV_8U);

	imshow("X", ix);
	imshow("Y", iy);
	waitKey();
	
	cartToPolar(desx, desy, mag, ang, false);

	normalize(mag, mag, 0, 255, NORM_MINMAX, CV_8U);
	normalize(ang, ang, 0, 255, NORM_MINMAX, CV_8U);

	imshow("mag", mag);
	waitKey();
	imshow("ang", ang);
	waitKey();

	Mat edgeImg;
	threshold(mag,edgeImg,100,255,CV_THRESH_BINARY);
	imshow("edge",edgeImg);
	waitKey();


	/*for (int y = 0; y < srcx.rows; y++)
	{
		for (int x = 0; x < srcx.cols; x++)
		{

			float p = mag.at<float>(y,x);
			if(p>=t)des.at<float>(y,x) = 1;
			else des.at<float>(y,x) = 0;

		}
	}

	imshow("edge", des);
	waitKey();
	*/
	/*float x,y,z;

	for (int y = 0; y < srcx.rows; y++)
	{
		for (int x = 0; x < srcx.cols; x++)
		{

			x = ix.at<float>(y, x);
			y = iy.at<float>(y, x);
			z = x*x + y*y;
			z = sqrt(z);
			if(z>=t) des.at<float>(y,x)=1;
			else des.at<float>(y,x)=0;

		}
	}
	
	imshow("edge", des);
	waitKey();*/

}



int main() {

	Mat srcx = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat srcy = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("Input", srcx);
	waitKey();
	edge_detect(srcx,srcy);
	//imshow("Output", output);
	//waitKey();
	//des.create(src.size(),src.type());

}