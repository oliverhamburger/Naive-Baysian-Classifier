#include "functions.h"

// Author: Tom Kang, Oliver Hamburger
float mean(float data[], int num) {
	float sumData, mean;

	for (int i = 0; i<num; ++i) {
		sumData += data[i];
	}

	mean = sumData / num;

	return mean;
}


// Author: Tom Kang, Oliver Hamburger
float calculateSD(float data[], int num) {
	float meanData, standardDeviation = 0.0;
	int i;

	meanData = mean(data, num);

	for (i = 0; i<num; ++i) {
		standardDeviation += pow(data[i] - meanData, 2);
	}

	return sqrt(standardDeviation / num);
}


// Author: Tom Kang, Angelo Williams
int compare(float a, float b, float c) {
	int result;

	if (a > b && a > c)
		result = 1;
	else if (b > a && b > c)
		result = 2;
	else if (c > a && c > b)
		result = 3;
	else {
		printf("\nERROR in compare() function:\na = %f\nb = %f\nc = %f\n\n", a, b, c);
	}

	return result;
}


// Author: Oliver Hamburger
float PtoX(float dataToTestAgainst[][4], float dataToTakePointFrom[][4],
				int sizeData, int indexOfDataP, int attributeIndex,
				bool dataPointInTestSet) {
	// Create temp array to hold all values for a certain dataset and 
	//	 certain attribute except the value currently being tested
	int sizeTemp = sizeData - 1;
	float temp[sizeTemp];
	
	// Populate temp array
	int tempCounter = 0;
	for (int i = 0; i < sizeData; i++) {
		if (dataPointInTestSet && i == indexOfDataP)
			continue;
		else {
			temp[tempCounter] = dataToTestAgainst[i][attributeIndex];
			++tempCounter;
		}
	}

	float end, first, second;

	// Calculate mean and SD
	float dataMean = mean(temp, sizeTemp);
	float SD = calculateSD(temp, sizeTemp);

	// Calculate PofX
	float SDsquared = pow(SD, 2);
	float top = pow((dataToTakePointFrom[indexOfDataP][attributeIndex] - dataMean), 2);

	first = 1 / (sqrt(2 * M_PI * SDsquared));
	second = exp(-top / (2 * SDsquared));
	end = first * second;

	return end;
}


// Author: Tom Kang
float getClassProb(float dataToTestAgainst[][4], float dataToTakePointFrom[][4],
						int sizeData, int indexOfDataP, bool dataPointInTestSet) {
	float x1Prob, x2Prob, x3Prob, x4Prob;
	float classProb;

	// Calculate the probability that the data point has each attribute
	x1Prob = PtoX(dataToTestAgainst, dataToTakePointFrom, sizeData, indexOfDataP, 0, dataPointInTestSet);
	x2Prob = PtoX(dataToTestAgainst, dataToTakePointFrom, sizeData, indexOfDataP, 1, dataPointInTestSet);
	x3Prob = PtoX(dataToTestAgainst, dataToTakePointFrom, sizeData, indexOfDataP, 2, dataPointInTestSet);
	x4Prob = PtoX(dataToTestAgainst, dataToTakePointFrom, sizeData, indexOfDataP, 3, dataPointInTestSet);

	// Calculate the probability that the data point is in the class being tested against
	classProb = x1Prob * x2Prob * x3Prob * x4Prob;

	return classProb;
}


// Author: Tom Kang, Angelo Williams
int totalProb(float dataToTakePointFrom[][4], int indexOfDataP,
float setosaData[][4], float versicolorData[][4],
float virginicaData[][4], int setosaCount, int versicolorCount,
int virginicaCount, int totalCount, int setFlag) {
float setosaProb, versicolorProb, virginicaProb;
int result;

// Lower total count by one since the sample being tested is not being tested against
totalCount -= 1;
bool pointInSetosa, pointInVersicolor, pointInVirginica = false;

// Set the bool of the corresponding data set to true if the data point is in that set
// Lower the count for that set by one since a sample from that set is being tested
if (setFlag == 1) {
pointInSetosa = true;
setosaCount -= 1;
}
else if (setFlag == 2) {
pointInVersicolor = true;
versicolorCount -= 1;
}
else if (setFlag == 3) {
pointInVirginica = true;
virginicaCount -= 1;
}

// Calculate the probability that the data point is a setosa
setosaProb = getClassProb(setosaData, dataToTakePointFrom, setosaCount, indexOfDataP, pointInSetosa);
setosaProb *= ((float)setosaCount / (float)totalCount);

// Calculate the probability that the data point is a versicolor
versicolorProb = getClassProb(versicolorData, dataToTakePointFrom, versicolorCount, indexOfDataP, pointInVersicolor);
versicolorProb *= ((float)versicolorCount / (float)totalCount);

// Calculate the probability that the data point is a virginica
virginicaProb = getClassProb(virginicaData, dataToTakePointFrom, virginicaCount, indexOfDataP, pointInVirginica);
virginicaProb *= ((float)virginicaCount / (float)totalCount);

// Find the largest of these three probabilities
result = compare(setosaProb, versicolorProb, virginicaProb);

return result;
}

// Author: Angelo Williams
void getDataFromFile(FILE *infile, float setosaData[][4], float versicolorData[][4], float virginicaData[][4]) {
	rewind(infile);

	float x1;
	float x2;
	float x3;
	float x4;
	char name[50];

	int setosaCount = 0;
	int versicolorCount = 0;
	int virginicaCount = 0;

	int i = 0;
	// Scan through file and add data points to their respective data set
	// Increment the various counters as their data points are parsed
	while (!feof(infile)) {
		fscanf(infile, "%f,", &x1);
		fscanf(infile, "%f,", &x2);
		fscanf(infile, "%f,", &x3);
		fscanf(infile, "%f,", &x4);
		fscanf(infile, "%s\n", name);

		if (strcmp(name, "Iris-setosa") == 0) {
			setosaData[setosaCount][0] = x1;
			setosaData[setosaCount][1] = x2;
			setosaData[setosaCount][2] = x3;
			setosaData[setosaCount][3] = x4;
			++setosaCount;
		}
		else if (strcmp(name, "Iris-versicolor") == 0) {
			versicolorData[versicolorCount][0] = x1;
			versicolorData[versicolorCount][1] = x2;
			versicolorData[versicolorCount][2] = x3;
			versicolorData[versicolorCount][3] = x4;
			++versicolorCount;
		}
		else if (strcmp(name, "Iris-virginica") == 0) {
			virginicaData[virginicaCount][0] = x1;
			virginicaData[virginicaCount][1] = x2;
			virginicaData[virginicaCount][2] = x3;
			virginicaData[virginicaCount][3] = x4;
			++virginicaCount;
		}
		else {
			printf("Unknown category found: %s\nTerminating...", name);
			exit(0);
		}
		i++;
	}
}