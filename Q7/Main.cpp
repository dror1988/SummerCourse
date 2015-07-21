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

	printf("%4.2f\n", String2Float("00111111001010001111010111000010")); //0.66

	printf("%4.2f\n", String2Float("10111111001000111101011100001010")); //-0.64

	printf("%f\n", String2Float("01000000010010010000111111011010")); //PI

	printf("%f\n", String2Float("00111111101101010000010011110011")); //sqrroor(2)

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

// swap 2 chars
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

// convert the number to decimal float
float Base2Decimal(const char* src, unsigned int percision){
	unsigned int numSize = strlen(src); // size of the number including fraction point
	float newNum = 0;
	double digitPower = 0;
	unsigned int fracPointIndex = findPoint(src); //fraction point index
	int i = 0; //index
	
	// case no fraction point exist 
	if (fracPointIndex == numSize)
		return (double)atoi(src);

	// create left side of fraction point
	for (i = fracPointIndex - 1; i >= 0; --i)
		newNum += (pow(2, digitPower++))*(char2num(src[i]));

	digitPower = -1;
	// create right side of fraction point
	for (i = (int)fracPointIndex + 1; i < (int)numSize; ++i)
		newNum += (pow(2, digitPower--))*(char2num(src[i]));

	return newNum;
}

// exrecise solution
float String2Float(char *float_str){
	char *binNum = (char*)malloc(23 + 1+1+1); //stores the mantisa and later add the 1
	char *exponent = (char*)malloc(8 + 1); //stores the exponent
	int exponenetVal=0;
	unsigned int numSize=0;
	int i = 0;
	double digitPower = 0;
	float num = 0;

	binNum[0] = '1'; //adds 1 in the head of the mantisa
	strncpy(binNum+1, float_str + 9, 24); //copy the mantisa to the new str
	strncpy(exponent, float_str + 1, 8); //copy exponenet to the new str
	exponent[8] = '\0';

	// calculate the exponent value
	numSize = strlen(exponent);
	for (i = numSize-1; i >=0; --i)
		exponenetVal += (int)(pow(2, digitPower++))*(char2num(exponent[i]));
	exponenetVal -= 127;
	
	/* 3 cases of exponent value:
		1. exponenet is >=0 means the fraction point is in place or need to move right
		2. exponenet is <0 means the number need to move right 
		3. exponenet is -127 means it is zero
	*/
	if (exponenetVal >= 0){
		for (i = 24; i > exponenetVal + 1; --i)
			swap(&binNum[i], &binNum[i - 1]);
		binNum[exponenetVal + 1] = '.';
		binNum[25] = '\0';
	}
	else if (exponenetVal < 0 && exponenetVal>-127){
		for (i = 24 - (exponenetVal + 2); i > 1; --i)
			swap(&binNum[i], &binNum[i - (exponenetVal + 3)]);
		binNum[0] = '0';
		binNum[1] = '.';
		binNum[25] = '\0';
	}
	else if (exponenetVal == -127){
		binNum[0] = '0';
		binNum[1] = '.';
		binNum[25] = '\0';
	}

	// convert from binary to decimal
	num = (float)Base2Decimal(binNum,23);

	// case of negative
	if (float_str[0] == '1')
		num = -num;
	
	//free allocations
	free(binNum);
	free(exponent);

	return num;

}