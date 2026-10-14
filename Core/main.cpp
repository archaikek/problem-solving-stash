#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define helper
#define debug if(0)

typedef long long int LL;
typedef long double LD;
typedef short int SH;

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

#include <cstdio>
#include <iostream>
#include <vector>

void readI(int *i);
void readUI(int *i);
void readLL(long long int *l);
void readULL(long long int *l);
void readS(char *s);
void write(long long int l);
void writeS(const char *s);

/* USER CODE BEGINS HERE */

inline int binsearch(const int *tab, int left, int right, const int val);

#define MAXN (200000)
#define INF (1<<30)

int sum[MAXN + 1]; // contains the running sum of input numbers modulo k
std::vector<int> pos[MAXN]; // contains the positions where each sum values appear in the sequence
int main()
{
#ifdef UNSAFE_IO
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);
#endif
	int t;
	readUI(&t);
	while (t--)
	{
		sum[0] = 0;
		pos[0].eb(0);
		int n, k;
		readUI(&n);
		readUI(&k);

		for (int i = 1; i <= n; ++i)
		{
			int a;
			readUI(&a);
			sum[i] = (sum[i - 1] + a) % k;
			pos[sum[i]].eb(i);
			
			debug printf("%d ", sum[i]);
		}
		debug printf("\n");

		int result = 0;
		for (int i = 0; i < k; ++i)
		{
			pos[i].eb(INF);
			debug for (auto p : pos[i]) printf("%d ", p);
			debug printf("\n");

			helper const int *tab = &(pos[i][0]), size = pos[i].size();
			for (int j = 0; j < size - 1; ++j)
			{
				int first_pos = binsearch(tab, j + 1, std::min(size, j + k + 1), tab[j] + k + 1);
				debug printf("Result: %d - %d = %d\n", size - 1, first_pos, size - 1 - first_pos);
				result += size - 1 - first_pos;
			}

			pos[i].clear();
		}
		write(result);
		putchar('\n');
	}
	return 0;
}

inline int binsearch(const int *tab, int left, int right, const int val)
{
	while (left + 1 < right)
	{
		int mid = (left + right) / 2;

		debug
		{
			printf("Ssearching <%d, %d) for %d: ", left, right, val);
			printf("-> ");
			for (int i = left; i < right; ++i)
			{
				if (i == mid)
					printf("(%d) ", tab[i]);
				else
					printf("%d ", tab[i]);
			}
			printf("<-\n");
		}

		if (val < tab[mid])
			right = mid;
		else
			left = mid;
	}
	if (tab[left] < val)
		++left;
	debug printf("\tReturning %d (%d)\n", left, tab[left]);
	return left;
}

/* END OF USER CODE */

void readI(int *i)
{
	register int r = 0;
	register char c = _getchar();
	int z = (c == '-' ? -1 : 1);

	while (c < '0' || c > '9')
	{
		c = _getchar();
		if (c == '-') z = -1;
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = _getchar();
	}
	*i = r * z;
}
void readUI(int *i)
{
	register int r = 0;
	register char c = _getchar();

	while (c < '0' || c > '9')
	{
		c = _getchar();
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = _getchar();
	}
	*i = r;
}
void readLL(long long int *l)
{
	register long long int r = 0;
	register char c = _getchar();
	int z = (c == '-' ? -1 : 1);

	while (c < '0' || c > '9')
	{
		c = _getchar();
		if (c == '-') z = -1;
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = _getchar();
	}
	*l = r * z;
}
void readULL(long long int *l)
{
	register long long int r = 0;
	register char c = _getchar();

	while (c < '0' || c > '9')
	{
		c = _getchar();
	}
	while (c >= '0' && c <= '9')
	{
		r = 10 * r + c - '0';
		c = _getchar();
	}
	*l = r;
}
void readS(char *s)
{
	register int index = 0;
	register char c = _getchar();

	while (c < '!' || c > 'z')
	{
		c = _getchar();
	}
	while (c >= '!' && c <= 'z')
	{
		s[index++] = c;
		c = _getchar();
	}
	s[index] = '\0';
}
void write(long long int l)
{
	if (!l) _putchar('0');
	else
	{
		if (l < 0)
		{
			_putchar('-');
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
			_putchar(digits[i]);
		}
	}
}
void writeS(const char *s)
{
	const char *end = s;
	while (*end != '\0')
	{
		_putchar(*end);
		++end;
	}
}