#include "dp_functions.h"

static int _n, _m, _k;

// PROCESS DOWN
static inline void process_dot_down(solution_t *prev_col, solution_t *curr_col, const int k)
{
	/* 
	Rozwiązania indeksowane <0; k+1>; i oznacza, że do uzyskania tego rozwiązania wykorzystano
	__ściśle mniej__ niż i pzrebitych ścian (tj. i=1 oznacza brak przebitych ścian, i=5 oznacza
	najlepszy wynik z wykorzystaniem od 0 do 4 przebitych ścian). 0 jest zarezerwowane dla
	niepoprawnych wyników.
	*/
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].down = int_max(curr_col[i - 1].down, solution_max(prev_col[i], 'U') + 1);
	}
}
static inline void process_at_down(solution_t *prev_col, solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].down = int_max(curr_col[i - 1].down, solution_max(prev_col[i - 1], 'U'));
	}
}
static inline void process_s_down(solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].down = 0;
	}
}

// PROCESS RIGHT
static inline void process_dot_right(solution_t *prev_col, solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].right = int_max(curr_col[i - 1].right, solution_max(prev_col[i], 'L') + 1);
	}
}
static inline void process_at_right(solution_t *prev_col, solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].right = int_max(curr_col[i - 1].right, solution_max(prev_col[i - 1], 'L'));
	}
}
static inline void process_s_right(solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].right = 0;
	}
}

// PROCESS LEFT
inline void process_dot_left(solution_t *prev_col, solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].left = int_max(curr_col[i - 1].left, solution_max(prev_col[i], 'R') + 1);
	}
}
inline void process_at_left(solution_t *prev_col, solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].left = int_max(curr_col[i - 1].left, solution_max(prev_col[i - 1], 'R'));
	}
}
inline void process_s_left(solution_t *curr_col, const int k)
{
	for (int i = 1; i <= k + 1; ++i)
	{
		curr_col[i].left = 0;
	}
}

/*
Rozwiązanie z użyciem programowania dynamicznego w złożoności O(NMK), gdzie N - liczba wierszy, M - liczba
kolumn, K - największa możliwa liczba skał do przebicia.

Korzystając z faktu, że po planszy można się poruszać jedynie w dół i na boki, optymalny wynik z wcześniejsych
wierszy można bez strat przenieść do kolejnych pod warunkiem, że będziemy utrzymywać po drodze informację
o wykorzystanych dotychczas przebitych ścianach (co jest załatwiane dodatkowym wymiarem w tablicy DP). Ponadto
w obrębie wiersza zabraniamy cofania się, stąd możemy przetworzyć wiersz od lewej do prawej niezależnie
od przetworzenia go od prawej do lewej, korzystając jedynie z wyników cząstkowych bazujących na wynikach
z poprzedniego wiersza (ruch w dół) oraz z poprzednich kolumn zgodnie z kierunkiem przetwarzania (ruchy w lewo
oraz w prawo).
*/
void generate_solution(char **board, solution_t ***dp, const int n, const int m, const int k)
{
	/* wiersze planszy indeksowane <0; n>; 0 jest zarezerwowane dla niepoprawnych wyników */
	for (int i = 1; i <= n; ++i)
	{
		helper solution_t **prev_row = dp[i - 1];
		helper solution_t **curr_row = dp[i];

		/* kolumny planszy indeksowane <0; m+1>; 0 i m+1 zarezerwowane dla niepoprawnych wyników */
		// move down
		for (int j = 1; j <= m; ++j)
		{
			helper solution_t *prev_col = prev_row[j];
			helper solution_t *curr_col = curr_row[j];
			switch (board[i][j])
			{
			case '.':
				process_dot_down(prev_col, curr_col, k);
				break;
			case '@':
				process_at_down(prev_col, curr_col, k);
				break;
			case 'S':
				process_s_down(curr_col, k);
				break;
			}
		}

		// move right
		for (int j = 1; j <= m; ++j)
		{
			helper solution_t *prev_col = curr_row[j - 1];
			helper solution_t *curr_col = curr_row[j];
			switch (board[i][j])
			{
			case '.':
				process_dot_right(prev_col, curr_col, k);
				break;
			case '@':
				process_at_right(prev_col, curr_col, k);
				break;
			case 'S':
				process_s_right(curr_col, k);
				break;
			}
		}

		// move left
		for (int j = m; j >= 0; --j)
		{
			helper solution_t *prev_col = curr_row[j + 1];
			helper solution_t *curr_col = curr_row[j];
			switch (board[i][j])
			{
			case '.':
				process_dot_left(prev_col, curr_col, k);
				break;
			case '@':
				process_at_left(prev_col, curr_col, k);
				break;
			case 'S':
				process_s_left(curr_col, k);
				break;
			}
		}
	}
}

/*
Funkcja ta służy do odtworzenia trasy generującej znalezionej przez powyższy algorytm programowania dynamicznego
wyniku.
*/
int backtrack(char **board, solution_t ***dp, const int n, const int m, const int k)
{
	int _n, _m, _k = k + 1, curr_result = -1;
	// find the location of the best result
	for (int i = 1; i <= n; ++i)
	{
		helper solution_t **row = dp[i];
		for (int j = 1; j <= m; ++j)
		{
			helper int result = solution_max(row[j][_k], 'U');
			if (result > curr_result)
			{
				curr_result = result;
				_n = i;
				_m = j;
			}
		}
	}
	int result = curr_result;

	char dir = 'U';
	while (board[_n][_m] != 'S')
	{
		dir = get_solution_direction(dp[_n][_m][_k], curr_result, dir);

		debug
		{
			solution_t sol = dp[_n][_m][_k];
			printf("%c: [%d, %d, %d] -> ", dir, _n, _m, _k);
			print_solution(sol);
			_putchar('\n');
		}
		
		if (board[_n][_m] == '.') --curr_result;
		else --_k;
		board[_n][_m] = dir;

		switch (dir)
		{
		case 'L':
			--_m;
			break;
		case 'R':
			++_m;
			break;
		case 'U':
			--_n;
			break;
		}
	}
	return result;
}


static bool visited[107][107];
static int result = 0, local_result = 0, walls_hit = -1;
static int walls_lim;

static char **board;
static int n, m, k;

static void dfs(const int row, const int col)
{
	if (walls_hit > walls_lim) return;
	visited[row][col] = true;
	if (board[row][col] == '.') ++local_result;
	else ++walls_hit;
	//printf("? checking (%d, %d) standing on %c; local_result = %d, result = %d; walls hit: %d/%d\n", row, col, board[row][col], local_result, result, walls_hit, walls_lim);

	result = std::max(result, local_result);
	if (local_result > result) return;
	if (!visited[row][col - 1]) dfs(row, col - 1);
	if (!visited[row][col + 1]) dfs(row, col + 1);
	if (row < n) dfs(row + 1, col);

	if (board[row][col] == '.') --local_result;
	else --walls_hit;
	visited[row][col] = false;
	//printf("exiting (%d %d)\n", row, col);
}
void run_brute_force(char **__board, const int __n, const int __m, const int __k)
{
	n = __n;
	m = __m;
	k = __k;
	board = __board;
	int start = 1;
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			visited[i][j] = false;
		}
	}
	for (int j = 1; j <= m; ++j) if (board[1][j] == 'S') start = j;
	walls_lim = k;

	dfs(1, start);
	printf("%d\n", result);
}