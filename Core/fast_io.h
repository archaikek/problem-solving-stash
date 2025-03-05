#pragma once
#include <cstdio>

#define UNSAFE_IO // comment this out if your program needs thread-safe IO
#ifdef __unix__
#include<unistd.h>
	#ifdef UNSAFE_IO
		#define _getchar getchar_unlocked
		#define _putchar putchar_unlocked
	#else
		#define _getchar getchar
		#define _putchar putchar
	#endif
#else
	#define _getchar getchar
	#define _putchar putchar
#endif

void readI(int *i);
void readUI(int *i);
void readLL(long long int *l);
void readULL(long long int *l);
void readS(char *s);
void write(long long int l);
void writeS(const char *s);