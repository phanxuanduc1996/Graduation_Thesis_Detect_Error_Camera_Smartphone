import numpy as np
import dataPre as dataPre
from sklearn import linear_model
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split

linkF = 'D:/DATA/CODE/GraduationProject/Features_Data/'
case = 'white'
dirTrain = linkF
dirTest = linkF
dataPre.loadDataTrain(dirTrain, case)
print(np.shape(dataPre.matTrain))
dataPre.loadDataTest(dirTest, case)
matTrain, matVal, labelTrain, labelVal = train_test_split(
    dataPre.matTrain, dataPre.labelTrain, test_size=0.2, random_state=1)

dataPre.FindMaxMin(matTrain)
dataPre.StandardData(matTrain)
dataPre.StandardData(matVal)
dataPre.StandardData(dataPre.matTest)

# train
logreg = linear_model.LogisticRegression(
    C=100, solver='lbfgs', multi_class='multinomial')
# 100
logreg.fit(matTrain, labelTrain)
print(case.upper())
labelP_val = logreg.predict(matVal)
print("Accuracy: %.2f %%" % (100*accuracy_score(labelVal, labelP_val)))
label_pred = logreg.predict(dataPre.matTest)
print("Accuracy: %.2f %%" % (100*accuracy_score(dataPre.labelTest, label_pred)))
