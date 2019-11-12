//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include<string>
//
//using namespace cv;
//using namespace std;
//
//// return center of Rect
//Point2f findRect(Mat input, Mat mask){
//
//
//	erode(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);
//
//	dilate(mask, mask, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)), Point(-1, -1), 2);
//
//	// extract contours
//	vector<vector<Point>> contours;
//	findContours(mask, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
//	Point2f center;
//	double max_rect = 0;
//	for (int i = 0; i<contours.size(); ++i)
//	{
//		double rect_size = contourArea(contours[i]);
//		Moments mu = moments(contours[i], false);
//
//		if (max_rect < rect_size){
//			max_rect = rect_size;
//			center = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
//			//circle(input, center, 15, Scalar(0,255,0),5); // draw center
//		}
//	}
//	return center;
//}
//
//Point2f getCenter(Point2f pR, Point2f pY){
//	return Point2f((pR.x + pY.x) / 2, (pR.y + pY.y) / 2);
//}
//
//int BlurCutML(char* imgPath, int lowerBound) {
//	string fileName = imgPath;
//	std::string base_filename = fileName.substr(fileName.find_last_of("/\\") + 1);
//	bool _debug = false;
//
//	Mat rawImg_ = imread(imgPath, 1);
//	if (rawImg_.rows == 0) return -1;//loi doc anh
//	cv::Mat pyImg, hsv, gray, src;
//
//	if (rawImg_.rows > rawImg_.cols) {
//		//neu bi lon thi xoay anh
//		resize(rawImg_, src, cv::Size(1500, 2000));
//		Point2f pt(src.cols / 2.0, src.rows / 2.0);
//		Mat r = getRotationMatrix2D(pt, 90, 1.0);
//		Rect box = RotatedRect(pt, src.size(), 90).boundingRect();
//		r.at<double>(0, 2) += box.width / 2.0 - pt.x;
//		r.at<double>(1, 2) += box.height / 2.0 - pt.y;
//		warpAffine(src, pyImg, r, box.size());
//	}
//	else resize(rawImg_, pyImg, Size(2000, 1500));//fix cố định kích thước resize để xử lý
//
//	Mat greenImg, yellowImg, blueImg, red1, red2, red, regImg, dst;
//
//	cv::cvtColor(pyImg, hsv, cv::COLOR_BGR2HSV);
//	cv::cvtColor(pyImg, gray, cv::COLOR_BGR2GRAY);
//	//loc cac kenh mau hsv
//	GaussianBlur(gray, gray, Size(3, 3), 0);
//	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
//	inRange(hsv, Scalar(95, 150, 50), Scalar(140, 255, 255), blueImg);
//	dilate(blueImg, blueImg, element, Point(-1, -1), 2);
//	inRange(hsv, Scalar(35, 50, 20), Scalar(90, 255, 255), greenImg);
//	dilate(greenImg, greenImg, element, Point(-1, -1), 2);
//	inRange(hsv, Scalar(15, 70, 70), Scalar(35, 255, 255), yellowImg);
//	dilate(yellowImg, yellowImg, element, Point(-1, -1), 2);
//	inRange(hsv, Scalar(165, 50, 50), Scalar(200, 255, 255), red1);
//	inRange(hsv, Scalar(0, 50, 50), Scalar(10, 255, 255), red2);
//	bitwise_or(red1, red2, red);
//	dilate(red, red, element, Point(-1, -1), 2);
//
//	bitwise_or(yellowImg, red, dst);
//	bitwise_or(blueImg, dst, dst);
//	bitwise_or(greenImg, dst, dst);
//
//
//	std::vector<std::vector<cv::Point> > contours_;
//	Point2f pGreen(0, 0), pBlue(0, 0), pRed(0, 0), pYellow(0, 0), center;
//	Moments mu;
//	int numColor = 0;
//	double area = 0, areaMax = 0, distan;
//	Mat dstColor;
//	cvtColor(dst, dstColor, CV_GRAY2BGR);
//
//	//count num square color green-red-blue-yellow > 3 is pass
//	int minAreaCamSau2 = 5000;
//	findContours(dst.clone(), contours_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//	for (int i = 0; i < contours_.size(); i++) {
//		area = contourArea(contours_[i]);
//
//		if (area > minAreaCamSau2) {
//			numColor++;
//			if (_debug) {
//				drawContours(dstColor, contours_, i, Scalar(0, 0, 255), 2);
//			}
//			cout << area << " ";
//		}
//	}
//	//check mau tren do hinh neu khong du 3/4 mau thi return faile
//	if (numColor < 3) return -2;//loi khong du mau 
//	//find center yellow
//	contours_.clear();
//	areaMax = 0;
//	//find center yellow
//	findContours(yellowImg.clone(), contours_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//	for (int i = 0; i < contours_.size(); i++) {
//		area = contourArea(contours_[i]);
//		if (area > 1000 && areaMax < area) {
//			mu = moments(contours_[i]);
//			pYellow = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
//			areaMax = area;
//		}
//	}
//	//find center red
//	contours_.clear();
//	areaMax = 0;
//
//	findContours(red.clone(), contours_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//	for (int i = 0; i < contours_.size(); i++) {
//		area = contourArea(contours_[i]);
//		if (area > 1000 && areaMax < area) {
//			areaMax = area;
//			mu = moments(contours_[i]);
//			pRed = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
//		}
//	}
//
//	Point2f pCenter((pRed.x + pYellow.x) / 2, (pRed.y + pYellow.y) / 2);
//	float distanceRed_yel = sqrt((pYellow.x - pRed.x)*(pYellow.x - pRed.x) + (pYellow.y - pRed.y)*(pYellow.y - pRed.y));
//	float distanceGreen_Blue;
//	distanceGreen_Blue = distanceRed_yel / 0.7292;
//	Rect allRectChart[12];
//
//	pBlue = Point2f(pCenter.x + distanceGreen_Blue / 2, pCenter.y);
//	pGreen = Point2f(pCenter.x - distanceGreen_Blue / 2, pCenter.y);
//
//	Point2f pRY(0.25*pRed.x + 0.75*pYellow.x, 0.25*pRed.y + 0.75*pYellow.y), pYR(0.75*pRed.x + 0.25*pYellow.x, 0.75*pRed.y + 0.25*pYellow.y);
//	Point2f pGB(pCenter.x + 0.21*distanceGreen_Blue, pCenter.y), pBG(pCenter.x - 0.21*distanceGreen_Blue, pCenter.y);
//
//	//cat hinh chu nhat
//	float para1, para2;
//	if (fileName.find("CamTruoc") != std::string::npos || fileName.find("Cam_truoc") != std::string::npos) {
//		para1 = 0.93;
//		para2 = -40;
//	}
//	else if (fileName.find("CamSau1") != std::string::npos || fileName.find("Cam_sau_1") != std::string::npos) {
//		para1 = 0.93;
//		para2 = 0;
//	}
//	else {
//		para1 = 0.942;
//		para2 = 25;
//	}
//	allRectChart[0] = Rect(pRY.x - 40, pRY.y - 150, 80, 300);
//	allRectChart[1] = Rect(pYR.x - 40, pYR.y - 150, 80, 300);
//	allRectChart[2] = Rect(pGB.x - 150, pGB.y - 40, 300, 80);
//	allRectChart[3] = Rect(pBG.x - 150, pBG.y - 40, 300, 80);
//
//	allRectChart[4] = Rect((pCenter.x - distanceGreen_Blue / 4) - 150, (pCenter.y - para1*distanceRed_yel / 2) - 40, 300, 80);
//	allRectChart[5] = Rect((pCenter.x + distanceGreen_Blue / 4) - 150, (pCenter.y - para1*distanceRed_yel / 2) - 40, 300, 80);
//	allRectChart[6] = Rect((pCenter.x - distanceGreen_Blue / 4) - 150, (pCenter.y + para1*distanceRed_yel / 2) - 40, 300, 80);
//	allRectChart[7] = Rect((pCenter.x + distanceGreen_Blue / 4) - 150, (pCenter.y + para1*distanceRed_yel / 2) - 40, 300, 80);
//
//	allRectChart[8] = Rect((pCenter.x + distanceGreen_Blue / 2) - 40 + para2, (pCenter.y - 0.483*distanceRed_yel / 2) - 150, 80, 300);
//	allRectChart[9] = Rect((pCenter.x - distanceGreen_Blue / 2) - 40 - para2, (pCenter.y - 0.483*distanceRed_yel / 2) - 150, 80, 300);
//	allRectChart[10] = Rect((pCenter.x + distanceGreen_Blue / 2) - 40 + para2, (pCenter.y + 0.483*distanceRed_yel / 2) - 150, 80, 300);
//	allRectChart[11] = Rect((pCenter.x - distanceGreen_Blue / 2) - 40 - para2, (pCenter.y + 0.483*distanceRed_yel / 2) - 150, 80, 300);
//
//	//check for debug
//	if (_debug) {
//		for (int i = 0; i < 12; i++) {
//			if (i < 4)
//				rectangle(pyImg, allRectChart[i], Scalar(0, 0, 255), 3);
//			else if (i < 8) rectangle(pyImg, allRectChart[i], Scalar(0, 255, 0), 3);
//			else rectangle(pyImg, allRectChart[i], Scalar(255, 0, 0), 3);
//		}
//		circle(pyImg, pRY, 10, Scalar(0, 0, 255), 8);
//		circle(pyImg, pYR, 10, Scalar(0, 255, 255), 8);
//		circle(pyImg, pGB, 10, Scalar(255, 0, 255), 8);
//		circle(pyImg, pBG, 10, Scalar(0, 255, 255), 8);
//		circle(dstColor, pGreen, 50, Scalar(0, 255, 0), 8);
//		circle(dstColor, pBlue, 50, Scalar(255, 0, 0), 8);
//		circle(dstColor, pRed, 50, Scalar(0, 0, 255), 8);
//		circle(dstColor, pYellow, 50, Scalar(0, 255, 255), 8);
//
//		line(dstColor, pYellow, pRed, Scalar(0, 0, 255), 3);
//		//cout << " dx = "<<abs(pYellow.x - pRed.x) <<"  dy = " <<abs(pYellow.y - pRed.y)<<" distance="<< distance;
//		namedWindow("pyImg", CV_WINDOW_KEEPRATIO);
//		imshow("pyImg", pyImg);
//
//		namedWindow("dstColor", CV_WINDOW_KEEPRATIO);
//		imshow("dstColor", dstColor);
//
//		namedWindow("dstImg", CV_WINDOW_KEEPRATIO);
//		imshow("dstImg", dst);
//		waitKey();
//	}
//
//	for (int i = 0; i < 12; i++) {
//		Mat cutImg = gray(allRectChart[i]), reCut;
//		if (cutImg.rows > cutImg.cols) {
//			Point2f pt(cutImg.cols / 2.0, cutImg.rows / 2.0);
//			Mat r = getRotationMatrix2D(pt, 90, 1.0);
//			Rect box = RotatedRect(pt, cutImg.size(), 90).boundingRect();
//			r.at<double>(0, 2) += box.width / 2.0 - pt.x;
//			r.at<double>(1, 2) += box.height / 2.0 - pt.y;
//			warpAffine(cutImg, reCut, r, box.size());
//			resize(reCut, reCut, Size(300, 80));
//		}
//		else reCut = cutImg;
//
//		int outName = lowerBound * 100 + i;
//		char buff[20];
//		_itoa_s(outName, buff, 10);
//		string oName = "../../Images_Data/Cut_Images/Blur/Test/NG/" + (string)buff + "_" + base_filename;
//		imwrite(oName, reCut);
//	}
//
//	return 1;
//}
//
//
//void run(){
//
//	vector<String> foName = { "../../Images_Data/Original_Images/Blur/Test/NG/*.jpg" };
//	for (int f = 0; f < foName.size(); ++f){
//		vector<String> fn;
//		glob(foName.at(f), fn, false);
//
//		//number of png files in images folder
//		size_t count = fn.size();
//		Mat src;
//		for (size_t t = 0; t<count; t++){
//			src = imread(fn[t]);
//			char * s = new char[fn[t].length() + 1];
//
//			strcpy(s, fn[t].c_str());
//
//			BlurCutML(s, t);
//
//		}
//	}
//}
//
//int main(int argc, char** argv)
//{
//	//char outputFile[] = "../blur_demo.csv";
//	//freopen(outputFile, "w", stdout);
//	run();
//}
