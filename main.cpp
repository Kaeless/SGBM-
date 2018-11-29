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
	//�����������У����Ӳ�����Ч��Ӱ��ϴ����Ҫ������ SADWindowSize��numberOfDisparities �� uniquenessRatio ������һ��ֻ����������������е��������������Ĭ�����ü��ɡ�
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
	sgbm(left_img, right_img, disp);//disp���������������short����
	Mat disp8, color(disp.size(), CV_8UC3);
	disp.convertTo(disp8, CV_8U, 255 / (numberOfDisparities*16.));//ת����uchar��ʾ

	sgbm.GenerateFalseMap(disp8, color);
	imshow("", color);
	imshow("", disp8);
	waitKey(10);
}
