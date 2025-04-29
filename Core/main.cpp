#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define debug if(0)
#define helper

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

#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

int n, m, node_index = 0;
int src, dst;
vector<int> *graph;

int *_index, *lowlink, *scc;
bool *on_stack;
vector<int> stack;

void strongconnect(const int x)
{
	_index[x] = lowlink[x] = node_index++;
	stack.eb(x);
	on_stack[x] = true;

	helper const int size = graph[x].size();
	for (int i = 0; i < size; ++i)
	{
		helper const int neighbour = graph[x][i];
		if (_index[neighbour] < 0) // neighbour not visited yet
		{
			strongconnect(neighbour);
			lowlink[x] = min(lowlink[x], lowlink[neighbour]);
		}
		else if (on_stack[neighbour]) // neighbour on stack must belong to the same SCC
		{
			lowlink[x] = min(lowlink[x], _index[neighbour]);
		} // otherwise x -> neighbour would be an edge pointing to another, already discovered SCC, and should be ignored
	}
	if (lowlink[x] == _index[x]) // no earlier node in the same SCC has been found, otherwise lowlink[x] would point to its index
	{
		for (;;)
		{
			helper const int y = stack.back();
			stack.pop_back();
			on_stack[y] = false;
			scc[y] = x;
			if (y == x) break;
		}
	}
}
int find(const int x)
{
	if (scc[x] == x) return x;
	return scc[x] = find(scc[x]);
}

int main()
{
#ifdef UNSAFE_IO
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);
#endif
	readUI(&n);
	graph =			new vector<int>[n];
	_index =		(int *)malloc(n * sizeof(int));
	lowlink =		(int *)malloc(n * sizeof(int));
	scc =			(int *)malloc(n * sizeof(int));
	on_stack =		(bool *)calloc(n, sizeof(bool));
	memset(_index, -1, n * sizeof(int));
	memset(scc, -1, n * sizeof(int));

	readUI(&m);
	while (m--)
	{
		readUI(&src);
		readUI(&dst);
		graph[src].eb(dst);
	}

	for (int i = 0; i < n; ++i)
	{
		if (_index[i] < 0) strongconnect(i);
	}
	for (int i = 0; i < n; ++i)
	{
		if (i < find(i)) // reconnect SCC ownership to the lowest-indexed node
		{
			scc[find(i)] = i;
			scc[i] = i;
		}
		printf("%d\n", find(i));
	}

	free(on_stack);
	free(scc);
	free(lowlink);
	free(_index);
	delete[] graph;
	return 0;
}
/*
3 3
0 1
1 0
1 2

*/