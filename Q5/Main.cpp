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

void swap(char* a, char* b){
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


void createDouble(char **str, char* binNum){
	char *strChange = *str;
	unsigned int fractionPoint = 0;
	unsigned int i,firstOne;
	unsigned int numLen = strlen(binNum);
	int mantisa;
	char mant[12] = "";

	fractionPoint = findPoint(binNum);

	// case the number is 0
	if (fractionPoint == 1 && numLen == 1){
		if (strcmp(binNum, "0") == 0)
			mantisa = 0;
		else{
			binNum[0] = '0';
			mantisa = 1023;
		}
	}
	else if (fractionPoint == numLen){
		for (i = 0; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 1] = '\0';
		mantisa = 1023 + numLen;
	}
	else if (fractionPoint == 1 && binNum[0] == '1'){
		for (i = 2; i<numLen; ++i)
			swap(&binNum[i], &binNum[i-2]);
		binNum[numLen - 2] = '\0';
		mantisa = 1023;
	}
	else if (fractionPoint == 1 && binNum[0] == '0'){
		firstOne = 0;
		for (i = 2; i < numLen; ++i){
			if (binNum[i] == '1'){
				firstOne = i;
				break;
			}
		}
		for (i = firstOne+1; i<numLen; ++i)
			swap(&binNum[i], &binNum[i - (firstOne + 1)]);
		binNum[numLen - (firstOne + 1)] = '\0';
		mantisa = 1023 - (firstOne - 1);
	}
	else{
		// remove the point
		for (i = fractionPoint; i < numLen-1; ++i)
			swap(&binNum[i], &binNum[i + 1]);

		//remove first one
		for (i = 0; i < numLen - 2; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 2] = '\0';
		mantisa = 1023 + (fractionPoint - 1);
	}

	_itoa(mantisa, mant,2);
	strcpy(strChange + 1 + (11 - strlen(mant)), mant);
	strcpy(strChange + strlen(strChange), binNum);
}

void createFloat(char **str, char* binNum){
	char *strChange = *str;
	unsigned int fractionPoint = 0;
	unsigned int i, firstOne;
	unsigned int numLen = strlen(binNum);
	int mantisa;
	char mant[9] = "";

	fractionPoint = findPoint(binNum);

	// case the number is 0
	if (fractionPoint == 1 && numLen == 1){
		if (strcmp(binNum, "0") == 0)
			mantisa = 0;
		else{
			binNum[0] = '0';
			mantisa = 127;
		}
	}
	else if (fractionPoint == numLen){
		for (i = 0; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 1] = '\0';
		mantisa = 127 + numLen;
	}
	else if (fractionPoint == 1 && binNum[0] == '1'){
		for (i = 2; i<numLen; ++i)
			swap(&binNum[i], &binNum[i - 2]);
		binNum[numLen - 2] = '\0';
		mantisa = 127;
	}
	else if (fractionPoint == 1 && binNum[0] == '0'){
		firstOne = 0;
		for (i = 2; i < numLen; ++i){
			if (binNum[i] == '1'){
				firstOne = i;
				break;
			}
		}
		for (i = firstOne + 1; i<numLen; ++i)
			swap(&binNum[i], &binNum[i - (firstOne + 1)]);
		binNum[numLen - (firstOne + 1)] = '\0';
		mantisa = 127 - (firstOne - 1);
	}
	else{
		// remove the point
		for (i = fractionPoint; i < numLen - 1; ++i)
			swap(&binNum[i], &binNum[i + 1]);

		//remove first one
		for (i = 0; i < numLen - 2; ++i)
			swap(&binNum[i], &binNum[i + 1]);
		binNum[numLen - 2] = '\0';
		mantisa = 127 + (fractionPoint - 1);
	}

	_itoa(mantisa, mant, 2);
	strcpy(strChange + 1 + (8 - strlen(mant)), mant);
	strcpy(strChange + strlen(strChange), binNum);
}

// exercise function wrapper
char* Convert2Float(bool neg, char *i, char *f, bool double_percision){
	char *strFP = (char*)malloc(32 + 32 * double_percision+1);
	char *numStr = (char*)malloc(strlen(i) + strlen(f) + 2);
	char *binNum;
	memset(strFP, '0', 32 + 32 * double_percision);
	strFP[32 + 32 * double_percision] = '\0';

	strcpy(numStr, i);
	if (strcmp(f, "0") != 0){
		numStr[strlen(i)] = '.';
		strcpy(numStr + strlen(i) + 1, f);
	}
	//}else
	//	strcpy(numStr + strlen(i), f);

	if (double_percision==true)
		binNum=_strdup(Base2Base(numStr, 10, 2, 64));
	else
		binNum = _strdup(Base2Base(numStr, 10, 2, 32));

	if (atoi(i)>0)
		strFP[0] = '0' + neg;

	if (double_percision == true)
		createDouble(&strFP, binNum);
	else
		createFloat(&strFP, binNum);

	free(numStr);
	free(binNum);

	if (strFP!=NULL && strlen(strFP) != (32 + 32 * double_percision)){
		strFP[strlen(strFP)] = '0';
	}
	return strFP;
}