import numpy as np
from sklearn import linear_model
from sklearn.metrics import accuracy_score
import dataPre as dataPre
import warnings
import math
from sklearn.utils.extmath import safe_sparse_dot
from sklearn.model_selection import train_test_split
warnings.filterwarnings("ignore", category=FutureWarning)

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

logreg = linear_model.RidgeClassifier(alpha=0.1)
# If num_Features = 9, set_up alpha = 70
# Elif num_Features = 11, set_up alpha = 33.
logreg.fit(matTrain, labelTrain)
print(case.upper())
labelVal_pred = logreg.predict(matVal)
print("Accuracy: %.2f %%" %(100*accuracy_score(labelVal, labelVal_pred)))
labelTest_pred = logreg.predict(dataPre.matTest)
print("Accuracy: %.2f %%" %(100*accuracy_score(dataPre.labelTest, labelTest_pred)))
