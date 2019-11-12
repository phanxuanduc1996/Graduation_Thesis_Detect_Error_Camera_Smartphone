# INFORMATION ABOUT THE DIRECTORY AND GUIDE TO RUNNING THE GRADUATION PROGRAM.

## Detection of camera errors through analysis of sample images by machine learning
Project for Samsung phone factory in Vietnam.<br />
The data for the thesis is confidential data of the factory, so I cannot publicize it.

- By: PHAN XUAN DUC
- MSSV: 20146212.
- Grade: CN-CNTT 01-K59.
- Subject: Computer Science.

## Projects performed on:

### Visual Studio 2013.
- Languages ​​used: ``C++``.
- Cut the area to extract the feature and perform image feature extraction of 4 cases.

### Visual Studio Code.
- Languages ​​used: ``Python``.
- Run a photo sorting program using different algorithms.

## Directory structure that contains DNN:

The ``Get_Feature_Image`` folder containing 2 Projects:
### Get_Feature_Image:
- Perform image cropping and extraction features of 4 cases in the Delta.
### Run_SVM:
- Performs running the SVM algorithm in C ++.

## Directory of classification models:
The ``dataPre.py`` file performs data normalization.

### CNN:
- Contains programs and photo data for the CNN model.
- In the case of Blur and Flare, there are two cases: running the program with a set of cropped image areas, such as SVM model, and the set of images is a scalable image of 180x240, similar to the two cases of Flash and White.
- In each directory of each case running CNN, for example CNN_Blur_80_300, the SAVE directory stores the trained model (Capacity of each model about 1.5 GB).

### Binary_Classification:
- Contains the program of Binary Regression algorithm.

### Linear_Regression:
- Contains the program of Linear Regression algorithm.

### Softmax_Regression:
- Contains program of Softmax Regression algorithm.

### Images_Data folder:
- Contains input image data.

### Original_Images:
- Contains the original image data of the problem.

### Cut_Images:
- Contains image data cropped out of specific extraction areas, including Blur and Flare.

### Resize_Images:
- Contains image data scaled to size 180x240, used in CNN model.
- In this folder contains programs that scale images into an input folder.

### Temp_Features:
- Saving the feature set is done for example, does not affect the original feature set when running related algorithms.

### Features_Data:
- The directory of the csv file set containing the extracted features.


## Instructions to run the program:

### Extract feature:
#### Install:
- OpenCV 2.4.13. (https://sourceforge.net/projects/opencvlibrary/files/opencv-win/2.4.13/opencv-2.4.13.exe/download)
- It is required to configure OpenCV into the corresponding Project using OpenCV in Visual Studio 2013.
- If you install a different version, you must edit the configuration.

#### Solution Platform:
- Win32.

#### Blur_Cut:
- Cut specific areas to extract in the Blur case.

#### Blur_Run:
- Perform extract specific to Blur case.

#### Flare_Cut:
- Cut out specific extracted areas in case of Flare.

#### Flare_Run:
- Perform extraction specific to the Flare case.

#### Flash_Run:
- Perform specific extraction for Flash case.

#### White_Run:
- Perform extraction specific to the White case.

#### Run_SVM:
- Run SVM algorithm model in Visual Studio in C ++ language.

#### The _Model.txt:
- File contains information about the model of the SVM algorithm for the training set being considered.

#### The Blur_Model.txt:
- Example stores information about the configuration of an SVM model with a Blur case. 

#### Information included
- The input parameters, super parameters, support vectors are obtained after training.


## Run the classification model:

### Installation:

#### [Python 3.6.6 64 bit](https://www.python.org/ftp/python/3.6.6/python-3.6.6-amd64.exe)
- Requires Visual Studio Code to install libraries such as Numpy, Tensorflow, Cv-python, ... (Libraries often used in Machine Learning)
- When running the algorithm program, move the Terminal to the directory containing the corresponding code file, otherwise the program will give an error.

### For files in the CNN directory:

#### ``dataset.py:``
- Perform training data settings.

#### ``predict.py:``
- Make a prediction of the output of test data (test sets).
#### ``train_cnn.py:``
- Perform model training and feature extraction.

As conditions allow, we only copy files that run the program.
If you need to learn about photo patterns in episodes to run problems and models of CNN models,
Please contact me by email: phanxuanduc1996@gmail.com.

Thank you.