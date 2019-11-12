#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ml/ml.hpp"
#include<fstream>
#include<time.h>
using namespace cv;
using namespace std;

string type = "Flash";
string trainingFile =  "../" + type +"_Train.csv";
string testFile= "../"+ type +"_Test.csv";
string modelFile= "../"+ type +"_Model.txt";
string stdFile = "../" + type + "_Std.csv";

vector< vector<float> > loadMaxMinData();
void test()
{
	ifstream ifs_test (testFile);

	string current_line;
	vector< vector<float> > test_data;
	  
	if(ifs_test.is_open()){
		// Start reading lines as long as there are lines in the file
		while(getline(ifs_test, current_line)){
			//	 Now inside each line we need to seperate the cols
			vector<float> values;
			std::stringstream temp(current_line);
			string single_value;
			while(getline(temp,single_value,',')){
				// convert the string element to a float value
				values.push_back(atof(single_value.c_str()));
			}
			// add the row to the complete data vector
			test_data.push_back(values);
		}
		ifs_test.close();
	}else cout << "Unable to open file..."; 

	// Train the SVM
	CvSVM SVM;

	char * s = new char[modelFile.length()+1];
	strcpy(s,modelFile.c_str());
	SVM.load(s);
	
	vector<int> result ;
	vector<vector<float>> v = loadMaxMinData();

	for (size_t i=0; i < (int) test_data.size(); i++){
		vector<float> values = test_data[i];
		Mat exampleMat = Mat::zeros(1, (int)values.size() - 1 , CV_32FC1);

		for(int cols = 0; cols < values.size() - 1; cols++){
			exampleMat.at<float>(0, cols) = values[cols];
			
			float maxTmp, minTmp;
			maxTmp = v[cols][0];
			minTmp = v[cols][1];
			float subTmp = maxTmp - minTmp;
			exampleMat.at<float>(0, cols) = (exampleMat.at<float>(0, cols) - minTmp*1.0) / subTmp*1.0;
	
		}

		float response = SVM.predict(exampleMat);

		if(response == 1){
			result.push_back(1);

		} else if(response == 0){
			result.push_back(0);
		}
	}

	int match = 0;
	int confusionMatrix [2][2] = {0};
	float normalizedConfusionMatrix[2][2] = {0};
	for(int i = 0; i < test_data.size(); ++i){
		int predict = result.at(i), goal = test_data[i][test_data[0].size() - 1];
		confusionMatrix[goal][predict]++;
		if(predict ==  goal){
			match++;
		} else{
			cout << "Not match = " << i <<" Predict = "<< predict << "  Goal = " << goal << endl;
		}
	}

	for(int i = 0; i < 2; ++i){
		int sum = 0;
		for(int k = 0; k < 2; k++){
			sum += confusionMatrix[i][k];
		}
		for(int j = 0; j < 2; ++j){
			if(sum != 0){
				normalizedConfusionMatrix[i][j] = (confusionMatrix[i][j]*1.0/sum);
			} else{
				normalizedConfusionMatrix[i][j] = -1;
			}
		}
	}


	cout << "---------------------------------------------" <<endl;
	float accurance = (match *1.0/ test_data.size())*100;
	std::cout <<"ACCURANCE = "<< match<<"/"<<test_data.size() <<" (";
	printf("%.2f%%)\n", accurance);


	cout << "********"<< endl;
	cout << "CONFUSION MATRIX (cot = predict)" << endl;
	for(int i = 0; i < 2; ++i){
		for(int j = 0; j < 2; ++j){
			cout << confusionMatrix[i][j]  << " (";
			printf("%.4f) ", normalizedConfusionMatrix[i][j]  );
		}
		cout << endl;
	}	
	cout << "********"<< endl;
	cout << "Precision = " << confusionMatrix[0][0]*1.0/(confusionMatrix[0][0] + confusionMatrix[1][0]) << endl;
	cout << "Recall = " << confusionMatrix[0][0]*1.0/(confusionMatrix[0][0] + confusionMatrix[0][1]) << endl;

}

void findMaxMin(Mat a){
	ofstream outfile;
	outfile.open(stdFile, ios::out);

	int cols = a.cols;
	int rows = a.rows;
	for (int i = 0; i < cols; ++i){
		float maxTmp = -1000000.0;
		float minTmp = 1000000.0;
		for (int j = 0; j < rows; ++j){
			float x = a.at<float>(j, i);
			if (x > maxTmp){
				maxTmp = a.at<float>(j, i);
			} 
			if (x < minTmp){
				minTmp = a.at<float>(j, i);
			}
		}
		outfile << maxTmp <<","<< minTmp << "\n";

	}
	outfile.close();
}

