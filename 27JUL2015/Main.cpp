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
	unsigned int i, numSize;

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

// remove trailing zeros
void removeTrailingZeros(char** strNew){
	char* str = *strNew;
	unsigned int fracPointIndex = findPoint(str);
	unsigned int index = strlen(str) - 1;
	char clearZero = 1;

	// while need to clear zeros or reached the fraction point
	while (clearZero == 1 && index > fracPointIndex){
		// replace 0 with NULL
		if (str[index] == '0')
			str[index--] = '\0';
		else
			clearZero = 0;
	}
}

// convert the whole part
char *convertWhole(int wholeVal, unsigned int dst_base){
	unsigned int index = 0;
	char c;
	char *newNum = (char*)malloc(100);

	// case the number is 0
	if (wholeVal == 0)
		newNum[index++] = '0';

	// create the whole part string
	while (wholeVal != 0){
		c = (wholeVal%dst_base); //break numbers according to the base
		wholeVal = (wholeVal / dst_base);
		// create the charcters for the string
		if (c >= 10 && c <= 35)
			c = c + 'A';
		else
			c = c + '0';
		// store the char in the string
		newNum[index++] = c;
	}
	newNum[index] = '\0';

	// reverse the string
	_strrev(newNum);
	return newNum;
}

//convert the fraction part
char *convertFraction(double fractionVal, unsigned int dst_base, unsigned int percision){
	unsigned int index = 0;
	char c;
	char *newNum = (char*)malloc(100);

	// create the fraction part string
	while (fractionVal != 0 && percision != 0){
		fractionVal = (fractionVal * dst_base);
		c = (int)fractionVal; //break numbers according to the base
		// create the charcters for the string
		if (c >= 10 && c <= 35)
			c = c + 'A';
		else
			c = c + '0';
		// store the char in the string
		newNum[index++] = c;

		fractionVal = fractionVal - (int)fractionVal;
		--percision;
	}
	newNum[index] = '\0';

	return newNum;
}


// covert the number to decimal double
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision){
	unsigned int numSize = strlen(src);
	double digitPower = 0;
	double newNum = 0;
	int startNum = 0;
	int i = 0;
	unsigned int fracPointIndex = findPoint(src);

	// case of negative number
	(src[0] == '-') ? startNum = 1 : startNum = 0;

	// case there is no fraction point
	if (fracPointIndex == numSize)
		return (double)atoi(src);

	// create left side of fraction point
	for (i = fracPointIndex - 1; i >= startNum; --i)
		newNum += (pow(src_base, digitPower++))*(char2num(src[i]));

	digitPower = -1;
	// create right side of fraction point
	for (i = (int)fracPointIndex + 1; i < (int)numSize; ++i)
		newNum += (pow(src_base, digitPower--))*(char2num(src[i]));

	// case of negative number
	if (src[0] == '-')
		newNum = -(newNum);

	return newNum;
}

// convert decimal to any base 
char* Decimal2Base(double src, unsigned int dst_base, unsigned int percision){
	int wholeVal = (int)abs(src);
	double fractionVal = fabs(src) - wholeVal;
	char *newNum = NULL;
	char *temp = NULL;
	int len = 0;

	newNum = (char*)malloc(100);

	//create the whole part
	temp = convertWhole(wholeVal, dst_base);
	if (src < 0){ //case negative number
		newNum[0] = '-';
		strcpy(newNum + 1, temp);
	}
	else // case positive
		strcpy(newNum, temp);
	free(temp);

	// the given number has fraction part
	if (fractionVal != 0)
		strcat(newNum, ".");

	//create the fraction part
	temp = convertFraction(fractionVal, dst_base, percision);
	strcat(newNum, temp);
	free(temp);

	//remove any trailing spaces
	removeTrailingZeros(&newNum);

	return newNum;
}