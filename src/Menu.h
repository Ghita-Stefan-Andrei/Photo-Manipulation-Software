#pragma once
#include "Header.h"
#include "Tools.h"

void AfisareMenu()
{
	cout << " Apasati orice tasta pt a inchide o imagine deschisa." << endl;
	cout << " Apasati \"*\" pt a inchide aplicatia." << endl << endl;
	cout << " ~MENU~ " << endl << endl;
	cout << " Pentru afisarea imaginii selectate apasati 1:" << endl;
	cout << " Pentru afisarea imaginii in alb si negru apasati 2:" << endl;
	cout << " Pentru afisarea imaginii redimensionate apasati 3 si introduceti de cate ori vreti sa fie marita:" << endl;
	cout << " Pentru a afisa histograme pt BGR si Greyscale apasati 4:" << endl;
	cout << " Pentru a afisa clahe apasati 5:" << endl;
}



//CASE 1
void _CASE_1(Mat img)
{
	imshow("Original", img);
	moveWindow("Original", 200,100);
	resizeWindow("Original", img.rows, img.cols);
	waitKey();
	destroyWindow("Original");
}
//CASE 2
void _CASE_2(Mat img, Mat& grey)
{
	for (int i = 0; i < grey.rows; i++)
	{
		for (int j = 0; j < grey.cols; j++)
		{
			grey.at<Vec3b>(i, j)[0] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
			grey.at<Vec3b>(i, j)[1] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
			grey.at<Vec3b>(i, j)[2] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
		}
	}
	namedWindow("GS", WINDOW_AUTOSIZE);
	imshow("GS", grey);
	moveWindow("GS", X_POZ_OF_IMG, Y_POZ_OF_IMG);
	waitKey();
	destroyWindow("GS");
}
//CASE 3
void _CASE_3()
{
	Mat img = imread("lena.jpg", IMREAD_GRAYSCALE);
	int zoom; 
	cout << " Introduceti valoare dorita:";
	cin >> zoom;
	Mat zimg(img.size() * zoom, 0);

	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			for (int k = 0; k < zoom; k++)
			{
				for (int h = 0; h < zoom; h++)
				{
					zimg.at<int8_t>(i * zoom + k, j * zoom + h) = img.at<int8_t>(i, j);
				}
			}
		}
	}

	namedWindow("ReSized", WINDOW_AUTOSIZE);
	imshow("ReSized", zimg);
	moveWindow("ReSized", 10 + img.cols, 5);
	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", img);
	moveWindow("img", 5, 5);
	waitKey();
	destroyAllWindows();
}
void _CASE_4(Mat img,Mat grey)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			grey.at<Vec3b>(i, j)[0] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
			grey.at<Vec3b>(i, j)[1] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
			grey.at<Vec3b>(i, j)[2] = (img.at<Vec3b>(i, j)[0] + img.at<Vec3b>(i, j)[1] + img.at<Vec3b>(i, j)[2]) / 3;
		}
	}
	vector<int> red;
	vector<int> green;
	vector<int> blue;
	vector<int>grey_v;
	for (int i = 0; i < 256; i++)
	{
		red.push_back(0);
		green.push_back(0);
		blue.push_back(0);
		grey_v.push_back(0);
	}
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			red[img.at<Vec3b>(i, j)[2]] += 1;
			green[img.at<Vec3b>(i, j)[1]] += 1;
			blue[img.at<Vec3b>(i, j)[0]] += 1;
			grey_v[grey.at<Vec3b>(i, j)[0]] += 1;
		}
	}
	Mat b_hist = imread("hist.jpg", IMREAD_COLOR);
	Mat g_hist = imread("hist.jpg", IMREAD_COLOR);
	Mat r_hist = imread("hist.jpg", IMREAD_COLOR);
	Mat gr_hist = imread("hist.jpg", IMREAD_COLOR);
	for (int i = 0; i < b_hist.rows; i++)
	{
		for (int j = 0; j < b_hist.cols; j++)
		{
			int b = sig(blue[j]);
			b_hist.at<Vec3b>(b_hist.rows - 1 - b, j)[0] = 255;
			b_hist.at<Vec3b>(b_hist.rows - 1 - b, j)[1] = 0;
			b_hist.at<Vec3b>(b_hist.rows - 1 - b, j)[2] = 0;

			int g = sig(green[j]);
			g_hist.at<Vec3b>(g_hist.rows - 1 - g, j)[0] = 0;
			g_hist.at<Vec3b>(g_hist.rows - 1 - g, j)[1] = 255;
			g_hist.at<Vec3b>(g_hist.rows - 1 - g, j)[2] = 0;

			int r = sig(red[j]);
			r_hist.at<Vec3b>(r_hist.rows - 1 - r, j)[0] = 0;
			r_hist.at<Vec3b>(r_hist.rows - 1 - r, j)[1] = 0;
			r_hist.at<Vec3b>(r_hist.rows - 1 - r, j)[2] = 255;

			int gr = sig(grey_v[j]);
			gr_hist.at<Vec3b>(gr_hist.rows - 1 - gr, j)[0] = 255 / 2;
			gr_hist.at<Vec3b>(gr_hist.rows - 1 - gr, j)[1] = 255 / 2;
			gr_hist.at<Vec3b>(gr_hist.rows - 1 - gr, j)[2] = 255 / 2;
		}
	}

	namedWindow("img", WINDOW_AUTOSIZE);
	imshow("img", img);
	moveWindow("img", 200, 100);

	namedWindow("BLUE_histogram", WINDOW_AUTOSIZE);
	imshow("BLUE_histogram", b_hist);
	moveWindow("BLUE_histogram", 205 + img.cols, 100);

	namedWindow("RED_histogram", WINDOW_AUTOSIZE);
	imshow("RED_histogram", r_hist);
	moveWindow("RED_histogram", 205 + img.cols, 135 + b_hist.rows);

	namedWindow("GREEN_histogram", WINDOW_AUTOSIZE);
	imshow("GREEN_histogram", g_hist);
	moveWindow("GREEN_histogram", 210 + img.cols + b_hist.cols, 100);

	namedWindow("GREY_histogram", WINDOW_AUTOSIZE);
	imshow("GREY_histogram", gr_hist);
	moveWindow("GREY_histogram", 210 + img.cols + b_hist.cols, 135 + b_hist.rows);

	namedWindow("Grey_img", WINDOW_AUTOSIZE);
	imshow("Grey_img", grey);
	moveWindow("Grey_img", 200 + 5 + 5 + 5 + b_hist.cols + b_hist.cols + img.cols, 100);

	waitKey();

	destroyAllWindows();
}
void _CASE_5(Mat& img)
{
	Mat lab_image;
	cvtColor(img, lab_image, COLOR_BGR2Lab);

	vector<cv::Mat> lab_planes(3);
	split(lab_image, lab_planes);

	Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	Mat dst;
	clahe->apply(lab_planes[0], dst);

	dst.copyTo(lab_planes[0]);
	merge(lab_planes, lab_image);

	Mat image_clahe;
	cvtColor(lab_image, image_clahe, COLOR_Lab2BGR);

	imshow("image original", img);
	imshow("image CLAHE", image_clahe);
	waitKey();
	destroyAllWindows();
}
