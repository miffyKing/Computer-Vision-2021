#include <iostream>
#include <opencv2\opencv.hpp>
#include <math.h>
#include <vector>
#include <tuple>

typedef struct ohmygod {
	int ga_coor;
	int se_coor;
	int rgb_b;
	int rgb_g;
	int rgb_r;
	float ga_coor_float;
	float se_coor_float;
}Ohmy;
//std::tuple<int, int, int> arr[3];
Ohmy arr[500][500];
cv::Mat problem_a_rotate_forward(cv::Mat img, double angle){
	//cv::Mat output;
	cv::Point2f center((img.rows - 1) / 2.0, (img.cols - 1) / 2.0);  //sero garo
	double seta = -1 * angle * CV_PI / 180.0;
	int sero = img.rows;
	int garo = img.cols;
	cv::Size2f size(sero, garo);
	int new_garo = (img.cols) * abs(cos(seta)) + (img.rows) * abs(sin(seta));
	int new_sero = (img.cols) * abs(sin(seta)) + (img.rows) * abs(cos(seta));
	cv::Point2f rot_center((new_sero) / 2.0, (new_garo) / 2.0);
	cv::Mat output = cv::Mat::zeros(new_sero, new_garo, img.type());
	cv::Mat real_output = cv::Mat::zeros(new_sero, new_garo, img.type());
	int min_ga = 10000;
	int min_se = 10000;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	int flag = 0;
	for (int i = 0; i < sero; i++) //세로
	{
		for (int j = 0; j < garo; j++) //가로
		{
			int i_ch, j_ch;
			int ro_ga, ro_se;
			ro_ga = cos(seta) * (i) - sin(seta) * (j);
			ro_se = sin(seta) * (i) + cos(seta) * (j);
			for (int x = 0; x < 3; x++)
			{
				arr[i][j].ga_coor = ro_ga;
				arr[i][j].se_coor = ro_se;
				arr[i][j].rgb_b = img.at<cv::Vec3b>(i, j)[0];
				arr[i][j].rgb_g = img.at<cv::Vec3b>(i, j)[1];
				arr[i][j].rgb_r = img.at<cv::Vec3b>(i, j)[2];
				min_ga = std::min(ro_ga, min_ga);
				min_se = std::min(ro_se, min_se);
			}
			if(ro_ga <=0 || ro_se <= 0)
			{
				flag = 1;
			}
		}
	}
	if (flag == 1)
	{
		if (min_se < 0 && min_ga < 0)
		{
			for (int i = 0; i < sero; i++)
			{
				for (int j = 0; j < garo; j++)
				{
					arr[i][j].ga_coor += abs(min_ga);
					arr[i][j].se_coor += abs(min_se);
				}
			}
		}
		else if (min_se < 0 && min_ga >= 0)
		{
			for (int i = 0; i < sero; i++)
			{
				for (int j = 0; j < garo; j++)
				{
					arr[i][j].se_coor += abs(min_se);
				}
			}
		}
		else if (min_ga < 0 && min_se >= 0)
		{
			for (int i = 0; i < sero; i++)
			{
				for (int j = 0; j < garo; j++)
				{
					arr[i][j].ga_coor += abs(min_ga);
				}
			}
		}
	}
	for (int i = 0; i <sero ; i++)
	{
		for (int j = 0; j < garo; j++)
		{
			output.at<cv::Vec3b>(arr[i][j].ga_coor, arr[i][j].se_coor)[0] = arr[i][j].rgb_b;
			output.at<cv::Vec3b>(arr[i][j].ga_coor, arr[i][j].se_coor)[1] = arr[i][j].rgb_g;
			output.at<cv::Vec3b>(arr[i][j].ga_coor, arr[i][j].se_coor)[2] = arr[i][j].rgb_r;
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); cv::waitKey(0);
	cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle)
{
	cv::Point2f center((img.rows - 1) / 2.0, (img.cols - 1) / 2.0);  //sero garo
	double seta = -1 * angle * CV_PI / 180.0;
	int sero = img.rows;
	int garo = img.cols;
	cv::Size2f size(sero, garo);
	int new_garo = (img.cols) * abs(cos(seta)) + (img.rows) * abs(sin(seta));
	int new_sero = (img.cols) * abs(sin(seta)) + (img.rows) * abs(cos(seta));
	cv::Point2f rot_center((new_sero) / 2.0, (new_garo) / 2.0);
	cv::Mat output = cv::Mat::zeros(new_sero, new_garo, img.type());
	cv::Mat real_output = cv::Mat::zeros(new_sero, new_garo, img.type());
	double min_ga = 10000;
	double min_se = 10000;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	int flag = 0;
	//printf("LLLL\n");
	for (int i = 0; i < sero; i++) //세로
	{
		for (int j = 0; j < garo; j++) //가로
		{
			int i_ch, j_ch;
			double ro_ga, ro_se;
			ro_se = cos(seta) * (i)- sin(seta) * (j);
			ro_ga = sin(seta) * (i)+ cos(seta) * (j);
	
			min_ga = std::min(ro_ga, min_ga);
			min_se = std::min(ro_se, min_se);
		}
	}
	//printf("%f %f\n", min_ga, min_se);
	for (int i = 0; i < new_sero; i++)
	{
		for (int j = 0; j < new_garo; j++)
		{
			double re_ro_se, re_ro_ga;
			re_ro_se = i - abs(min_se);
			re_ro_ga = j - abs(min_ga);
			int after_se = cos(seta)* (re_ro_se)+sin(seta) * (re_ro_ga);
			int after_ga = -1*sin(seta) * (re_ro_se)+cos(seta) * (re_ro_ga);

			if (after_se< sero && after_ga < garo && after_se >=0 && after_ga >=0)
			{
				output.at<cv::Vec3b>(i, j) = img.at<cv::Vec3b>(after_se, after_ga);
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("b_output", output); cv::waitKey(0);
	cv::waitKey(0);
	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle){
	//cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	cv::Point2f center((img.rows - 1) / 2.0, (img.cols - 1) / 2.0);  //sero garo
	double seta = -1 * angle * CV_PI / 180.0;
	int sero = img.rows;
	int garo = img.cols;
	cv::Size2f size(sero, garo);
	int new_garo = (img.cols) * abs(cos(seta)) + (img.rows) * abs(sin(seta));
	int new_sero = (img.cols) * abs(sin(seta)) + (img.rows) * abs(cos(seta));
	cv::Point2f rot_center((new_sero) / 2.0, (new_garo) / 2.0);
	cv::Mat output = cv::Mat::zeros(new_sero, new_garo, img.type());
	cv::Mat real_output = cv::Mat::zeros(new_sero, new_garo, img.type());
	double min_ga = 10000;
	double min_se = 10000;
	int flag = 0;
	//printf("LLLL\n");
	for (int i = 0; i < sero; i++) //세로
	{
		for (int j = 0; j < garo; j++) //가로
		{
			int i_ch, j_ch;
			double ro_ga, ro_se;
			ro_se = cos(seta) * (i)-sin(seta) * (j);
			ro_ga = sin(seta) * (i)+cos(seta) * (j);

			min_ga = std::min(ro_ga, min_ga);
			min_se = std::min(ro_se, min_se);
		}
	}
	//printf("%f %f\n", min_ga, min_se);
	for (int i = 0; i < new_sero-1; i++)
	{
		for (int j = 0; j < new_garo-1; j++)
		{
			double re_ro_se, re_ro_ga;
			re_ro_se = i - abs(min_se);
			re_ro_ga = j - abs(min_ga);
			double after_se = cos(seta) * (re_ro_se)+sin(seta) * (re_ro_ga);
			double after_ga = -1 * sin(seta) * (re_ro_se)+cos(seta) * (re_ro_ga);
			
			if (after_se - (int)after_se > 0 || after_ga - (int)after_ga > 0)
			{
				if (after_se+1 < sero && after_ga+1 < garo && after_se >= 0 && after_ga >= 0)
				{
					//printf("QQQQQ\n");
					//cv::Point2f B(floor(re_x), floor(re_y) + 1);
						//cv::Point2f C(floor(re_x) + 1, floor(re_y) + 1);
						//cv::Point2f A(floor(re_x), floor(re_y));
						//cv::Point2f D(floor(re_x), floor(re_y) + 1); //좌표확인용으로 만들고 사용하지는 않음
					float alpha = after_se - floor(after_se);
					float beta = floor(after_se) + 1 - after_se;
					float p = after_ga - floor(after_ga);  float q = floor(after_ga) + 1 - after_ga;
					float w1 = after_ga - floor(after_ga); float w2 = floor(after_ga) + 1 - after_ga;
					float h1 = after_se - floor(after_se); float h2 = floor(after_se) + 1 - after_se;
					int rgb_arr[4][3];

					for (int k = 0; k < 3; k++)
					{
						rgb_arr[0][k] = img.at<cv::Vec3b>(floor(after_se), floor(after_ga))[k]; //a
						rgb_arr[1][k] = img.at<cv::Vec3b>(floor(after_se), floor(after_ga) + 1)[k]; //b
						rgb_arr[2][k] = img.at<cv::Vec3b>(floor(after_se)+1, floor(after_ga) + 1)[k]; //c
						rgb_arr[3][k] = img.at<cv::Vec3b>(floor(after_se), floor(after_ga) + 1)[k]; //d
					}
					float final_b = (q * beta * rgb_arr[0][0]) + (q * alpha * rgb_arr[1][0]) + (p * beta * rgb_arr[3][0]) + (p * alpha * rgb_arr[2][0]);
					float final_g = (q * beta * rgb_arr[0][1]) + (q * alpha * rgb_arr[1][1]) + (p * beta * rgb_arr[3][1]) + (p * alpha * rgb_arr[2][1]);
					float final_r = (q * beta * rgb_arr[0][2]) + (q * alpha * rgb_arr[1][2]) + (p * beta * rgb_arr[3][2]) + (p * alpha * rgb_arr[2][2]);
					//pdf에서 주어진 식 그대로 옮겨적은 것
					output.at<cv::Vec3b>(i, j)[0] = final_b;
					output.at<cv::Vec3b>(i, j)[1] = final_g;
					output.at<cv::Vec3b>(i, j)[2] = final_r;
					//output.at<cv::Vec3b>(i, j) = img.at<cv::Vec3b>(after_se, after_ga);
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("c_output", output); cv::waitKey(0);
	cv::waitKey(0);
	return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {
	/*
	img : input image
	num : number for brightness (increase or decrease)
	x : x coordinate of image (for square part)
	y : y coordinate of image (for square part)

	*/
	cv::Mat output = img.clone();
	int size = 100;
	int height = (y + 100 > img.cols) ? img.cols : y + 100;
	int width = (x + 100 > img.rows) ? img.rows : x + 100;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}

	}
	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	return output;
}

int main(void){

	double angle = 45.0f;
	angle *= -1;
	cv::Mat input = cv::imread("lena.jpg");
	//Fill problem_a_rotate_forward and show output
	//problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	//problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
	//Example how to access pixel value, change params if you want
	//Example_change_brightness(input, 100, 50, 125);
}