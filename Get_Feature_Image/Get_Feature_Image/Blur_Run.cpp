//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include<string>
//
//using namespace cv;
//using namespace std;
//
//void run(){
//	freopen("../../Images_Data/Temp_Features/Blur_Train.csv", "w", stdout);
//	vector<String> foName = { "../../Images_Data/Cut_Images/Blur/Train/OK/", "../../Images_Data/Cut_Images/Blur/Train/NG/" };
//
//	//	freopen("../blur_new2_test.csv", "w", stdout);
//	//vector<String> foName = { "E:\\Data\\CNN\\img_test\\NG", "E:\\Data\\CNN\\img_test\\OK" };
//
//	for (int f = 0; f < foName.size(); ++f){
//		vector<String> fn;
//		glob(foName.at(f), fn, false);
//
//		//number of png files in images folder
//		size_t count = fn.size();
//		Mat src;
//		for (size_t i = 0; i < count; i++){
//			src = imread(fn[i]);
//			Mat src_gray;
//			cvtColor(src, src_gray, CV_RGB2GRAY);
//
//			Mat des, abs_dst;
//			int ddepth = CV_16S;
//			int kernel_size = 3;
//			Laplacian(src_gray, des, ddepth, kernel_size);
//			convertScaleAbs(des, abs_dst);
//
//			//Mat mymy;
//
//			//Mat kernel = Mat::ones(3, 3, CV_32F);
//			//kernel.at<float>(0, 0) = 0.0f;
//			//kernel.at<float>(0, 2) = 0.0f;
//			//kernel.at<float>(2, 0) = 0.0f;
//			//kernel.at<float>(2, 2) = 0.0f;
//			//kernel.at<float>(1, 1) = -4.0f;
//			//filter2D(src_gray, mymy, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
//
//			Scalar mean;
//			Scalar std;       // do lech chuan
//			meanStdDev(abs_dst, mean, std);
//			double kq = std[0] * std[0];
//			cout << kq << ",";
//
//			meanStdDev(src_gray, mean, std);
//			cout << mean[0] << ",";
//
//			// Initialize parameters
//			int histSize = 256;    // bin size
//			float range[] = { 0, 255 };
//			const float *ranges[] = { range };
//
//			// Calculate histogram
//			MatND hist;
//			calcHist(&src_gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
//
//			// Show the calculated histogram in command window
//			double total;
//			total = src_gray.rows * src_gray.cols;
//			int maxC = -1, varH = -1;
//			for (int h = 0; h < histSize; h++)
//			{
//				float binVal = hist.at<float>(h);
//				//cout << " " << binVal;
//				if (binVal > maxC){
//					maxC = binVal;
//					varH = h;
//				}
//			}
//			cout << varH << ",";
//
//			cout << f << endl;
//			//namedWindow("my", CV_WINDOW_FREERATIO);
//			//imshow("my", mymy );
//			//waitKey(0);
//
//		}
//	}
//}
//
//int main()
//{
//	run();
//}