#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define debug if(0)
#define MAXN 10007

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
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

void readI(int *i);
void readUI(int *i);
void readLL(long long int *l);
void readULL(long long int *l);
void readS(char *s);
void write(long long int l);
void writeS(const char *s);

int n, m, lowpoint[MAXN], depth[MAXN], visited[MAXN], result, run_count;
vector<int> neighbours[MAXN];

inline void connect(const int u, const int v)
{
	neighbours[u].eb(v);
	neighbours[v].eb(u);
}

void get_articulation_points(const int node, const int parent, const int dep)
{
	visited[node] = run_count;
	lowpoint[node] = depth[node] = dep;
	int child_count = 0;
	bool is_articulation_point = false;

	const int size = neighbours[node].size();
	for (int i = 0; i < size; ++i)
	{
		const int neighbour = neighbours[node][i];
		if (visited[neighbour] < run_count)
		{
			get_articulation_points(neighbour, node, dep + 1);
			++child_count;
			if (lowpoint[neighbour] >= dep) is_articulation_point = true;
			lowpoint[node] = min(lowpoint[node], lowpoint[neighbour]);
		}
		else if (neighbour != parent)
		{
			lowpoint[node] = min(lowpoint[node], depth[neighbour]);
		}
	}
	if ((parent >= 0 && is_articulation_point) || (parent < 0 && child_count > 1)) ++result;
}

int main()
{
#ifdef UNSAFE_IO
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);
#endif
infloop:
	readUI(&n);
	readUI(&m);
	if (n == 0 && m == 0) goto endloop;
	
	for (int i = 0; i <= n; ++i)
	{
		neighbours[i].clear();
	}
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		readUI(&u);
		readUI(&v);
		connect(u, v);
	}

	result = 0;
	++run_count;
	get_articulation_points(1, -1, 0);
	write(result);
	writeS("\n");
goto infloop;

endloop:

	return 0;
}

/*
3 3
1 2
2 3
1 3
6 8
1 3
6 1
6 3
4 1
6 4
5 2
3 2
3 5
0 0
*/

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