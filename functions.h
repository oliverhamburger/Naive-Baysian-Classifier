// Author: Angelo Williams

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846


/*
* Parameters:
	float data[]: the array of floats to find the mean of
	int num: the amount of floats in data[]
* Return: float, the mean of data[]
*/
float mean(float data[], int num);

/*
* Parameters:
	float data[]: the array of floats to find the standard deviation of
	int num: the amount of floats in data[]
* Return: float, the standard deviation of data[]
*/
float calculateSD(float data[], int num);

/*
* Parameters:
	float a, float b, float c: floats to be compared
* Return: returns 1 if a is the largest, 2 if b, and 3 if c
*/
int compare(float a, float b, float c);

/*
* Parameters:
	float dataToTestAgainst[][4]: Data set for the data point to be compared against
	float dataToTakePointFrom[][4]: Data set from which the data point will be taken
	int sizeData: the amount of samples for the class being used
	int indexOfDataP: the index of the data point being tested
	int attributeIndex: the current attribute being tested
	bool dataPointInTestSet: pass true if the data point is within the data set being tested
* Return: float, probability of the data point having the attribute passed
*/
float PtoX(float dataToTestAgainst[][4], float dataToTakePointFrom[][4],
	int sizeData, int indexOfDataP, int attributeIndex, bool dataPointInTestSet);

/*
* Parameters:
	float dataToTestAgainst[][4]: Data set for the data point to be compared against
	float dataToTakePointFrom[][4]: Data set from which the data point will be taken
	int sizeData: the amount of samples for the class being used
	int indexOfDataP: the index of the data point being tested
	bool dataPointInTestSet: pass true if the data point is within the data set being tested
* Return: float, probability of the data point being in the comparison data set / class
*/
float getClassProb(float dataToTestAgainst[][4], float dataToTakePointFrom[][4],
	int sizeData, int indexOfDataP, bool dataPointInTestSet);

/*
* Parameters:
	float dataToTestAgainst[][4]: Data set for the data point to be compared against
	int indexOfDataP: the index of the data point being tested
	float setosaData[][4]: the data set for setosa samples
	float versicolorData[][4]: the data set for versicolor samples
	float virginicaData[][4]: the data set for virginica samples
	int setosaCount: amount of setosa samples
	int versicolorCount: amount of versicolor samples
	int virginicaCount: amount of virginica samples
	int totalCount: total amount of ssamples
	int setFlag: 1 if the data point is a setosa, 2 if versicolor, 3 if virginica
* Return: int, 1 if it is most likely that the sample is a Setosa, 2 if Versicolor, 3 if Virginica
*/
int totalProb(float dataToTakePointFrom[][4], int indexOfDataP,
	float setosaData[][4], float versicolorData[][4], float virginicaData[][4],
	int setosaCount, int versicolorCount, int virginicaCount, int totalCount, int setFlag);

/*
* Parameters:
	FILE *infile: a pointer to the file containing the data set
	float setosaData[][4]: a multidimensional array that will contain the Setosa data
	float versicolorData[][4]: a multidimensional array that will contain the Versicolor data
	float virginicaData[][4]: a multidimensional array that will contain the Virginica data
* Return: void
*/
void getDataFromFile(FILE *infile, float setosaData[][4], float versicolorData[][4], float virginicaData[][4]);



#endif