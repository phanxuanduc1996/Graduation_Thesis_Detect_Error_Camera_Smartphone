//#define _CRT_SECURE_NO_WARNINGS
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//using namespace cv;
//using namespace std;
//
//
//RNG rng(12345);
//int main()
//{
//	freopen("../../Images_Data/Temp_Features/Flare_Test.csv", "w", stdout);
//	string arr[] = { "../../Images_Data/Cut_Images/Flare/Test/NG/", "../../Images_Data/Cut_Images/Flare/Test/OK/" };
//
//	//freopen("../Flare_new2_Test.csv", "w", stdout);
//	//string arr[] = { "E:\\Data\\CNN_Ledon\\ledOn_Test\\NG\\*.jpg", "E:\\Data\\CNN_Ledon\\ledOn_Test\\OK\\*.jpg" };
//	//string arr[] = { "E:\\Data\\CNN_Ledon\\img_test\\NG\\*.jpg", "E:\\Data\\CNN_Ledon\\img_test\\OK\\*.jpg" };
//
//	for (int tt = 0; tt < 2; tt++){
//		vector<string> fn;
//		glob(arr[tt], fn, false);
//
//		for (string s : fn){
//			//cout<<s<<",";
//			Mat mat = imread(s);
//			Mat mat_gray, mat_hsv;
//			//lay kenh blue
//			extractChannel(mat, mat_gray, 0);
//			//cvtColor(mat, mat_gray, CV_RGB2GRAY);
//
//			cvtColor(mat, mat_hsv, CV_RGB2HSV);
//			//Mat1b mask2;
//			//inRange(mat_hsv, Scalar(0, 0, 190), Scalar(255, 51, 255), mask2);
//
//
//			// Initialize parameters
//			int histSize = 256;    // bin size
//			float range[] = { 0, 255 };
//			const float *ranges[] = { range };
//
//			// Calculate histogram
//			MatND hist;
//			calcHist(&mat_gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
//
//			// Show the calculated histogram in command window
//			double total;
//			total = mat_gray.rows * mat_gray.cols;
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
//			//	cout << varH << ",";
//
//			Mat mask1;
//			//threshold(mat_gray, mask1, (varH < 249) ? varH + 5 : 170, 255, THRESH_BINARY);
//			threshold(mat_gray, mask1, 170, 255, THRESH_BINARY);
//			/*	namedWindow("threshold", CV_WINDOW_FREERATIO);
//				imshow("threshold", mask1);*/
//
//
//			Mat1b mask;
//
//			blur(mat_gray, mat_gray, Size(3, 3), Point(-1, -1));
//
//			adaptiveThreshold(mat_gray, mask, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, -2);
//
//			/*	namedWindow("mask", CV_WINDOW_FREERATIO);
//				imshow("mask", mask);*/
//
//
//			dilate(mask, mask, getStructuringElement(MORPH_DILATE, Size(5, 5)), Point(-1, -1), 2);
//			erode(mask, mask, getStructuringElement(MORPH_ERODE, Size(3, 3)), Point(-1, -1), 2);
//
//			Mat newMask = mask & mask1;
//
//			//namedWindow("mask_lamdep", CV_WINDOW_FREERATIO);
//			//imshow("mask_lamdep", mask);
//
//
//			//namedWindow("new mask", CV_WINDOW_FREERATIO);
//			//imshow("new mask", newMask);
//			vector<vector<Point> > contours;
//			vector<Vec4i> hierarchy;
//			findContours(newMask, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//			/// Ve contour lon nhat
//			Mat drawing = Mat::zeros(newMask.size(), CV_8UC3);
//			double mx = 0.0;
//			int index = -1;
//
//			//Tim contour co dien tich lon nhat
//			for (int i = 0; i < contours.size(); i++)
//			{
//				// cout << contourArea(contours[i]) << endl;
//				double area = contourArea(contours[i]);
//				if (area > mx){
//					mx = area;
//					index = i;
//				}
//			}
//
//			if (index != -1){
//				//Ve contour
//				Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
//				drawContours(drawing, contours, index, color, 2, 8, hierarchy, 0, Point());
//
//				//Trich xuat dac trung cho contour index
//
//				//1. Dien tich contour 
//				double scale = 1.0*contourArea(contours[index]);
//				//double scale = 1.0*contourArea(contours[index]);
//				cout << scale << ",";
//
//
//				//3. Tim Hu moments
//				Moments mm = moments(contours[index]);
//				double hu[7];
//				HuMoments(mm, hu);
//				for (int i = 0; i < 7; i++){
//					cout << hu[i] << ",";
//				}
//
//				//9. Dien tich hinh chu nhat nho nhat
//				RotatedRect rectM = minAreaRect(contours[index]);
//				double minA, wM, hM, shortM, longM;
//				wM = rectM.size.width;
//				hM = rectM.size.height;
//				shortM = (wM > hM) ? hM : wM;
//				longM = (wM < hM) ? hM : wM;
//				/*	double tmp = 1.0*longM / shortM;
//					double eccentricity = sqrt(1 - tmp*tmp);
//
//					cout << 1.0*minA << "," << tmp << "," << eccentricity <<",";*/
//
//				cout << shortM << "," << longM << ",";
//			}
//
//			Mat mask3;
//			threshold(mat_gray, mask3, 252, 255, THRESH_BINARY);
//			vector<vector<Point> > contours2;
//			vector<Vec4i> hierarchy2;
//			findContours(mask3, contours2, hierarchy2, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
//
//			/// Ve contour lon nhat
//			Mat drawing2 = Mat::zeros(mask3.size(), CV_8UC3);
//			double mx2 = 0.0;
//			int index2 = -1;
//
//			//Tim contour co dien tich lon nhat
//			for (int i = 0; i < contours2.size(); i++)
//			{
//				// cout << contourArea(contours[i]) << endl;
//				double area = contourArea(contours2[i]);
//				if (area > mx2){
//					mx2 = area;
//					index2 = i;
//				}
//			}
//
//			Scalar color = Scalar(0, 255, 0);
//			drawContours(drawing2, contours2, index2, color, 2, 8, hierarchy2, 0, Point());
//
//			//namedWindow("src", CV_WINDOW_FREERATIO);
//			//imshow("src", mat);
//			//namedWindow("draw", CV_WINDOW_FREERATIO);
//			//imshow("draw", drawing);
//			//namedWindow("draw2", CV_WINDOW_FREERATIO);
//			//imshow("draw2", drawing2);
//			//waitKey(0);
//
//			RotatedRect rectM2 = minAreaRect(contours2[index2]);
//			double minA2, wM2, hM2, shortM2, longM2;
//			wM2 = rectM2.size.width;
//			hM2 = rectM2.size.height;
//			shortM2 = (wM2 > hM2) ? hM2 : wM2;
//			longM2 = (wM2 < hM2) ? hM2 : wM2;
//			minA2 = 1.0*wM2*hM2;
//
//			cout << 1.0*contourArea(contours2[index2]) << "," << shortM2 << "," << longM2 << ",";
//
//			//3. Tim Hu moments
//			Moments mm2 = moments(contours2[index2]);
//			double hu2[7];
//			HuMoments(mm2, hu2);
//			for (int i = 0; i < 7; i++){
//				cout << hu2[i] << ",";
//			}
//			cout << tt;
//			cout << "\n";
//		}
//	}
//}