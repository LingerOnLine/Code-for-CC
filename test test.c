#include<stdio.h>
#include "int256.h"

int main(void) {
	printf_s("Welcome to use the \"int256.h\"\n");
	printf_s("The main information is as follow:\n");
	printf_s("The max length of char value is : 78 .");
	putchar('\n');
	printf_s("MYUINT256_MAX £º");
	char cc[79];
	printVU256(MYUINT256_MAX, cc);
	putchar('\n');
	printf_s("MYINT256_MAX £º");
	printV256(MYINT256_MAX, cc);
	putchar('\n');
	printf_s("MYINT256_MIN £º");
	printV256(MYINT256_MIN, cc);
	putchar('\n');
	printf_s("See£¿");
}