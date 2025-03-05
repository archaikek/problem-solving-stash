#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define debug if(0)

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
	#include <cstdio>
	#define _getchar getchar
	#define _putchar putchar
#endif

typedef long long int LL;
typedef long double LD;
typedef short int SH;

inline void readI(int *i)
{
	register int r = 0;
	register char c = getchar();
	int z = (c == '-' ? -1 : 1);

	while (c < '0' || c > '9')
	{
		c = getchar();
		if (c == '-') z = -1;
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = getchar();
	}
	*i = r * z;
}
inline void readUI(int *i)
{
	register int r = 0;
	register char c = getchar();

	while (c < '0' || c > '9')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = getchar();
	}
	*i = r;
}
inline void readLL(long long int *l)
{
	register long long int r = 0;
	register char c = getchar();
	int z = (c == '-' ? -1 : 1);

	while (c < '0' || c > '9')
	{
		c = getchar();
		if (c == '-') z = -1;
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = getchar();
	}
	*l = r * z;
}
inline void readULL(long long int *l)
{
	register long long int r = 0;
	register char c = getchar();

	while (c < '0' || c > '9')
	{
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = getchar();
	}
	*l = r;
}
inline void readS(char *s)
{
	register int index = 0;
	register char c = getchar();

	while (c < '!' || c > 'z')
	{
		c = getchar();
	}
	while (c >= '!' && c <= 'z')
	{
		s[index++] = c;
		c = getchar();
	}
}
inline void write(long long int l)
{
	if (!l) putchar('0');
	else
	{
		if (l < 0)
		{
			putchar('-');
			l = -l;
		}
		int index = 0, digits[21];
		while (l)
		{
			digits[++index] = l % 10 + '0';
			l /= 10;
		}
		for (int i = index + 1; --i;)
		{
			putchar(digits[i]);
		}
	}
}
inline void writeS(const char *s)
{
	const char *end = s;
	while (*end != '\0')
	{
		putchar(*end);
		++end;
	}
}


int main()
{

	return 0;
}