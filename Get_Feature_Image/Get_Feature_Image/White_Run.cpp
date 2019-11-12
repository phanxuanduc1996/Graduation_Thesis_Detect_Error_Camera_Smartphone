#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "iostream"
#include "algorithm"

using namespace cv;
using namespace std;
vector<Mat> ChiaKhoi(Mat src, int width, int height, int WX, int HY){

	vector<Mat> mCells;

	//CHIA ANH THANH n KHOI
	//cout << width << " " << height << endl;
	for (int x = 0; x < width; x += WX) {
		for (int y = 0; y < height; y += HY) {
			//int k = x*y + x;
			int x1 = WX;
			int y1 = HY;
			if (2 * x1 + x > width) x1 = width - x;
			if (2 * y1 + y > height) y1 = height - y;
			Rect grid_rect(x, y, x1, y1);
			//  cout << grid_rect << endl;
			mCells.push_back(Mat(src, grid_rect));

			//		rectangle(src, grid_rect, Scalar(0, 255, 0), 5);
			//		namedWindow("name", CV_WINDOW_FREERATIO);
			//		imshow("name", src);
			//		imshow(format("grid%d", k), src(grid_rect));
			if (2 * HY + y > height) break;
			//		waitKey();
		}
		if (2 * WX + x > width) break;
	}
	return mCells;
}
int main(){
	// Read Image and Save Features to File.
	vector<string> fn;
	freopen("../../Images_Data/Temp_Features/White_Train.csv", "w", stdout);
	string paths[] = { "../../Images_Data/Original_Images/White/Train/NG/", "../../Images_Data/Original_Images/White/Train/OK/" };

	for (int h = 0; h < 2; h++){
		string path = paths[h];
		glob(path, fn, false);

		for (string s : fn){
			Mat src = imread(s);
			vector<Mat> mCells;

			//////CHIA ANH THANH 9 KHOI
			int width = src.cols;
			int height = src.rows;
			mCells = ChiaKhoi(src, width, height, width / 3, height / 3);

			//TIM TRUNG BINH CUA BA KENH B, G, R TRONG MOI KHOI     
			for (Mat mat : mCells){
				//cout<<mean(mat)<<endl;
				Scalar sc = mean(mat);
				cout << sc[0] << "," << sc[1] << "," << sc[2] << ",";

			}
			//cout <<endl;

			//LAM NOI ANH, SAU DO TIM CONTOURS (XAC DINH DOM DEN)
			Mat src_gray, dst;
			cvtColor(src, src_gray, CV_BGR2GRAY);
			blur(src_gray, src_gray, Size(3, 3));

			//Lam noi dom

			adaptiveThreshold(src_gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 199, 13);

			//Tim contours
			Mat canny_output;
			int thresh = 100;
			//Canny(dst, canny_output, thresh, thresh * 2, 3);
			vector<vector<Point>> contours;
			vector<Vec4i> hierarchy;
			findContours(dst, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
			double maxA = 0;
			for (int i = 0; i < contours.size(); i++){
				double tmp = contourArea(contours[i]);
				if (tmp > 400){
					if (maxA < tmp) maxA = tmp;
				}
			}
			cout << maxA << ",";


			/////Lam noi dom trang
			//threshold(src_gray, src_gray, 191, 255, THRESH_BINARY_INV);
			//adaptiveThreshold(src_gray, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 199, 13);

			////SHOW 
			//namedWindow("root", CV_WINDOW_FREERATIO);
			//imshow("root", src);
			//namedWindow("processed", CV_WINDOW_FREERATIO);
			//imshow("processed", dst);
			//waitKey();

			// Chia thanh cac blocks, moi block lay trung binh block, 4 diem co gia cao nhat, 4 diem co gia tri thap nhat
			vector<Mat> khois;
			khois = ChiaKhoi(src_gray, src.cols, src.rows, width / 7, height / 7);

			for (Mat mat : khois){
				cout << mean(mat)[0] << ",";
				int n = mat.cols*mat.rows, index = 0;
				vector<double>arrs;
				for (int i = 0; i < mat.rows; i++){
					for (int j = 0; j < mat.cols; j++){
						//arrs[index++] = mat.at<double>(i,j);
						arrs.push_back(mat.at<uchar>(i, j) - '0');
					}
				}
				sort(arrs.begin(), arrs.begin() + arrs.size());
				for (int i = 0; i < 4; i++){
					cout << arrs[i] << ",";
				}
				for (int i = arrs.size() - 1; i >= arrs.size() - 4; i--){
					cout << arrs[i] << ",";
				}
			}
			cout << h;
			cout << "\n";

		}
	}
	return 0;
}