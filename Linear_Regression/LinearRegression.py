from __future__ import print_function
import numpy as np
from sklearn import datasets, linear_model
from sklearn.model_selection import train_test_split
import dataPre as dataPre

linkF = 'D:/DATA/CODE/GraduationProject/Features_Data/'
case = 'blur'
dirTrain = linkF
dirTest = linkF
dataPre.loadDataTrain(dirTrain, case)
dataPre.loadDataTest(dirTest, case)
matTrain, matVal, labelTrain, labelVal = train_test_split(dataPre.matTrain, dataPre.labelTrain, test_size = 0.2, random_state=1)
dataPre.FindMaxMin(matTrain)
dataPre.StandardData(matTrain)
dataPre.StandardData(matVal)
dataPre.StandardData(dataPre.matTest)

# Building matTrainBar
one = np.ones((np.shape(matTrain)[0], 1))
matTrainBar = np.concatenate((one, matTrain), axis=1)

# Calculating weights of the fitting line
A = np.dot(matTrainBar.T, matTrainBar)
b = np.dot(matTrainBar.T, labelTrain)
w = np.dot(np.linalg.pinv(A), b)

# For Testing
one = np.ones((np.shape(dataPre.matTest)[0], 1))
matTestBar = np.concatenate((one, dataPre.matTest), axis=1)

# Calculating dataTest
resultTest = np.dot(matTestBar, w)
print(case.upper())
# Checking result
cntTest = np.shape(resultTest)[0]
checkTrue = 0
checkFalse = 0
for i in range(cntTest):
    if resultTest[i] > 0.5 and dataPre.labelTest[i] == 1:
        checkTrue += 1
    elif resultTest[i] < 0.5 and dataPre.labelTest[i] == 0:
        checkTrue += 1
    else:
        checkFalse += 1
	
accur = 100*checkTrue/(checkTrue+checkFalse)
print("Accuracy: %.2f %%" %(accur))
# print(w)
# print(resultTest)
# ===== SKLEARN ===========
# Fit the model by Linear Regression
regr = linear_model.LinearRegression(fit_intercept=False)
regr.fit(matTrainBar, labelTrain)

resultSklearn = np.dot(matTestBar, regr.coef_)
checkTrue = 0
checkFalse = 0

for i in range(cntTest):
    if resultSklearn[i] > 0.5 and dataPre.labelTest[i] == 1:
        checkTrue += 1
    elif resultSklearn[i] < 0.5 and dataPre.labelTest[i] == 0:
        checkTrue += 1
    else:
        checkFalse += 1

accur = 100*checkTrue/(checkTrue+checkFalse)
print("By SKLEARN...")
print("Accuracy: %.2f %%" %(accur))
