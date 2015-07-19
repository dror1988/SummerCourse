#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int findPoint(const char* src);
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision);
char* Decimal2Base(double src, unsigned int dst_base, unsigned int percision);
char* Base2Base(const char* src, unsigned int src_base, unsigned int dst_base, unsigned int percision){
	return Decimal2Base(Base2Decimal(src, src_base, percision), dst_base, percision);
//	return 0;
}

void main(){
	char src[80];
	unsigned int src_base,dst_base,percision;

	scanf("%s %d %d %d", &src, &src_base,&dst_base ,&percision);
	printf("%s\n", Base2Base(src, src_base, dst_base, percision));
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

// covert the number to binary
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision){
	unsigned int numSize = strlen(src);
	int i=0;
	double digitPower = 0;
	unsigned int fracPointIndex = findPoint(src);
	double newNum = 0;
	unsigned int startNum;

	(src[0] == '-') ? startNum = 1 : startNum = 0;

	if (fracPointIndex == numSize)
		return (double)atoi(src);

	// create left side of fraction point
	for (i = fracPointIndex - 1; i >= startNum; --i)
		newNum += (pow(src_base, digitPower++))*(src[i] - '0');

	digitPower = -1;
	// create right side of fraction point
	for (i = fracPointIndex + 1; i < numSize; ++i)
		newNum += (pow(src_base, digitPower--))*(src[i] - '0');

	if (src[0] == '-')
		newNum = -(newNum);

	return newNum;
}

char *convertWhole(int wholeVal, unsigned int dst_base){
	unsigned int index = 0;
	char c;
	char *newNum;
	newNum = (char*)malloc(100);
	while (wholeVal != 0){
		c = (wholeVal%dst_base);
		wholeVal = (wholeVal / dst_base); 
		if (c == 10){
			c = 'A';
		}
		else if (c == 11){
			c ='B';
		}
		else if (c == 12){
			c = 'C';
		}
		else if (c == 13){
			c = 'D';
		}
		else if (c == 14){
			c = 'E';
		}
		else if (c == 15){
			c = 'F';
		}
		else{
			c = c + '0';
		}
		// Returns for each remainer option
		newNum[index++] = c;
	}
	newNum[index] = '\0';

	_strrev(newNum);
	return newNum;
}

char *convertFraction(double fractionVal, unsigned int dst_base, unsigned int percision){
	unsigned int index = 0;
	char c;
	char *newNum;
	newNum = (char*)malloc(100);

	while (fractionVal != 0 && percision!=0){
		fractionVal = (fractionVal * dst_base);
		c = (int)fractionVal;
		if (c == 10){
			c = 'A';
		}
		else if (c == 11){
			c = 'B';
		}
		else if (c == 12){
			c = 'C';
		}
		else if (c == 13){
			c = 'D';
		}
		else if (c == 14){
			c = 'E';
		}
		else if (c == 15){
			c = 'F';
		}
		else{
			c = c + '0';
		}
		// Returns for each remainer option
		newNum[index++] = c;
		fractionVal = fractionVal - (int)fractionVal;
		--percision;
	}
	newNum[index] = '\0';

	return newNum;
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
	strcat(newNum, ".");
	strcat(newNum, convertFraction(fractionVal, dst_base, percision));

	return newNum;
}