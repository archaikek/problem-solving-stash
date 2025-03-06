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
#include <cstdlib>

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

typedef struct edge_t
{
	int src, dst, cost;
};
bool operator<(const edge_t &a, const edge_t &b)
{
	return a.cost < b.cost;
}

int n, m, src, dst, cost;
vector<int> nodes[MAX_NODE_COUNT + 1];
edge_t edges[MAX_EDGE_COUNT];
LL result;

int rep[MAX_NODE_COUNT + 1], rep_size[MAX_NODE_COUNT + 1];
int find(const int node)
{
	if (node == rep[node]) return node;
	return rep[node] = find(rep[node]);
}
void onion(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x == y) return;

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

void bubblesort(edge_t *tab, const int size, edge_t *buffer)
{
	buffer[0] = tab[0];
	for (int i = 1; i < size; ++i)
	{
		for (int j = i; j >= 0; --j)
		{
			if (tab[i] < buffer[j - 1])
			{
				buffer[j] = buffer[j - 1];
			}
			else
			{
				buffer[j] = tab[i];
				break;
			}
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}

void _merge(edge_t *tab, edge_t *mid, int size, edge_t *buffer)
{
	const int half = mid - tab;
	int left = 0, right = 0;
	for (int i = 0; i < size; ++i)
	{
		if ((left < half && tab[left] < mid[right]) || right >= size - half)
		{
			buffer[i] = tab[left++];
		}
		else
		{
			buffer[i] = mid[right++];
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}

void _mergesort_hybrid(edge_t *tab, const int size, edge_t *buffer, const int cutoff)
{
	if (size <= cutoff)
	{
		bubblesort(tab, size, buffer);
		return;
	}

	const int half = size / 2;
	edge_t *mid = tab + half;
	_mergesort_hybrid(tab, half, buffer, cutoff);
	_mergesort_hybrid(mid, size - half, buffer, cutoff);

	int left = 0, right = 0;
	for (int i = 0; i < size; ++i)
	{
		if ((left < half && tab[left] < mid[right]) || right >= size - half)
		{
			buffer[i] = tab[left++];
		}
		else
		{
			buffer[i] = mid[right++];
		}
	}
	for (int i = 0; i < size; ++i)
	{
		tab[i] = buffer[i];
	}
}
void mergesort_hybrid(edge_t *begin, edge_t *end, const int cutoff)
{
	const int size = end - begin;
	edge_t *buffer = (edge_t *)malloc(size * sizeof(edge_t));

	_mergesort_hybrid(begin, size, buffer, cutoff);

	free(buffer);
}

int main()
{
	readUI(&n);
	readUI(&m);
	init_find_and_union(n);

	for (int i = 0; i < m; ++i)
	{
		readUI(&src);
		readUI(&dst);
		readUI(&cost);

		nodes[src].eb(dst);
		nodes[dst].eb(src);
		edges[i] = { src, dst, cost };
	}
	mergesort_hybrid(edges, edges + m, 32);

	for (int i = 0; i < m; ++i)
	{
		if (find(edges[i].src) != find(edges[i].dst))
		{
			result += edges[i].cost;
			onion(edges[i].src, edges[i].dst);
		}
	}

	write(result);
	return 0;
}