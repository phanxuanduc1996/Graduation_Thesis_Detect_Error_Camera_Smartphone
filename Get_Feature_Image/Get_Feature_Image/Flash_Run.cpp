//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include<string>
//
//using namespace cv;
//using namespace std;
//
//bool contain(string a){
//	int  m, n;
//	char x[] = "sau";
//	n = a.length();
//	m = strlen(x);
//	for (int i = 0; i < n - m; ++i){
//		if (a[i] == x[0] || a[i] == x[0] - 32){
//			for (int j = 0; j < m; j++){
//				if (a[i + j] != x[j] && a[i + j] != x[j] - 32){
//					break;
//				}
//				if (j == m - 1 && a[i + j + 1] == 2){
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}
//
//void run(){
//
//	freopen("../../Images_Data/Temp_Features/Flash_Train.csv", "w", stdout);
//	vector<String> foName = { "../../Images_Data/Original_Images/Flash/Train/NG/", "../../Images_Data/Original_Images/Flash/Train/OK/" };
//
//	for (int f = 0; f < foName.size(); ++f){
//		vector<String> fn;
//		glob(foName.at(f), fn, false);
//
//		//number of png files in images folder
//		size_t count = fn.size();
//		Mat src;
//		for (size_t t = 0; t < count; t++){
//			src = imread(fn[t]);
//
//			if (contain(fn[t])){ // neu la anh camSau2
//				Size size(4500, 3000);
//				resize(src, src, size);//resize image
//			}
//			if (src.rows > src.cols){
//				// rotate 90 degree
//				transpose(src, src);
//				flip(src, src, 1);
//			}
//
//			//Create a black image with the size as the image
//
//
//			Mat imgLines = Mat::zeros(src.size(), CV_8UC3);
//
//
//			// center
//			Point2f center(src.rows / 2, src.cols / 2);
//			// draw center
//			circle(imgLines, center, 5, Scalar(0, 0, 255), 10);
//
//			vector<Mat> mats;
//
//			double width = center.x * 650 / 1673;
//			// theo chieu kim dong ho + em o tam
//			int rect1[] = { 1000, 2750, 2750, 1000, 1900 };
//			int rect2[] = { 700, 700, 2037, 2037, 1400 };
//
//			for (int i = 0; i < 5; ++i){
//				Rect grid(rect1[i] * center.x / 1673, rect2[i] * center.y / 2265, width, width);
//				rectangle(imgLines, grid, Scalar(0, 0, 255), 10);
//				Mat dst = Mat(src, grid);
//				mats.push_back(dst);
//
//			}
//
//			// tinh tong mean cua 4 em xq
//			double sum = 0;
//			for (int i = 0; i < 5; ++i){
//				Mat mat_blue;
//				extractChannel(mats.at(i), mat_blue, 0);
//				//cout << mean(mat_blue)[0] << ",";
//				//sum += mean(mat_blue)[0];
//				//cout << mean(mat_blue)[0] << endl;
//
//				Mat tachNguongTuDong;
//				int nguong = threshold(mat_blue, tachNguongTuDong, 0, 255, THRESH_OTSU + THRESH_TOZERO);
//				double meanMoi = mean(tachNguongTuDong)[0] * (mat_blue.cols*mat_blue.rows)*1.0 / countNonZero(tachNguongTuDong);
//				cout << nguong << "," << meanMoi << ",";
//				//namedWindow("thres", CV_WINDOW_FREERATIO);
//				//imshow("thres", tachNguongTuDong); //show the original image
//
//				//Scalar mean = mean(mask_upstate);
//				//Scalar multiplier = float(mask.size) / cv2.countNonZero(mask)
//				//mean = tuple([multiplier * x for x in mean])
//
//				//Mat xe = tachNguongTuDong & mat_blue;
//				//threshold(mat_blue, tachNguongTuDong, 0, 255, THRESH_OTSU);
//				//namedWindow("xe", CV_WINDOW_FREERATIO);
//				//imshow("xe", xe); //show the original image
//				//waitKey(0);
//			}
//
//			//// in ra mean cua em tam
//			//Mat mat_blue;
//			//extractChannel(mats.at(4), mat_blue, 0);
//			//cout << mean(mat_blue)[0] << ",";
//			//// in ra hieu 
//			//cout << (mean(mat_blue)[0] - sum / 4.0) << ",";
//
//			src = src + imgLines;
//			//if (f == 0){
//			//	if (t == 21 || t == 32 || t == 40){
//			//		namedWindow("2", CV_WINDOW_FREERATIO);
//			//		imshow("2", src); //show the original image
//			//		waitKey(0);
//			//	}
//			//	
//			//}
//			//if (f == 1){
//			//	if ( t == (94-50)){
//			//		namedWindow("2", CV_WINDOW_FREERATIO);
//			//		imshow("2", src); //show the original image
//			//		waitKey(0);
//			//	}
//			//}
//			cout << f << "\n";
//		}
//	}
//}
//
//int main()
//{
//	run();
//}
