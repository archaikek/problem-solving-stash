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
#include <vector>

using namespace std;

#define INF 1000000007

int n, m;
int src, dst;
int *rep, *union_size;
bool *visited;
int curr_order, *post_order;
vector<int> *graph, *transposed;

int find(int x)
{
	if (x == rep[x]) return x;
	return rep[x] = find(rep[x]);
}
void onion(int x, int y)
{
	x = find(x);
	y = find(y);

	if (x == y) return;
	if (union_size[x] < union_size[y]) swap(x, y);

	rep[y] = rep[x];
	union_size[x] += union_size[y];
}

void dfs1(const int x)
{
	visited[x] = true;
	const int size = graph[x].size();
	for (int i = 0; i < size; ++i)
	{
		if (!visited[graph[x][i]]) dfs1(graph[x][i]);
	}
	post_order[curr_order++] = x;
}
void dfs2(const int x)
{
	visited[x] = false;
	const int size = transposed[x].size();
	for (int i = 0; i < size; ++i)
	{
		helper int neighbour = transposed[x][i];
		if (visited[neighbour])
		{
			onion(x, neighbour);
			dfs2(neighbour);
		}
	}
}

int main()
{
#ifdef UNSAFE_IO
	std::cin.tie(0);
	std::cout.tie(0);
	std::ios_base::sync_with_stdio(0);
#endif
	readUI(&n);
	rep =			(int *)malloc(n * sizeof(int));
	union_size =	(int *)malloc(n * sizeof(int));
	visited =		(bool *)calloc(n, sizeof(bool));
	post_order =	(int *)malloc(n * sizeof(int));
	graph =			new vector<int>[n];
	transposed =	new vector<int>[n];
	for (int i = 0; i < n; ++i)
	{
		rep[i] = i;
		union_size[i] = 1;
	}
	readUI(&m);

	for (int i = 0; i < m; ++i)
	{
		readUI(&src);
		readUI(&dst);
		graph[src].eb(dst);
		transposed[dst].eb(src);
	}

	for (int i = 0; i < n; ++i) // calculate post orders for the graph
	{
		if (!visited[i]) dfs1(i);
	}
	for (int i = n - 1; i >= 0; --i)
	{
		if (visited[post_order[i]]) dfs2(post_order[i]); // traverse the transposed graph in reverse post order
	}
	for (int i = 0; i < n; ++i)
	{
		if (i < find(i))
		{
			rep[rep[i]] = rep[i] = i; // transfer the union representant to the lowest member of the union
		}
		write(find(i));
		_putchar('\n');
	}

	delete[] transposed;
	delete[] graph;
	free(post_order);
	free(visited);
	free(union_size);
	free(rep);
	return 0;
}
/*
3 3
0 1
1 0
1 2

*/