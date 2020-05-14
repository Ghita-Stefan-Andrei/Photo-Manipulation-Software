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
	cout << " Pentru a aplica filtru de zgomot apasati 5:" << endl;
	cout << " Pentru a afisa clahe apasati 6:" << endl;
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
	Mat b(4 + img.rows, 4 + img.cols, 0);
	{
		for (int i = 2; i < img.rows + 2; i++)
		{
			for (int j = 2; j < img.cols + 2; j++)
			{
				b.at<int8_t>(i, j) = img.at<int8_t>(i - 2, j - 2);
			}
		}
		for (int i = 0; i < img.rows + 4; i++)
		{
			for (int j = 0; j < img.cols + 4; j++)
			{
				//skip pt elementele mat
				if ((i >= 2 && i < img.rows + 2) || (j >= 0 && j < 2 && j >= img.cols + 2 && j < img.cols + 4))
				{
					continue;
				}
				//sus
				if (i >= 0 && i < 2 && j >= 2 && j < img.rows + 2)
				{
					//mat2[i][j] = mat[0][j - WinSize / 2];
					b.at<int8_t>(i, j) = img.at<int8_t>(0, j - 2);
				}
				//jos
				if (i >= img.rows + 2 && i < img.rows + 4 && j >= 2 && j < img.cols + 2)
				{
					//mat2[i][j] = mat[h - 1][j - WinSize / 2];
					b.at<int8_t>(i, j) = img.at<int8_t>(img.rows - 1, j - 2);
				}
			}
		}
		for (int i = 0; i < img.rows + 4; i++)
		{
			for (int j = 0; j < img.cols + 4; j++)
			{
				//skip pt elementele mat
				if (j >= 2 && j < img.cols + 2)
				{
					continue;
				}
				//stanga
				if (i >= 0 && i < img.rows + 4 && j >= 0 && j < 2)
				{
					//mat2[i][j] = mat2[i][WinSize / 2];
					b.at<int8_t>(i, j) = b.at<int8_t>(i, 2);
				}
				//dreapta
				if (i >= 0 && i < img.rows + 4 && j >= img.cols + 2 && j < img.cols + 4)
				{
					//mat2[i][j] = mat2[i][l + WinSize / 2 - 1];
					b.at<int8_t>(i, j) = b.at<int8_t>(i, img.cols + 1);
				}
			}
		}
	}
	imwrite("tocolor.png", b);
	Mat c = imread("tocolor.png", IMREAD_COLOR);
	int nr = 0;
	imwrite("i.png", img);
	Mat filtrat = imread("i.png",IMREAD_COLOR);
	Mat t = filtrat;
	int pro = (filtrat.rows * filtrat.cols) / 100;
	int pixelcount = 0;
	int spro = 0;
	//imshow("Filtru_off", c);
	//moveWindow("Filtru_off", 100, 100);
	//waitKey(1);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			filtrat.at<Vec3b>(i, j) = filtruMedian(i,j,t);
			//pause();
			pixelcount++;
			if (pixelcount == pro)
			{
				clrscr();
				cout << " Progres filtru: " << ++spro << "%" << endl;
				pixelcount = 0;
			}
		}
	}
	//medianBlur(img, noise, 5);
	namedWindow("Filtru_On", WINDOW_AUTOSIZE);
	imshow("Filtru_On", filtrat);
	moveWindow("Filtru_On", 105 + filtrat.cols, 100);
	waitKey();
	destroyAllWindows();
}
void _CASE_6(Mat& img)
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