# coding:utf-8

from numpy import *
import operator
from collections import Counter
import xlrd


# 导入特征数据
def file2matrix():
    workbook = xlrd.open_workbook(r'C:\Users\Administrator\Desktop\shuju.xls')
    # 改成自己的文件路径和文件名
    # print(workbook.sheet_names())
    sheet1 = workbook.sheet_by_index(0)  # 按excel的表格的顺序,从0开始
    # print(sheet1.name,sheet1.nrows,sheet1.ncols)#名字,行,列
    # returnMat =sheet1.row_values(0:6) 目标就是把140*6的矩阵整进去
    returnMat = []
    for i in range(sheet1.nrows - 10):
        returnMat = sheet1.row_values(i, 0, -1) + returnMat
    returnMat = array(returnMat).reshape(130, 5)
    # print(returnMat)
    classLabel = sheet1.col_values(5)
    # print(classLabel)
    return returnMat, classLabel  # 将文本中的数据导入到列表


# 归一化数据,保证特征等权重
def autoNorm(dataset):
    minVals = dataset.min(0)
    maxVals = dataset.max(0)
    ranges = maxVals - minVals
    normDataSet = zeros(shape(dataset))  # 建立与dataSet结构一样的矩阵
    # print(normDataSet)
    m = dataset.shape[0]
    for i in range(1, m):
            normDataSet[i, :] = (dataset[i, :] - minVals) / ranges
    return normDataSet, ranges, minVals


# KNN算法
def classify(input, dataSet, label, k):
    dataSize = dataSet.shape[0]
    # 计算欧式距离
    diff = tile(input, (dataSize, 1)) - dataSet
    sqdiff = diff ** 2
    squareDist = sum(sqdiff, axis=1)  # 行向量分别相加，从而得到新的一个行向量
    dist = squareDist ** 0.5

    # 对距离进行排序
    sortedDistIndex = dist.argsort()
    # argsort()根据元素的值从大到小对元素进行排序，返回下标

    classCount = {}
    for i in range(k):
        voteLabel = label[sortedDistIndex[i]]
        # 对选取的K个样本所属的类别个数进行统计
        classCount[voteLabel] = classCount.get(voteLabel, 0) + 1
    # 选取出现的类别次数最多的类别
    maxCount = 0
    for key, value in classCount.items():
        if value > maxCount:
            maxCount = value
            classes = key
    return classes


# 测试
def datingTest():
    testdata = xlrd.open_workbook(r'C:\Users\Administrator\Desktop\shuju.xls')
    # 改成自己的文件路径和文件名
    # print(testdata.sheet_names())
    sheet1 = testdata.sheet_by_index(0)  # 按excel的表格的顺序,从0开始
    # print(sheet1.name,sheet1.nrows,sheet1.ncols)#名字,行,列
    datingDataMat = []
    for i in range(100):
        datingDataMat = sheet1.row_values(i, 0, -1) + datingDataMat
    datingDataMat = array(datingDataMat).reshape(100, 5)
    print(datingDataMat)
    datingLabels = sheet1.col_values(5, 0, 100)
    print(datingLabels)
    normMat, ranges, minVals = autoNorm(datingDataMat)
    m = normMat.shape[0]
    testNum = 10
    # int(m * rate)
    errorCount = 0.0
    for i in range(100):  # testNum
        classifyResult = classify(normMat[i, :], normMat[0:m, :], datingLabels[0:m], 10)
        print("分类后的结果为:,", classifyResult)
        print("原结果为：", datingLabels[i])
        if (classifyResult != datingLabels[i]):
            errorCount += 1.0
    print("误分率为:", (errorCount / float(testNum)))


# 预测函数
def classifyPerson():
    resultList = ['0','1', '2', '3', '4', '5', '6', '7', '8', '9']
    DataMat, Labels = file2matrix()
    normMat, ranges, minVals = autoNorm(DataMat)
    inArr = array([6.401899671, 0.362470814, 3.133093082, 3, 1.441860465])  # Label 8
    classifierResult = int(classify((inArr - minVals) / ranges, normMat, Labels, 11))
    print("分类类别为", resultList[classifierResult - 1])


classifyPerson()
datingTest()
