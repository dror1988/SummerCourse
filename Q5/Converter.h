#ifndef CONVERTER_H__
#define CONVERTER_H__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// find fraction point in the string  if there is any
unsigned int findPoint(const char* src);
// convert char to num
int char2num(char c);
// covert the number to binary
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision);
// convert the whole part
char *convertWhole(int wholeVal, unsigned int dst_base);
//convert the fraction part
char *convertFraction(double fractionVal, unsigned int dst_base, unsigned int percision);
//remove trailing spaces
char* removeTrailingZeros(char* str);

//convert from decimal to a given base
char* Decimal2Base(double src, unsigned int dst_base, unsigned int percision);
//converts from src number src_base to dst_base with the given percision
char* Base2Base(const char* src, unsigned int src_base, unsigned int dst_base, unsigned int percision);
//unsigned int findPoint(const char* src);
double Base2Decimal(const char* src, unsigned int src_base, unsigned int percision);

#endif