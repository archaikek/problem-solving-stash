#include "dp_functions.h"

static int _n, _m, _k;

// PROCESS DOWN
static inline void process_dot_down(solution_t *prev_col, solution_t *curr_col, const int k)
{
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


void generate_solution(char **board, solution_t ***dp, const int n, const int m, const int k)
{
	for (int i = 1; i <= n; ++i)
	{
		helper solution_t **prev_row = dp[i - 1];
		helper solution_t **curr_row = dp[i];

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