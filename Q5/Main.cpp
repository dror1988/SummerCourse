#include "Converter.h"

char* Convert2Float(bool neg, char *i, char *f, bool double_percision);


void main(){
	char *res;

	res = Convert2Float(false, "13", "5", false);
	printf("%s\n", res);
	free(res);

	res = Convert2Float(true, "43", "75", false);
	printf("%s\n", res);
	free(res);

	res = Convert2Float(false, "0", "66", true);
	printf("%s\n", res);
	free(res);

	res = Convert2Float(true, "11", "25", true);
	printf("%s\n", res);
	free(res);

	res = Convert2Float(true, "0", "0", true);
	printf("%s\n", res);
	free(res);

	res = Convert2Float(true, "1", "0", true);
	printf("%s\n", res);
	free(res);
}

// swap chars
void swap(char* a, char* b){
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//create double presentation
void createDouble(char **str, char* binNum){
	char *strChange = *str; //for ease of use
	unsigned int numLen = strlen(binNum);

	unsigned int fractionPoint = 0;
	unsigned int i = 0;
	unsigned int firstOne = 0; //will store the index of the first 1
	int exponenet = 0;
	char expo[12] = ""; //exponent string

	fractionPoint = findPoint(binNum); //find the index of the fraction point

	// creation of the exponenet and mantisa
	if (fractionPoint == 1 && numLen == 1){ // case the number is with only 1 digit and no fraction point
		if (strcmp(binNum, "0") == 0) // number is 0
			exponenet = 0;
		else{
			binNum[0] = '0';
			exponenet = 1023;
		}
	}
	else if (fractionPoint == numLen){ // the number has no fraction
		for (i = 0; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 1] = '\0';
		exponenet = 1023 + numLen;
	}
	else if (fractionPoint == 1 && binNum[0] == '1'){ // the number is in the format 1.xxx...
		for (i = 2; i<numLen; ++i)
			swap(&binNum[i], &binNum[i-2]);
		binNum[numLen - 2] = '\0';
		exponenet = 1023;
	}
	else if (fractionPoint == 1 && binNum[0] == '0'){ // the number is in the format 0....1...
		firstOne = 0;
		for (i = 2; i < numLen; ++i){ //find the first 1
			if (binNum[i] == '1'){
				firstOne = i;
				break;
			}
		}
		for (i = firstOne+1; i<numLen; ++i) // create the correct mantisa
			swap(&binNum[i], &binNum[i - (firstOne + 1)]);
		binNum[numLen - (firstOne + 1)] = '\0';
		exponenet = 1023 - (firstOne - 1);
	}
	else{ // any other case
		// remove the point
		for (i = fractionPoint; i < numLen-1; ++i)
			swap(&binNum[i], &binNum[i + 1]);

		//remove first one
		for (i = 0; i < numLen - 2; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 2] = '\0';
		exponenet = 1023 + (fractionPoint - 1);
	}

	_itoa(exponenet, expo, 2); //create exponenet string
	strcpy(strChange + 1 + (11 - strlen(expo)), expo); // store the exponent in place
	strcpy(strChange + strlen(strChange), binNum); //store the mantisa in place
}

void createFloat(char **str, char* binNum){
	char *strChange = *str; //for ease of use
	unsigned int numLen = strlen(binNum);

	unsigned int fractionPoint = 0;
	unsigned int i = 0;
	unsigned int firstOne = 0; //will store the index of the first 1
	int exponenet = 0;
	char expo[9] = ""; //exponent string

	fractionPoint = findPoint(binNum); //find the index of the fraction point

	// creation of the exponenet and mantisa
	if (fractionPoint == 1 && numLen == 1){ // case the number is with only 1 digit and no fraction point
		if (strcmp(binNum, "0") == 0) // number is 0
			exponenet = 0;
		else{
			binNum[0] = '0';
			exponenet = 127;
		}
	}
	else if (fractionPoint == numLen){ // the number has no fraction
		for (i = 0; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 1] = '\0';
		exponenet = 127 + numLen;
	}
	else if (fractionPoint == 1 && binNum[0] == '1'){ // the number is in the format 1.xxx...
		for (i = 2; i<numLen; ++i)
			swap(&binNum[i], &binNum[i - 2]);
		binNum[numLen - 2] = '\0';
		exponenet = 127;
	}
	else if (fractionPoint == 1 && binNum[0] == '0'){ // the number is in the format 0....1...
		firstOne = 0;
		for (i = 2; i < numLen; ++i){ //find the first 1
			if (binNum[i] == '1'){
				firstOne = i;
				break;
			}
		}
		for (i = firstOne + 1; i<numLen; ++i) // create the correct mantisa
			swap(&binNum[i], &binNum[i - (firstOne + 1)]);
		binNum[numLen - (firstOne + 1)] = '\0';
		exponenet = 127 - (firstOne - 1);
	}
	else{ // any other case
		// remove the point
		for (i = fractionPoint; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);

		//remove first one
		for (i = 0; i < numLen - 2; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 2] = '\0';
		exponenet = 127 + (fractionPoint - 1);
	}

	_itoa(exponenet, expo, 2); //create exponenet string
	strcpy(strChange + 1 + (8 - strlen(expo)), expo); // store the exponent in place
	strcpy(strChange + strlen(strChange), binNum); //store the mantisa in place
}

// exercise function wrapper
char* Convert2Float(bool neg, char *i, char *f, bool double_percision){
	char *strFP = (char*)malloc(32 + 32 * double_percision+1); //allocate memory according to the double_percision
	char *numStr = (char*)malloc(strlen(i) + strlen(f) + 1 + 1); //allocate memory that will store whole, fraction and point
	char *binNum;

	memset(strFP, '0', 32 + 32 * double_percision); //set all cells with '0'
	strFP[32 + 32 * double_percision] = '\0'; // set last digit to NULL

	// create number string
	strcpy(numStr, i);
	if (strcmp(f, "0") != 0){
		numStr[strlen(i)] = '.';
		strcpy(numStr + strlen(i) + 1, f);
	}

	// transform to binary according to the double_percision
	if (double_percision==true)
		binNum = _strdup(Base2Base(numStr, 10, 2, 52));
	else
		binNum = _strdup(Base2Base(numStr, 10, 2, 23));

	if (atoi(i)>0) // case the number is not zero
		strFP[0] = '0' + neg;

	// create the presentation according to the double_percision
	if (double_percision == true)
		createDouble(&strFP, binNum);
	else
		createFloat(&strFP, binNum);

	free(numStr);
	free(binNum);

	// use the following if so that all zeros will be shown
	if (strFP!=NULL && strlen(strFP) != (32 + 32 * double_percision)){
		strFP[strlen(strFP)] = '0';
	}

	return strFP;
}