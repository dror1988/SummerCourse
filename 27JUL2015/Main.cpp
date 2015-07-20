#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//unsigned int findPoint(const char* src);
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision);
char* Decimal2Base(double src, unsigned int dst_base, unsigned int percision);
char* Base2Base(const char* src, unsigned int src_base, unsigned int dst_base, unsigned int percision){
	return Decimal2Base(Base2Decimal(src, src_base, percision), dst_base, percision);
}

void main()
{
	char *res;
	res = Base2Base("-110011.01", 2, 10, 5);
	printf("%s\n", res);
	free(res);
	res = Base2Base("1AB.CD", 16, 2, 20);
	printf("%s\n", res);
	free(res);
	res = Base2Base("234.12", 5, 10, 10);
	printf("%s\n", res);
	free(res);
	res = Base2Base("0", 9, 10, 5);
	printf("%s\n", res);
	free(res);
	res = Base2Base("10", 10, 10, 5);
	printf("%s\n", res);
	free(res);
}

// find fraction point in the string  if there is any
unsigned int findPoint(const char* src){
	unsigned int i,numSize;

	numSize = strlen(src);

	for (i = 0; i < numSize; ++i)
		if (src[i] == '.')
			return i;

	return numSize;
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
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision){
	unsigned int numSize = strlen(src);
	int i=0;
	double digitPower = 0;
	unsigned int fracPointIndex = findPoint(src);
	double newNum = 0;
	int startNum;

	(src[0] == '-') ? startNum = 1 : startNum = 0;

	if (fracPointIndex == numSize)
		return (double)atoi(src);

	// create left side of fraction point
	for (i = fracPointIndex - 1; i >= startNum; --i)
		newNum += (pow(src_base, digitPower++))*(char2num(src[i]));

	digitPower = -1;
	// create right side of fraction point
	for (i = fracPointIndex + 1; i < numSize; ++i)
		newNum += (pow(src_base, digitPower--))*(char2num(src[i]));

	if (src[0] == '-')
		newNum = -(newNum);

	return newNum;
}

// convert the whole part
char *convertWhole(int wholeVal, unsigned int dst_base){
	unsigned int index = 0;
	char c;
	char *newNum;
	newNum = (char*)malloc(100);
	if (wholeVal == 0)
		newNum[index++] = '0';
	while (wholeVal != 0){
		c = (wholeVal%dst_base);
		wholeVal = (wholeVal / dst_base); 
		if (c >= 10 && c <= 35)
			c= c + 'A';
		else
			c = c + '0';
		// Returns for each remainer option
		newNum[index++] = c;
	}
	newNum[index] = '\0';

	_strrev(newNum);
	return newNum;
}

//convert the fraction part
char *convertFraction(double fractionVal, unsigned int dst_base, unsigned int percision){
	unsigned int index = 0;
	char c;
	char *newNum;
	newNum = (char*)malloc(100);

	while (fractionVal != 0 && percision!=0){
		fractionVal = (fractionVal * dst_base);
		c = (int)fractionVal;
		if (c >= 10 && c <= 35)
			c = c + 'A';
		else
			c = c + '0';
		// Returns for each remainer option
		newNum[index++] = c;
		fractionVal = fractionVal - (int)fractionVal;
		--percision;
	}
	newNum[index] = '\0';

	return newNum;
}

char* removeTrailingZeros(char* str){
	unsigned int fracPointIndex = findPoint(str);
	unsigned int index = strlen(str) -1;
	char clearZero = 1;

	while (clearZero == 1 && index > fracPointIndex){
		if (str[index] == '0')
			str[index--] = '\0';
		else
			clearZero = 0;
	}

	return str;
}

char* Decimal2Base(double src, unsigned int dst_base, unsigned int percision){
	int wholeVal = abs(src);
	double fractionVal = fabs(src) - wholeVal;
	char *newNum;
	int len;

	newNum = (char*)malloc(100);

	if (src < 0){
		newNum[0] = '-';
		strcpy(newNum+1,convertWhole(wholeVal, dst_base));
	}else
		strcpy(newNum, convertWhole(wholeVal, dst_base));
	if (fractionVal!=0)
		strcat(newNum, ".");
	strcat(newNum, convertFraction(fractionVal, dst_base, percision));
	removeTrailingZeros(newNum);

	return newNum;
}