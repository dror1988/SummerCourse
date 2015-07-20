#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printArrayBinary(void *arr, unsigned int size);
void printByteBinary(const char c);

void main(){
	double num;
	scanf("%lf", &num);
	printArrayBinary((void*)&num, sizeof(num));
}

void printArrayBinary(void *arr, unsigned int size){
	unsigned int i;

	for (i = size - 1; i > 0; --i){
		printByteBinary(*((char*)arr + i));
		printf("-");
	}
	printByteBinary(*((char*)arr));
	printf("\n");
}

void printByteBinary(const char c){
	int i;
	char mask;

	for (i = 7; i >= 0; --i){
		mask = 1<<i;
		if ((mask&c) != 0)
			printf("1");
		else
			printf("0");
	}
}