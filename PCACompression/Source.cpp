#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	Mat image;
	image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	double mean[3] = { 0, 0, 0 };	// mean vector
	double cov[3][3];	// covariance matrix

	// initialize the matrix with 0s
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cov[i][j] = 0;
		}
	}

	int n = image.rows * image.cols; // number of pixels of a single color

	// ASSUME BGRBGRBGRBGR

	for (int i = 0; i < n * 3;  i += 3)
	{
		// First, calculate the average values
		mean[0] += image.data[i];	  // avg blue value
		mean[1] += image.data[i + 1]; // avg green value
		mean[2] += image.data[i + 2]; // avg red value

	}

	mean[0] /= n;
	mean[1] /= n;
	mean[2] /= n;

	cout << "Mean Blue: " << mean[0] << endl;
	cout << "Mean Green: " << mean[1] << endl;
	cout << "Mean Red: " << mean[2] << endl;
		
	// Next, calculate the covariance matrix:

	// var(blue) = cov[0][0]
	for (int i = 0; i < n*3; i+=3)
	{
		cov[0][0] += ((image.data[i] - mean[0]) * (image.data[i] - mean[0]));
	}
	cov[0][0] /= (n-1);

	// cov(blue,green) = cov[0][1]
	for (int i = 0; i < n * 3; i += 3)
	{
		cov[0][1] += ((image.data[i] - mean[0]) * (image.data[i + 1] - mean[1]));
	}
	cov[0][1] /= (n-1);

	// cov(blue,red) = cov[0][2]
	for (int i = 0; i < n * 3; i += 3)
	{
		cov[0][2] += ((image.data[i] - mean[0]) * (image.data[i + 2] - mean[2]));
	}
	cov[0][2] /= (n-1);


	cov[1][0] = cov[0][1]; // same values so no need to recalculate
	
	// var(green) = cov[1][1]
	for (int i = 0; i < n * 3; i += 3)
	{
		cov[1][1] += ((image.data[i+1] - mean[1]) * (image.data[i+1] - mean[1]));
	}
	cov[1][1] /= (n - 1);

	// cov(green, red) = cov[1][2]
	for (int i = 0; i < n * 3; i += 3)
	{
		cov[1][2] += ((image.data[i+1] - mean[1]) * (image.data[i + 2] - mean[2]));
	}
	cov[1][2] /= (n - 1);

	cov[2][0] = cov[0][2]; // same values so no need to recalculate

	cov[2][1] = cov[1][2]; // same values

	// var(red) = cov[2][2]
	for (int i = 0; i < n * 3; i+=3)
	{
		cov[2][2] += ((image.data[i + 2] - mean[2]) * (image.data[i + 2] - mean[2]));
	}
	cov[2][2] /= (n - 1);

	cout << endl;

	// display the covariance values
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << cov[i][j] << " ";
		}

		cout << endl;
	}

	// calculate the eigenvalues/vectors
	





	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", image);                   // Show our image inside it.

	waitKey(0);                                          // Wait for a keystroke in the window
	return 0;
}