#include "dp_functions.h"

static int _n, _m, _k;
// utility
solution_t *copy_row(solution_t *row, const int m)
{
	solution_t *new_row = (solution_t *)malloc(sizeof(solution_t) * (m + 2));
	for (int i = 0; i <= m + 1; ++i) new_row[i] = row[i];
	return new_row;
}
solution_t **copy_wall(solution_t **wall, const int k, const int m)
{
	solution_t **new_wall = (solution_t **)malloc(sizeof(solution_t) * (k + 2));
	for (int i = 0; i <= k + 1; ++i) new_wall[i] = copy_row(wall[i], m);
	return new_wall;
}


void move_down(char *line, solution_t **prev_wall, solution_t **curr_wall, const int k, const int m)
{
	helper solution_t *prev_row_minus = prev_wall[0];
	helper solution_t *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper solution_t *prev_row = prev_wall[i];
		helper solution_t *curr_row = curr_wall[i];

		for (int j = 1; j <= m; ++j)
		{
			debug
			{
				_m = j;
			printf("%c: [%d, %d, %d] %d -> ", line[j], _n, _k, _m, curr_row[j]);
			}
			switch (line[j])
			{
			case 'S':
				curr_row[j].down = 0;
				break;
			case '.':
				curr_row[j].down = std::max(solution_max(prev_row[j]) + 1, solution_max(curr_row_minus[j]));
				break;
			case '@':
				curr_row[j].down = std::max(solution_max(prev_row_minus[j]), solution_max(curr_row_minus[j]));
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		prev_row_minus = prev_row;
		curr_row_minus = curr_row;
	}
}
void move_right(char *line, solution_t **curr_wall, const int k, const int m)
{
	helper solution_t *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper solution_t *curr_row = curr_wall[i];
		for (int j = 1; j <= m; ++j)
		{
			debug
			{
				_m = j;
			printf("%c: [%d, %d, %d] %d -> ", line[j], _n, _k, _m, curr_row[j]);
			}
			switch (line[j])
			{
			case 'S':
				curr_row[j].right = 0;
				break;
			case '.':
				curr_row[j].right = std::max(solution_max(curr_row[j - 1]) + 1, solution_max(curr_row[j]));
				break;
			case '@':
				curr_row[j].right = std::max(solution_max(curr_row_minus[j - 1]), solution_max(curr_row[j]));
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		curr_row_minus = curr_row;
	}
}
void move_left(char *line, solution_t **curr_wall, const int k, const int m)
{
	helper solution_t *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper solution_t *curr_row = curr_wall[i];
		for (int j = m; j >= 0; --j)
		{
			debug
			{
				_m = j;
			printf("%c: [%d, %d, %d] %d -> ", line[j], _n, _k, _m, curr_row[j]);
			}
			switch (line[j])
			{
			case 'S':
				curr_row[j].left = 0;
				break;
			case '.':
				curr_row[j].left = std::max(solution_max(curr_row[j + 1]) + 1, solution_max(curr_row[j]));
				break;
			case '@':
				curr_row[j].left = std::max(solution_max(curr_row_minus[j + 1]), solution_max(curr_row[j]));
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		curr_row_minus = curr_row;
	}
}

void process_wall(char *line, solution_t **prev_wall, solution_t **curr_wall, const int k, const int m)
{
	move_down(line, prev_wall, curr_wall, k, m);

	solution_t **curr_wall_copy = copy_wall(curr_wall, k, m);
	move_right(line, curr_wall, k, m);
	move_left(line, curr_wall_copy, k, m);
	for (int i = 1; i <= k + 1; ++i)
	{
		helper solution_t *row = curr_wall[i];
		helper solution_t *row_copy = curr_wall_copy[i];
		for (int j = 1; j <= m; ++j)
		{
			row[j] = std::max(row[j], row_copy[j]);
		}
	}

	for (int i = 0; i <= k + 1; ++i)
	{
		free(curr_wall_copy[i]);
	}
	//free(curr_wall_copy); guh??
}
void generate_solution(char **board, solution_t ***dp, const int k, const int n, const int m)
{
	helper solution_t **prev_wall = dp[0];
	for (int i = 1; i <= n; ++i)
	{
		debug _n = i;
		helper solution_t **curr_wall = dp[i];
		helper char *line = board[i];
		debug printf("??? %s\n", line);
		process_wall(line, prev_wall, curr_wall, k, m);

		prev_wall = curr_wall;
	}
}