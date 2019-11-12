//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include<string>
//
//using namespace cv;
//using namespace std;
//
//int cutFlareML(const char* imgName, int index) {
//	int imgSize = 150;
//	string fileName = imgName;
//	std::string base_filename = fileName.substr(fileName.find_last_of("/\\") + 1);
//	bool _debug = false;
//	Mat rawImg_ = imread(imgName, CV_LOAD_IMAGE_COLOR), src, rawImg;
//
//	if (rawImg_.rows == 0) return -1;//error read image
//	if (rawImg_.rows > rawImg_.cols) {
//		resize(rawImg_, rawImg, cv::Size(1500, 2000));
//	}
//	else resize(rawImg_, rawImg, Size(2000, 1500));//fix cố định kích thước resize để xử lý
//
//	if (_debug) {
//		namedWindow("rawImg", CV_WINDOW_KEEPRATIO);
//		imshow("rawImg", rawImg);
//	}
//
//	Mat _thresh, grayImage;
//	cvtColor(rawImg, grayImage, CV_BGR2GRAY);
//
//	vector<Rect> retan;
//	//chia ảnh ra làm 4 phần
//	int addFix = 150;
//	retan.push_back(Rect(0, 0, rawImg.cols / 2, rawImg.rows / 2));
//	retan.push_back(Rect(rawImg.cols / 2, 0, rawImg.cols / 2, rawImg.rows / 2));
//	retan.push_back(Rect(0, rawImg.rows / 2, rawImg.cols / 2, rawImg.rows / 2));
//	retan.push_back(Rect(rawImg.cols / 2, rawImg.rows / 2, rawImg.cols / 2, rawImg.rows / 2));
//
//	//cắt ngưỡng để lấy điểm sáng nhất
//	threshold(grayImage, _thresh, 250, 255, CV_THRESH_BINARY);
//	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
//	erode(_thresh, _thresh, element, Point(-1, -1), 2);
//	dilate(_thresh, _thresh, element, Point(-1, -1), 1);
//
//	int sumLines = 0;
//	// xử lý từng vùng ảnh trong 4 vùng nếu có flare thì cho next luôn
//	for (int i = 0; i < 4; i++) {
//		//cắt ngưỡng của điểm sáng nhất để tìm biên của đường tròn
//		Mat cutImageBinary = _thresh(retan[i]);
//		Mat cutImageBlue = rawImg(retan[i]);
//		if (_debug) {
//			imshow("cutImageBlue", cutImageBlue);
//		}
//		vector<vector<Point>> contours_;
//		sumLines = 0;
//		Rect rectBoudingCircle;
//		//tìm biên đường tròn
//		findContours(cutImageBinary, contours_, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//		if (contours_.size() == 0) {
//			continue;
//		}
//		//tìm biên lớn nhất
//		double area, areaThresh = 0;
//		int indexOfMax = 0;
//		Moments mu;
//		Point2f massCenter;
//		int disBoder = 150;
//
//		for (int j = 0; j < contours_.size(); j++) {
//			area = contourArea(contours_[j]);
//			if (area > areaThresh) {
//				mu = moments(contours_[j], false);
//				massCenter = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
//				if (massCenter.x < disBoder || massCenter.y < disBoder || massCenter.x > cutImageBinary.cols - disBoder || massCenter.y > cutImageBinary.rows - disBoder)
//					continue;
//
//				areaThresh = area;
//				indexOfMax = j;
//			}
//		}
//		rectBoudingCircle = boundingRect(contours_[indexOfMax]);
//		mu = moments(contours_[indexOfMax], false);
//		massCenter = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);
//		Mat tmp1;
//		try {
//			tmp1 = cutImageBlue(Rect(massCenter.x - imgSize, massCenter.y - imgSize, imgSize * 2, imgSize * 2)); //cam_truoc
//		}
//		catch (Exception e) {
//			continue;
//		}
//		int outName = index * 10 + i;
//		char buff[20];
//		_itoa_s(outName, buff, 10);
//		string oName = "../../Images_Data/Cut_Images/Flare/Test/OK/" + (string)buff + base_filename;
//		imwrite(oName, tmp1);
//		if (_debug) {
//			imshow("tmp1", tmp1);
//			waitKey(0);
//		}
//
//	}
//	return 0;
//}
//
//void run(){
//
//	vector<String> foName = { "../../Images_Data/Original_Images/Flare/Test/OK/*.jpg" };
//	for (int f = 0; f < foName.size(); ++f){
//		vector<String> fn;
//		glob(foName.at(f), fn, false);
//
//		//number of png files in images folder
//		size_t count = fn.size();
//		Mat src;
//		for (size_t t = 0; t < count; t++){
//			src = imread(fn[t]);
//			char * s = new char[fn[t].length() + 1];
//
//			strcpy(s, fn[t].c_str());
//
//			cutFlareML(s, t);
//		}
//	}
//}
//int main(){
//	run();
//	return 0;
//}