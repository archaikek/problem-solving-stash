#include "dp_functions.h"

static int _n, _m, _k;
// utility
int *copy_row(int *row, const int m)
{
	int *new_row = (int *)malloc(sizeof(int) * (m + 2));
	for (int i = 0; i <= m + 1; ++i) new_row[i] = row[i];
	return new_row;
}
int **copy_wall(int **wall, const int k, const int m)
{
	int **new_wall = (int **)malloc(sizeof(int) * (k + 2));
	for (int i = 0; i <= k + 1; ++i) new_wall[i] = copy_row(wall[i], m);
	return new_wall;
}


void move_down(char *line, int **prev_wall, int **curr_wall, const int k, const int m)
{
	helper int *prev_row_minus = prev_wall[0];
	helper int *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper int *prev_row = prev_wall[i];
		helper int *curr_row = curr_wall[i];

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
				curr_row[j] = 0;
				break;
			case '.':
				curr_row[j] = std::max(prev_row[j] + 1, curr_row_minus[j]);
				break;
			case '@':
				curr_row[j] = std::max(prev_row_minus[j], curr_row_minus[j]);
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		prev_row_minus = prev_row;
		curr_row_minus = curr_row;
	}
}
void move_right(char *line, int **curr_wall, const int k, const int m)
{
	helper int *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper int *curr_row = curr_wall[i];
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
				curr_row[j] = 0;
				break;
			case '.':
				curr_row[j] = std::max(curr_row[j - 1] + 1, curr_row[j]);
				break;
			case '@':
				curr_row[j] = std::max(curr_row_minus[j - 1], curr_row[j]);
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		curr_row_minus = curr_row;
	}
}
void move_left(char *line, int **curr_wall, const int k, const int m)
{
	helper int *curr_row_minus = curr_wall[0];
	for (int i = 1; i <= k + 1; ++i)
	{
		debug _k = i;
		helper int *curr_row = curr_wall[i];
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
				curr_row[j] = 0;
				break;
			case '.':
				curr_row[j] = std::max(curr_row[j + 1] + 1, curr_row[j]);
				break;
			case '@':
				curr_row[j] = std::max(curr_row_minus[j + 1], curr_row[j]);
				break;
			}
			debug printf("%d\n", curr_row[j]);
		}

		curr_row_minus = curr_row;
	}
}

void process_wall(char *line, int **prev_wall, int **curr_wall, const int k, const int m)
{
	move_down(line, prev_wall, curr_wall, k, m);

	int **curr_wall_copy = copy_wall(curr_wall, k, m);
	move_right(line, curr_wall, k, m);
	move_left(line, curr_wall_copy, k, m);
	for (int i = 1; i <= k + 1; ++i)
	{
		helper int *row = curr_wall[i];
		helper int *row_copy = curr_wall_copy[i];
		for (int j = 1; j <= m; ++j)
		{
			row[j] = std::max(row[j], row_copy[j]);
		}
	}

	for (int i = 0; i <= k + 1; ++i)
	{
		free(curr_wall_copy[i]);
	}
	free(curr_wall_copy);
}
void generate_solution(char **board, int ***dp, const int k, const int n, const int m)
{
	helper int **prev_wall = dp[0];
	for (int i = 1; i <= n; ++i)
	{
		debug _n = i;
		helper int **curr_wall = dp[i];
		helper char *line = board[i];
		debug printf("??? %s\n", line);
		process_wall(line, prev_wall, curr_wall, k, m);

		prev_wall = curr_wall;
	}
}