vector< vector<float> > loadMaxMinData(){

	ifstream ifs_test(stdFile);

	string current_line;
	vector< vector<float> > mm_data;

	if (ifs_test.is_open()){
		// Start reading lines as long as there are lines in the file
		while (getline(ifs_test, current_line)){
			//	 Now inside each line we need to seperate the cols
			vector<float> values;
			std::stringstream temp(current_line);
			string single_value;
			while (getline(temp, single_value, ',')){
				// convert the string element to a float value
				values.push_back(atof(single_value.c_str()));
			}
			// add the row to the complete data vector
			mm_data.push_back(values);
		}
		ifs_test.close();
	}
	else cout << "Unable to open file";


	return mm_data;
	
	
}

void changeData(Mat a){
	vector<vector<float>> v = loadMaxMinData();
	int cols = a.cols;
	int rows = a.rows;
	for (int i = 0; i < cols; ++i){
		float maxTmp, minTmp;
		maxTmp = v[i][0];
		minTmp = v[i][1];
		float subTmp = maxTmp - minTmp;
		for (int j = 0; j < rows; ++j){
			a.at<float>(j, i) = (a.at<float>(j, i) - minTmp*1.0) / subTmp*1.0;
		}
	}
}

int main()
{
	ifstream ifs_train (trainingFile);

	string current_line;
	vector< vector<float> > train_data;

	if(ifs_train.is_open()){
		// Start reading lines as long as there are lines in the file
		while(getline(ifs_train, current_line)){
			// Now inside each line we need to seperate the cols
			vector<float> values;
			std::stringstream temp(current_line);
			string single_value;
			while(getline(temp,single_value,',')){
				// convert the string element to a float value
				values.push_back(atof(single_value.c_str()));
			}
			// add the row to the complete data vector
			train_data.push_back(values);
		}

		ifs_train.close();
	}else cout << "Unable to open file"; 

	// Now add all the data into a Mat element
	Mat trainingDataMat = Mat::zeros((int)train_data.size() , (int)train_data[0].size() - 1, CV_32FC1);
	Mat labelsMat = Mat::zeros((int)train_data.size() , 1, CV_32SC1);
	// Loop over vectors and add the data
	for(int rows = 0; rows < (int)train_data.size() ; rows++){
		for(int cols= 0; cols< (int)train_data[0].size() - 1; cols++){
			trainingDataMat.at<float>(rows,cols) = train_data[rows][cols];
		}
		labelsMat.at<int>(rows,0) = (int)train_data[rows][train_data[0].size() - 1];
	}
	findMaxMin(trainingDataMat);
	changeData(trainingDataMat);

	ParamGrid nogrid = ParamGrid(0, 0, 0);
	// Set up SVM's parameters
	CvSVMParams params;
	params.svm_type    = 	CvSVM::C_SVC ;
	params.kernel_type = CvSVM::POLY;
	params.degree = 3;
	//params.termCriteria(TermCriteria(TermCriteria::MAX_ITER, 100000, 1e-6));
//	params.gamma = 500;
//	params.C = 100;
	// Train the SVM
	CvSVM SVM;

	SVM.train_auto(trainingDataMat, labelsMat, Mat(), Mat(), params,10);
	CvSVMParams newParams = SVM.get_params();
	cout << endl;
	cout << "KERNEL   : " << newParams.kernel_type << endl;
	cout << "SVM TYPE : " << newParams.svm_type << endl;
	cout << "Degree   : " << newParams.degree << endl;
	cout << "Gamma    : " << newParams.gamma << endl;
	cout << "Coef0    : " << newParams.coef0 << endl;
	cout << "Cvalue   : " << newParams.C << endl;
	cout << "p        : " << newParams.p << endl;
	char * s = new char[modelFile.length()+1];

	strcpy(s,modelFile.c_str());
	SVM.save(s);
	clock_t start = clock();
	test();
	clock_t finish = clock();
	double duration = (double)(finish - start);
	cout <<"\n\n\n";
	printf("Thoi gian thuc thi: %lf ms\n", duration);
	getchar();
}