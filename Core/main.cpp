#include "common_defines.h"
#include "fast_io.h"
#include "structs.h"

#include <algorithm>

int find_independent_set(const graph_t *graph, int *solution);
void brute_force(const int n, const int k, const int *x, const int *y, int *solution);
int brute_result = 1 << 30;

int main(int argc, char **argv)
{
	int cases;
	readUI(&cases);
	for (int t = 0; t < cases; ++t)
	{
		int n, k;
		readUI(&n);
		readUI(&k);
		int *x = (int *)malloc(2 * n * sizeof(int)), *y = x + n;
		int m = 0;
		ii *lengths = (ii *)malloc(((n * (n - 1)) / 2) * sizeof(ii));
		graph_t *graph = create_graph(n);

		for (int i = 0; i < n; ++i)
		{
			readI(x + i);
			readI(y + i);
			for (int j = 0; j < i; ++j)
			{
				add_edge(graph, i, j);
				lengths[m++] = { SQ(x[i] - x[j]) + SQ(y[i] - y[j]), n * i + j }; // should be a square root of this, but these work too
			}
		}
		sort(lengths, lengths + m);

		if (true)
		//if (argc > 1 && strcmp(argv[1], "-brute") == 0)
		{
			int *solution = (int *)malloc(k * sizeof(int));
			brute_force(n, k, x, y, solution);

			printf("case %d Y\n", t + 1);
			for (int i = 0; i < k; ++i)
			{
				printf("%d ", solution[i]);
			}
			printf("\n");

			free(solution);
		}
		else
		{
			int left = 0, right = m; // right - first outside the table
			int *solution = (int *)malloc(k * sizeof(int));
			int *temp_solution = (int *)malloc(n * sizeof(int));
			while (left + 1 < right)
			{
				int mid = (left + right) / 2; // mid - first outside the left half <==> first in the right half
				graph_t *squared = create_squared_graph(graph, lengths, mid);

				int result = find_independent_set(squared, temp_solution);
				delete_graph(squared);

				if (result <= k) // solution found, look for something smaller
				{
					memcpy(solution, temp_solution, result * sizeof(int));
					int pos = result, offset = 0;
					for (int i = 0; pos < k; ++i) // insert random *other* vertices to the solution, to have it of size k
					{
						if (solution[i - offset] != i) // the vertex was not used, it's good to add
						{
							solution[pos++] = i;
							++offset;
						}
					}
					right = mid;
				}
				else // solution not found, look for something bigger
				{
					left = mid;
				}
			}

			printf("case %d Y\n", t + 1);
			for (int i = 0; i < k; ++i)
			{
				printf("%d ", solution[i]);
			}
			printf("\n");
			free(temp_solution);
			free(solution);
		}

		delete_graph(graph);
		free(lengths);
		free(x);
	}
	return 0;
}

int find_independent_set(const graph_t *graph, int *solution)
{
	const int n = graph->size;
	int result = 0;
	set<int> *sol = new set<int>();
	helper const vector<int> *edges = graph->edges;

	for (int i = 0; i < n; ++i)
	{
		const int size = edges[i].size();
		for (int j = 0; j < size; ++j)
		{
			if (sol->find(edges[i][j]) != sol->end()) goto noadd;
		}
		sol->insert(i);
noadd:
		continue;
	}

	helper const set<int>::iterator end = sol->end();
	for (set<int>::iterator it = sol->begin(); it != end; ++it)
	{
		solution[result++] = *it;
	}
	delete sol;
	return result;
}

void _brute_force(const int n, const int k, const int *x, const int *y, int *solution,
	const int depth, const int start, int *temp)
{
	if (depth == k)
	{
		int result = 0;
		for (int i = 0; i < n; ++i)
		{
			int dist = 1 << 30;
			for (int j = 0; j < k; ++j)
			{
				dist = min(dist, SQ(x[i] - x[temp[j]]) + SQ(y[i] - y[temp[j]]));
				debug printf("\t\t? %d->%d = %d\n", i, temp[j], SQ(x[i] - x[temp[j]]) + SQ(y[i] - y[temp[j]]));
			}
			debug printf("\tdist(%d) = %d\n", i, dist);
			result = max(result, dist);
		}

		debug
		{
			printf("??? ");
			for (int i = 0; i < k; ++i) printf("%d ", temp[i]);
			printf("-> %d\n", result);
		}

		if (result < brute_result)
		{
			brute_result = result;
			memcpy(solution, temp, k * sizeof(int));
		}
		return;
	}
	for (int i = start; i < n; ++i)
	{
		temp[depth] = i;
		_brute_force(n, k, x, y, solution, depth + 1, i + 1, temp);
	}
}
void brute_force(const int n, const int k, const int *x, const int *y, int *solution)
{
	brute_result = 1 << 30;
	int *temp = (int *)malloc(k * sizeof(int));
	_brute_force(n, k, x, y, solution, 0, 0, temp);
	free(temp);
}


/*
2
6 2
1 5
1 1
4 3
5 3
8 5
8 1

6 2
0 8
0 0
4 4
16 4
20 8
20 0


5
5 2
-3 -4
-4 3
2 -3
-2 -3
-5 5

5 4
2 0
-5 -4
1 -1
-1 0
5 -5

5 2
-3 0
5 -2
-1 -5
2 4
4 5

5 3
5 0
-1 -5
3 2
-5 1
-1 3

5 4
-1 2
1 1
5 4
0 5
-2 2

*/