#include "functions.h"

// Author: Oliver Hamburger, Tom Kang, Angelo Williams
int main(){
	FILE *infile;
	infile = fopen("iris.data", "r");
	
	int setosaCount = 0;
	int versicolorCount = 0;
	int virginicaCount = 0;
	int totalCount = 0;
	
	float temp;
	char name[50];

	// Prepare the data file to be parsed
	while (!feof(infile)) {
		fscanf(infile, "%f,", &temp);
		fscanf(infile, "%f,", &temp);
		fscanf(infile, "%f,", &temp);
		fscanf(infile, "%f,", &temp);
		fscanf(infile, "%s\n", name);

		if (strcmp(name, "Iris-setosa") == 0) {
			++setosaCount;
		}
		else if (strcmp(name, "Iris-versicolor") == 0) {
			++versicolorCount;
		}
		else if (strcmp(name, "Iris-virginica") == 0) {
			++virginicaCount;
		}
		else {
			printf("Unknown category found: %s\nTerminating...", name);
			exit(0);
		}

		++totalCount;
	}
	
	float setosaData[setosaCount][4];
	float versicolorData[versicolorCount][4];
	float virginicaData[virginicaCount][4];
	
	// Populate data sets with data points from data file
	getDataFromFile(infile, setosaData, versicolorData, virginicaData);

	// correctCount will be incremented by 1 every time a sample is correctly predicted
	int correctCount = 0;
	int currentResult;
	char resultMap[4][11] = { "", "Setosa", "Versicolor", "Virginica" };

	// Predict all Setosa samples
	for (int i = 0; i < setosaCount; ++i) {
		currentResult = totalProb(setosaData, i, setosaData,
			versicolorData, virginicaData, setosaCount,
			versicolorCount, virginicaCount, totalCount, 1);
		
		if (currentResult == 1)
			++correctCount;

		printf("Setosa #%i prediction: %s\n", i + 1, resultMap[currentResult]);
	}

	// Predict all Versicolor samples
	for (int i = 0; i < versicolorCount; ++i) {
		currentResult = totalProb(versicolorData, i, setosaData,
			versicolorData, virginicaData, setosaCount,
			versicolorCount, virginicaCount, totalCount, 2);

		if (currentResult == 2)
			++correctCount;

		printf("Versicolor #%i prediction: %s\n", i + 1, resultMap[currentResult]);
	}

	// Predict all Virginica samples
	for (int i = 0; i < virginicaCount; ++i) {
		currentResult = totalProb(virginicaData, i, setosaData,
			versicolorData, virginicaData, setosaCount ,
			versicolorCount, virginicaCount, totalCount, 3);

		if (currentResult == 3)
			++correctCount;

		printf("Virginica #%i prediction: %s\n", i + 1, resultMap[currentResult]);
	}
	
	float accuracyPercentage = ((float)correctCount / (float)totalCount) * 100;
	printf("\nAccuracy: %i/%i, %.2f%%\n", correctCount, totalCount, accuracyPercentage);

	return 0;
}