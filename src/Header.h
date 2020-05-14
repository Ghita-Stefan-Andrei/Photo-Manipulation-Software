#pragma once
#include<opencv2/opencv.hpp>
#include<iostream>
#include<thread>  // SLEEP
#include<chrono>  // SLEEP
#include<conio.h> //_kbhit() _getch()
#include<string>
#include<sstream> //stringstream
#include<cmath>
#define X_POZ_OF_IMG 200
#define Y_POZ_OF_IMG 100
#define euler_nr exp(1.0)
#define sigmoid_cons -0.00439444915467
#define Black_Pixel 0
#define White_Pixel 255
#define Filter_size 5
using namespace std;
using namespace cv;