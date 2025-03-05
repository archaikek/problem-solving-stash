#define _CRT_SECURE_NO_WARNINGS
#define ff first
#define ss second
#define debug if(0)

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
	#include <cstdio>
	#define _getchar getchar
	#define _putchar putchar
#endif

typedef long long int LL;
typedef long double LD;
typedef short int SH;

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
inline void readS(char *s)
{
	register int index = 0;
	register char c = getchar();

	while (c < '!' || c > 'z')
	{
		c = getchar();
	}
	while (c >= '!' && c <= 'z')
	{
		s[index++] = c;
		c = getchar();
	}
	s[index] = '\0';
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
			digits[++index] = l % 10 + '0';
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

#include <vector>
#include <map>
#include <queue>
#include <cstring>

#define MAX_NAME_LENGTH 10
#define MAX_NODE_COUNT 10000

using namespace std;

typedef struct name_t
{
	char name[MAX_NAME_LENGTH];
};
bool operator<(const name_t &a, const name_t &b)
{
	return strcmp(a.name, b.name) < 0;
}

int s, n, p, r;
int results[MAX_NODE_COUNT + 1], visited[MAX_NODE_COUNT + 1], run_count;
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
		clear_vector(nodes[i]);
	}
}
void clear_map(map<name_t, int> &m)
{
	map<name_t, int> empty;
	swap(m, empty);
}

int main()
{
	readUI(&s);
	while (s--)
	{
		readUI(&n);
		clear_map(cities);
		clear_nodes(n);
	}
	return 0;
}