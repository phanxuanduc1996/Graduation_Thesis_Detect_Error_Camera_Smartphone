import scipy.io as sio
import numpy as np
from sklearn.svm import SVC
from sklearn.metrics import accuracy_score
import dataPre as dataPre
import warnings
import math
from sklearn.utils.extmath import safe_sparse_dot
from sklearn.model_selection import train_test_split
warnings.filterwarnings("ignore", category=FutureWarning)

linkF = 'D:/DATA/CODE/GraduationProject/Features_Data/'
# Link temp: D:/DATA/CODE/GraduationProject/Images_Data/Temp_Features/
case = 'flash'
dirTrain = linkF
dirTest = linkF
dataPre.loadDataTrain(dirTrain, case)
dataPre.loadDataTest(dirTest, case)
matTr, matVal, labelTr, labelVal = train_test_split(dataPre.matTrain, dataPre.labelTrain, test_size = 0.01, random_state=1)

#   BLUR
# clf = SVC(kernel='rbf', gamma=0.50625, C=62.5)
#   FLARE
# clf = SVC(kernel='rbf', gamma=0.50625, C=0.5)
#   FLASH
# clf = SVC(kernel='rbf', gamma=0.50625, C=0.5)
#   WHITE
clf = SVC(kernel='rbf', gamma=0.50625, C=0.5)
# C = 195, 200, 201

dataPre.FindMaxMin(matTr)
dataPre.StandardData(matTr)
dataPre.StandardData(matVal)
dataPre.StandardData(dataPre.matTest)
clf.fit(matTr, labelTr)
print(case.upper())
y_val = clf.predict(matVal)
print("Accuracy: %.2f %%" % (100*accuracy_score(labelVal, y_val)))
y_pred = clf.predict(dataPre.matTest)
print("Accuracy: %.2f %%" % (100*accuracy_score(dataPre.labelTest, y_pred)))
