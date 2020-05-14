#include "Menu.h"

int main()
{
	Mat img = imread("lena.jpg", IMREAD_COLOR);
	Mat Grey_img = imread("lena.jpg", IMREAD_COLOR);
	Mat noise = imread("noise.png", IMREAD_GRAYSCALE);
	Mat clahe = imread("clahe.png");
	while (true)
	{
		AfisareMenu();
		if (_kbhit())
		{

			switch (_getch())
			{
			case '1':_CASE_1(img); break;

			case '2':_CASE_2(img,Grey_img); break;

			case '3':_CASE_3(); break;

			case '4':_CASE_4(img, Grey_img); break;

			case '5':_CASE_5(noise); break;

			case '6':_CASE_6(clahe); break;

			case '*':goto here; //Iese din bucla infinita

			default:break;
			}

		}
		sleep(1);
		clrscr();
	}

	here:

	return 0;
}