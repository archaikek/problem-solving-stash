#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define debug if(0)

#define UNSAFE_IO // comment this out if your program needs thread-safe IO
#ifdef __unix__
#include<unistd.h>
#include<cstdio>
#ifdef UNSAFE_IO
#define _getchar getchar_unlocked
#define _putchar putchar_unlocked
#endif
#else
#define _getchar getchar
#define _putchar putchar
#include <cstdio>
#endif

#include <vector>
#include <queue>

#define MAX_NODE_COUNT 1000

using namespace std;

typedef long long int LL;
typedef long double LD;
typedef short int SH;

inline void readI(int *i)
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
inline void readUI(int *i)
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
inline void readLL(long long int *l)
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
inline void readULL(long long int *l)
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
inline void readS(char *s)
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
inline void write(long long int l)
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
inline void writeS(const char *s)
{
	const char *end = s;
	while (*end != '\0')
	{
		_putchar(*end);
		++end;
	}
}

int t, n, src, m, dst, start, mode;
int visited[MAX_NODE_COUNT + 1], run_count;
vector<int> nodes[MAX_NODE_COUNT + 1], path;

void dfs(int node)
{
	path.eb(node);
	visited[node] = run_count;
	
	const int size = nodes[node].size();
	for (int i = 0; i < size; ++i)
	{
		if (visited[nodes[node][i]] < run_count) dfs(nodes[node][i]);
	}
}
void bfs(int node)
{
	visited[node] = run_count;
	queue<int> queue;

	queue.push(node);
	while (!queue.empty())
	{
		node = queue.front();
		queue.pop();
		path.eb(node);

		const int size = nodes[node].size();
		for (int i = 0; i < size; ++i)
		{
			if (visited[nodes[node][i]] < run_count)
			{
				visited[nodes[node][i]] = run_count;
				queue.push(nodes[node][i]);
			}
		}
	}
}
inline void write_path()
{
	debug _putchar('\t');
	const int size = path.size();
	for (int i = 0; i < size; ++i)
	{
		write(path[i]);
		_putchar(' ');
	}
	_putchar('\n');
}

int main()
{
	readUI(&t);
	for (int x = 1; x <= t; ++x)
	{
		readUI(&n);
		for (int i = 1; i <= n; ++i) nodes[i].clear();
		for (int i = 0; i < n; ++i)
		{
			readUI(&src);
			readUI(&m);
			for (int j = 0; j < m; ++j)
			{
				readUI(&dst);
				nodes[src].eb(dst);
			}
		}

		bool written = false;
		for (;;)
		{
			readUI(&src);
			readUI(&mode);
			if (src == 0 && mode == 0) break;
			if (!written)
			{
				written = true;
				writeS("graph ");
				write(x);
				_putchar('\n');
			}

			++run_count;
			path.clear();
			if (mode == 0)
			{
				dfs(src);
			}
			else
			{
				bfs(src);
			}
			write_path();
		}
	}
	return 0;
}

/*
3
6
1 2 3 4
2 2 3 6
3 2 1 2
4 1 1
5 0
6 1 2
5 1
1 0
1 0
0 0
10
1 6 3 5 6 7 8 9
2 1 9
3 2 1 5
4 5 6 7 8 9 10
5 4 1 3 7 8
6 3 1 4 7
7 5 1 4 5 6 8
8 5 1 4 5 7 10
9 3 1 2 4
10 2 4 8
7 1
1 0
2 1
4 1
7 1
0 0
2
1 0
2 0
1 1
0 0
*/