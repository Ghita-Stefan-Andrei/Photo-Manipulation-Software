#pragma once
#include "Header.h"
void clrscr()
{
	cout << "\033[2J\033[1;1H";
}
void sleep(int seconds)
{
	int milliseconds = seconds * 1000;
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
void pause()
{
	while (true) { if (_kbhit()) { _getch(); break; } }
}
char pause_and_getch()
{
	char x;
	while (true) { if (_kbhit()) { x = _getch(); break; } }
	return x;
}
template <typename T,typename TT>
TT convert(T a)
{
	stringstream ss;
	TT b;
	ss << a;
	ss >> b;
	return b;
}
int sig(int x)
{
	return 100 / (1 + pow(euler_nr, sigmoid_cons * x));
}
int lower_point(int x)
{
	return -x / 2;
}
int upper_point(int x)
{
	return x / 2 + 1;
}
Vec3b aritm(vector<Vec3b> v)
{
	//v.erase(v.begin() + (v.size()) / 2);
	Vec3b s;
	s[0] = 0;
	s[1] = 0;
	s[2] = 0;
	for (int i = 0; i < v.size(); i++)
	{
		s[0] += v[i][0];
		s[1] += v[i][1];
		s[2] += v[i][2];
	}
	int b = s[0] / v.size();
	int g = s[1] / v.size();
	int r = s[2] / v.size();
	s[0] = b;
	s[1] = g;
	s[2] = r;
	return s;
}
//int AbatereP(vector<int>v)
//{
//	int8_t a = aritm(v);
//	int8_t sumas = 0;
//	for (int i = 0; i < v.size(); i++)
//	{
//		sumas += (a - v[i]) * (a - v[i]);
//	}
//	return sqrt(sumas / (v.size() * (v.size() + 1)));
//}
Vec3b getPixel(Mat& img, int x, int y)
{
	int width = img.cols;
	int height = img.rows;
	if (x < 0) x = 0;
	if (y >= width) y = width - 1;
	if (y < 0) y = 0;
	if (x >= height) x = height - 1;
	Vec3b ret = img.at<Vec3b>(x, y);
	return ret;
}
bool sortare_p(Vec3b a, Vec3b b)
{
	return a[0] < b[0];
}
Vec3b filtruMedian(int ii, int jj, Mat& img)
{
	vector<Vec3b> de_sort;
	for (int i = lower_point(Filter_size); i < upper_point(Filter_size); i++)
	{
		for (int j = lower_point(Filter_size); j < upper_point(Filter_size); j++)
		{
			de_sort.push_back(getPixel(img,i,j));
			//cout << i << " " << j << " " << getPixel(img, i, j) << endl;
		}
	}
	sort(de_sort.begin(), de_sort.end(),sortare_p);
	/*for (int i = 0; i < de_sort.size(); i++)
	{
		cout << de_sort[i] << " ";
	}
	cout << endl;*/
	/*for (int i = 0; i < Filter_size * Filter_size - 1; i++)
	{
		for (int j = i + 1; j < Filter_size * Filter_size; j++)
		{
			if (de_sort[i][0] > de_sort[j][0])
			{
				Vec3b aux = de_sort[i];
				de_sort[i] = de_sort[j];
				de_sort[j] = aux;
			}
		}
	}*/

	return de_sort[Filter_size * Filter_size / 2];
}
