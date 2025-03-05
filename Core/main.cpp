#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define eb emplace_back
#define debug if(0)

#define UNSAFE_IO // comment this out if your program needs thread-safe IO
#ifdef __unix__
#include<unistd.h>
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
#include <map>
#include <cstring>

#define MAX_NAME_LENGTH 10
#define MAX_NODE_COUNT 10000
#define INF ((1<<31) - 1)

using namespace std;

typedef long long int LL;
typedef long double LD;
typedef short int SH;

typedef struct name_t
{
	char name[MAX_NAME_LENGTH];
};
bool operator<(const name_t &a, const name_t &b)
{
	return strcmp(a.name, b.name) < 0;
}

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

int s, n, p, r;
int results[MAX_NODE_COUNT + 1], updated[MAX_NODE_COUNT + 1], run_count;
name_t name, name2;
vector<pair<int, int>> nodes[MAX_NODE_COUNT + 1];
pair<int, int> temp;
map<name_t, int> cities;

void clear_vector(vector<pair<int, int>> &v)
{
	vector<pair<int, int>> empty;
	swap(empty, v);
}
void clear_nodes(const int node_count)
{
	for (int i = 1; i <= n; ++i)
	{
		nodes[i].clear();
	}
}
void clear_map(map<name_t, int> &m)
{
	//map<name_t, int> empty;
	//swap(m, empty);
	m.clear();
}

void dijkstra(const int start, const int finish)
{
	results[start] = 0;
	if (start == finish) return;

	++run_count;
	updated[start] = run_count;
	priority_queue<pair<int, int>> queue;
	int curr_node;

	queue.push({ 0, start });
	while (!queue.empty())
	{
		temp = queue.top();
		queue.pop();
		curr_node = temp.ss;
		if (curr_node == finish) break; // reached the finish, result found
		if (-temp.ff != results[curr_node]) continue; // suboptimal route to curr_node used, ignore
		debug printf("Processing %d @ %d\n", temp.ss, -temp.ff);

		const int size = nodes[curr_node].size();
		for (int i = 0; i < size; ++i)
		{
			temp = nodes[curr_node][i];
			int dest = temp.ff, cost = temp.ss;
			if (updated[dest] < run_count || results[dest] > results[curr_node] + cost)
			{
				updated[dest] = run_count;
				results[dest] = results[curr_node] + cost;
				queue.push({ -results[dest], dest });
			}
		}
	}
}

int main()
{
	readUI(&s);
	while (s--)
	{
		readUI(&n);
		clear_map(cities);
		clear_nodes(n);

		for (int i = 1; i <= n; ++i)
		{
			readS(name.name);
			cities[name] = i;

			readUI(&p);
			while (p--)
			{
				readUI(&temp.ff);
				readUI(&temp.ss);
				debug printf("%d --%d--> %d\n", i, temp.ss, temp.ff);
				nodes[i].eb(temp);
			}
		}

		readUI(&r);
		while (r--)
		{
			readS(name.name);
			readS(name2.name);
			dijkstra(cities[name], cities[name2]);
			write(results[cities[name2]]);
			_putchar('\n');
		}
	}
	return 0;
}
/*
1
4
gdansk
2
2 1
3 3
bydgoszcz
3
1 1
3 1
4 4
torun
3
1 3
2 1
4 1
warszawa
2
2 4
3 1
2
gdansk warszawa
bydgoszcz warszawa
*/