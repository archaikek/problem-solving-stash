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

		/*
		Zauważmy, że odległością między najdalszymi dwoma punktami w dowolnym rozwiązaniu jest krawędź między nimi;
		będziemy chcieli uporzadkować te krawędzie od najkrótszej do najdłuższej i spróbować znaleźć tę, która
		faktycznie będzie tą najdłuższą wyznaczajacą jakość rozwiązania.
		*/
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

		//if (true)
		if (argc > 1 && strcmp(argv[1], "-brute") == 0)
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
		else if (n <= 2)
		{
			printf("case %d Y\n0 \n", t + 1);
		}
		else
		{
			/*
			Zastosujemy bisekcję w celu znalezienia poszukiwanej krawędzi - jest ich O(n^2), stąd badanie rozwiązania
			będziemy wykonywali O(log^2 n) razy. 
			Samo poszukiwanie będzie przebiegało w następujący sposób: po wybraniu krawędzi odrzucimy wszystkie
			krawędzie większe od niej, i w tak pomniejszonym grafie będziemy chcieli znaleźć zbiór dominujący
			o rozmiarze co najwyżej k - jeśli taki znajdziemy, to z definicji będzie on sąsiadował z każdym innym
			wierzchołkiem w grafie, a te z konstrukcji grafu będą w odległości nie większej niż badana krawędź.
			*/
			int left = 0, right = m; // right - first outside the table
			int *solution = (int *)malloc(k * sizeof(int));
			int *temp_solution = (int *)malloc(n * sizeof(int));
			while (true)
			{
				/*
				Pomysł: Stwórzmy "kwadrat" grafu, czyli graf z tymi samymi wierzchołkami, ale do zbioru sąsiadów
				każdego wierzchołka v dodamy również sąsiadów sąsiadów v. Wówczas zbiór sąsiadów v w wyjściowym
				grafie będzie tworzył klikę w kwadracie tego grafu.
				Teraz zauważmy, że mając pewien zbiór dominujacy o rozmiarze d w wyjściowym grafie, kwadrat grafu
				będziemy mogli pokryć d klikami (ponieważ zbiór sąsiadów każdego z tych d wierzchołków tworzy własną
				klikę). Oznacza to, że w dowolnym zbiorze niezależnym w kwadracie grafu z każdej takiej kliki 
				znajdzie się co najwyżej 1 wierzchołek. Stąd obserwacja, że dowolny zbiór niezależny 
				w kwadracie	grafu będzie niewiększy od dowolnego zbioru dominującego w wyjściowym grafie.
				Ponadto dowolny maksymalny zbiór niezależny sam w sobie jest zbiorem dominującym tego grafu.
				Łącząc te obserwacje otrzymujemy, że dowolny maksymalny zbiór niezależny w kwadracie grafu
				stworzy nam pewne rozwiązanie w grafie wyjściowym o tym samym rozmiarze. W kwadracie grafu
				jest to zbiór dominujący, a tym samym w wyjściowym grafie każdy wierzchołek będzie od tego zbioru
				oddalony o co najwyżej dwie krawędzie. Z konstrukcji grafu wiemy, jakiej długości jest najdłuższa
				jego krawędź, stąd według tego rozwiązania, korzystając z nierówności trójkąta, faktyczne rozwiązanie
				będzie co najwyżej dwukrotnie gorsze. Ponieważ każdy zbiór niezależny w kwadracie grafu jest
				niewiększy od każdego zbioru dominującego w grafie wyjściowym, na pewno nie istnieje zbiór dominujący
				rozmiaru co najwyżej k w grafie, w którego kwadracie nie jesteśmy w stanie skonstruować maksymalnego
				zbioru niezależnego o rozmiarze co najwyżej k, qed.
				*/
				int mid = (left + right) / 2; // mid - first outside the left half <==> first in the right half
				graph_t *squared = create_squared_graph(graph, lengths, mid);

				int result = find_independent_set(squared, temp_solution);
				delete_graph(squared);

				debug printf("??? (%d, %d) -> %d\n", left, right, result);

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
					if (left == right - 1) break;
					right = mid;
				}
				else // solution not found, look for something bigger
				{
					if (left == right - 1) break;
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

/*
Zgodnie z twierdzeniem, każdy maksymalny zbiór niezależny w grafie jest również zbiorem dominującym. Możemy go zatem
wyszukać w sposób zachłanny - wybieramy kolejne wierzchołki v i patrzymy, czy żaden z sąsiadów v nie znajduje się
już w naszym zbiorze niezależnym. Jeśli nie, to dodajemy v do zbioru niezależnego.
*/
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