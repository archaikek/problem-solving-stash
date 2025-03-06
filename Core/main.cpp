#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define UNSAFE_IO // comment this out if your program needs thread-safe IO
#ifdef __unix__
#include <unistd.h>
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

#include <vector>

#define ff first
#define ss second
#define eb emplace_back
#define debug if(1)

#define MAX_NODE_COUNT 10000
#define MAX_EDGE_COUNT 100000

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

int n, m;
vector<pair<int, int>> nodes[MAX_NODE_COUNT + 1];
pair<int, int> edges[MAX_EDGE_COUNT];
LL result;

int rep[MAX_NODE_COUNT + 1], rep_size[MAX_NODE_COUNT + 1];
int find(const int node)
{
	if (node == rep[node]) return node;
	return rep[node] = find(rep[node]);
}
void onion(int x, int y)
{
	int x = find(x);
	int y = find(y);
	if (x == y) return x;

	if (rep_size[x] < rep_size[y])
	{
		swap(x, y);
	}
	rep[y] = x;
	rep_size[x] += rep_size[y];
}
void init_find_and_union(const int node_count)
{
	for (int i = 1; i <= node_count; ++i)
	{
		rep[i] = i;
		rep_size[i] = 1;
	}
}

int main()
{
	readUI(&n);
	readUI(&m);

	return 0;
}