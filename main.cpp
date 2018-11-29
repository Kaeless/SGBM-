#include"sgbm.h"
int main()
{

	Mat left_img = imread("l_7.bmp", 0);
	Mat right_img = imread("r_7.bmp", 0);
	//Mat left_img = imread("left.png", 0);
	//Mat right_img = imread("right.png", 0);
	//imshow("left", left_img);
	//waitKey(10);

	cv::myStereoSGBM sgbm;
	//在上述参数中，对视差生成效果影响较大的主要参数是 SADWindowSize、numberOfDisparities 和 uniquenessRatio 三个，一般只需对这三个参数进行调整，其余参数按默认设置即可。
	int SADWindowSize = 11;
	sgbm.preFilterCap = 63;
	sgbm.SADWindowSize = SADWindowSize > 0 ? SADWindowSize : 3;
	int cn = left_img.channels();
	int numberOfDisparities = 512;
	sgbm.P1 = 16 * cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
	sgbm.P2 = 64 * cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
	sgbm.minDisparity = 0;
	sgbm.numberOfDisparities = numberOfDisparities;
	sgbm.uniquenessRatio = 7;
	sgbm.speckleWindowSize = 100;
	sgbm.speckleRange = 10;
	sgbm.disp12MaxDiff = 1;
	Mat disp;
	sgbm(left_img, right_img, disp);//disp经过处理输出的是short类型
	Mat disp8, color(disp.size(), CV_8UC3);
	disp.convertTo(disp8, CV_8U, 255 / (numberOfDisparities*16.));//转化成uchar显示

	sgbm.GenerateFalseMap(disp8, color);
	imshow("", color);
	imshow("", disp8);
	waitKey(10);
}
