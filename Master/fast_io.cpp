#include "fast_io.h"

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
			digits[index++] = l % 10 + '0';
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