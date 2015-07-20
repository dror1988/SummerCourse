#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float String2Float(char *float_str);

void main(){

	printf("%f\n", String2Float("11000001001111000000000000000000")); //-11.75

	printf("%f\n", String2Float("01000000101000000000000000000000")); //5.0

	printf("%3.1f\n", String2Float("00000000000000000000000000000000")); //0.0

}

// find fraction point in the string  if there is any
unsigned int findPoint(const char* src){
	unsigned int i, numSize;

	numSize = strlen(src);

	for (i = 0; i < numSize; ++i)
	if (src[i] == '.')
		return i;

	return numSize;
}

void swap(char* a, char* b){
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// convert char to num
int char2num(char c){
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 10;
	if (c >= 'a' && c <= 'z')
		return c - 'a' + 10;
}

// covert the number to binary
double Base2Decimal(const char* src, unsigned int percision){
	unsigned int numSize = strlen(src);
	int i = 0;
	double digitPower = 0;
	unsigned int fracPointIndex = findPoint(src);
	double newNum = 0;

	if (fracPointIndex == numSize)
		return (double)atoi(src);

	// create left side of fraction point
	for (i = fracPointIndex - 1; i >= 0; --i)
		newNum += (pow(2, digitPower++))*(char2num(src[i]));

	digitPower = -1;
	// create right side of fraction point
	for (i = fracPointIndex + 1; i < numSize; ++i)
		newNum += (pow(2, digitPower--))*(char2num(src[i]));

	return newNum;
}

float String2Float(char *float_str){
	char *binNum = (char*)malloc(23 + 1+1+1);
	char *exponent = (char*)malloc(8 + 1);
	int exponenetVal=0;
	unsigned int numSize;
	int i = 0;
	double digitPower = 0;
	double num = 0;

	binNum[0] = '1';
	strncpy(binNum+1, float_str + 9, 24);
	strncpy(exponent, float_str + 1, 8);
	exponent[8] = '\0';

	numSize = strlen(exponent);
	for (i = numSize-1; i >=0; --i)
		exponenetVal += (int)(pow(2, digitPower++))*(char2num(exponent[i]));
	exponenetVal -= 127;
	
	if (exponenetVal >= 0){
		for (i = 24; i > exponenetVal + 1; --i)
			swap(&binNum[i], &binNum[i - 1]);
		binNum[exponenetVal + 1] = '.';
		binNum[25] = '\0';
	}
	else if (exponenetVal < 0){
		for (i = 24 - (exponenetVal + 1); i > 0; --i)
			swap(&binNum[i], &binNum[i - (exponenetVal + 1)]);
		binNum[0] = '0';
		binNum[1] = '.';
		binNum[25] = '\0';
	}

	num = Base2Decimal(binNum,23);

	if (float_str[0] == '1')
		num = -num;

	free(binNum);
	free(exponent);
	return num;

}