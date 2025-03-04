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

inline void readI(int *i);
inline void readUI(int *i);
inline void readLL(long long int *l);
inline void readULL(long long int *l);
inline void write(long long int l);
inline void writeS(const char *s);