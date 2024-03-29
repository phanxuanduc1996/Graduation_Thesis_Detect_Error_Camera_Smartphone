import os
import numpy as np
import math

matTrain = []
labelTrain = []
matTest = []
labelTest = []
maxCols = []
minCols = []


def FindMaxMin(matrix):
    numRows = np.shape(matrix)[0]
    numCols = np.shape(matrix)[1]
    for col in range(numCols):
        maxTmp = float(-100000)
        minTmp = float(100000)
        for row in range(numRows):
            if matrix[row][col] > maxTmp:
                maxTmp = matrix[row][col]
            if matrix[row][col] < minTmp:
                minTmp = matrix[row][col]
        maxCols.append(maxTmp)
        minCols.append(minTmp)


def StandardData(matrix):
    numRows = np.shape(matrix)[0]
    numCols = np.shape(matrix)[1]
    for col in range(numCols):
        subTmp = maxCols[col] - minCols[col]
        for row in range(numRows):
            matrix[row][col] = (matrix[row][col] - minCols[col]) / subTmp
    return matrix


def LoadDataTrain(dir, case):
    allFile = os.listdir(dir)
    for fileTrain in allFile:
        fileTrain = fileTrain.lower()
        if fileTrain.startswith(case) and fileTrain.endswith("_training.csv"):
            with open(os.path.join(dir, fileTrain), "r") as fd:
                while True:
                    lineTrain = fd.readline()
                    if not lineTrain:
                        break
                    lineTrain = lineTrain.split(",")
                    numOfFeature = len(lineTrain)
                    lineTrain = np.array(lineTrain)
                    featTrain = []
                    for cnt in range(numOfFeature-1):
                        featTrain.append(float(lineTrain[cnt]))

                    if int(lineTrain[numOfFeature - 1]) == 0:
                        labelTrain.append(0)
                    else:
                        labelTrain.append(1)
                    matTrain.append(featTrain)
    FindMaxMin(matTrain)
    StandardData(matTrain)


def LoadDataTest(dir, case):
    allFile = os.listdir(dir)
    for fileTest in allFile:
        fileTest = fileTest.lower()
        if fileTest.startswith(case) and fileTest.endswith("_test.csv"):
            with open(os.path.join(dir, fileTest), "r") as fd:
                while True:
                    lineTest = fd.readline()
                    if not lineTest:
                        break
                    lineTest = lineTest.split(",")
                    numOfFeature = len(lineTest)
                    lineTest = np.array(lineTest)
                    featTest = []
                    for cnt in range(numOfFeature-1):
                        featTest.append(float(lineTest[cnt]))

                    if int(lineTest[numOfFeature - 1]) == 0:
                        labelTest.append(0)
                    else:
                        labelTest.append(1)
                    matTest.append(featTest)
    StandardData(matTest)
