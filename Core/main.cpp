#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define debug if(0)
#define MOD 1000000007
#define MAXN 200007

typedef long long int LL;
typedef long double LD;
typedef short int SH;
using namespace std;

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
#include <algorithm>

void readI(int *i);
void readUI(int *i);
void readLL(long long int *l);
void readULL(long long int *l);
void readS(char *s);
void write(long long int l);
void writeS(const char *s);

int n, m, order[MAXN], o, visited[MAXN], run_count = 1;
vector<int> neighbours[MAXN], rev[MAXN], comp, scc_sizes;

int max_size = 1, sum_counts[MAXN];
LL result = 1;
vector<int> pent;

void dfs1(const int node)
{
	visited[node] = run_count;
	const int size = neighbours[node].size();
	for (int i = 0; i < size; ++i)
	{
		if (visited[neighbours[node][i]] < run_count) dfs1(neighbours[node][i]);
	}
	order[o++] = node;
}
void dfs2(const int node)
{
	visited[node] = run_count;
	comp.eb(node);
	const int size = rev[node].size();
	for (int i = 0; i < size; ++i)
	{
		if (visited[rev[node][i]] < run_count) dfs2(rev[node][i]);
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
	readUI(&m);
	for (int i = 0; i < m; ++i)
	{
		int src, dst;
		readUI(&src);
		readUI(&dst);
		neighbours[src].eb(dst);
		rev[dst].eb(src);
	}

	for (int i = 0; i < n; ++i)
	{
		if (visited[i] < run_count) dfs1(i);
	}

	++run_count;
	for (int i = n - 1; i >= 0; --i)
	{
		if (visited[order[i]] < run_count)
		{
			comp.clear();
			dfs2(order[i]);
			scc_sizes.eb(comp.size());
			max_size = max(max_size, (int)comp.size());
		}
	}

	sum_counts[0] = 1;
	for (int i = 1;; ++i)
	{
		int g = i * (3 * i - 1) / 2;
		if (g > max_size) break;
		pent.eb(g);

		g = i * (3 * i + 1) / 2;
		if (g > max_size) continue;
		pent.eb(g);
	}

	int size = pent.size();
	for (int i = 1; i <= max_size; ++i)
	{
		LL sum = 0;
		for (int j = 0; j < size; ++j)
		{
			int g = pent[j];
			if (g > i) break;
			int sign = (j / 2 % 2 == 0 ? 1 : -1);
			sum += sign * (LL)sum_counts[i - g];
			sum %= MOD;
		}
		sum_counts[i] = (sum + MOD) % MOD;
	}

	size = scc_sizes.size();
	for (int i = 0; i < size; ++i)
	{
		result *= sum_counts[scc_sizes[i]];
		result %= MOD;
	}

	write(result);

	return 0;
}

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