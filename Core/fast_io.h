#pragma once

#define UNSAFE_IO // comment this out if your program needs thread-safe IO
#ifdef __unix__
#include<unistd.h>
	#ifdef UNSAFE_IO
		#define getchar getchar_unlocked
		#define putchar putchar_unlocked
	#endif
#else
	#include <cstdio>
#endif

void readI(int *i);
void readUI(int *i);
void readLL(long long int *l);
void readULL(long long int *l);
void write(long long int l);
void writeS(const char *s);