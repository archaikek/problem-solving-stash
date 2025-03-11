#include "structs.h"

int int_max(const int a, const int b)
{
	return (a > b ? a : b);
}
int solution_max(const solution_t sol, const char dir)
{
	switch (dir)
	{
	case 'L':
		return int_max(sol.down, sol.right);
	case 'R':
		return int_max(sol.down, sol.left);
	default:
		return int_max(sol.down, int_max(sol.left, sol.right));
	}
}
char get_solution_direction(const solution_t sol, const int curr_result, const char curr_dir)
{
	switch (curr_dir)
	{
	case 'L':
		if (sol.right == curr_result) return 'L';
		else return 'U';
		break;
	case 'R':
		if (sol.left == curr_result) return 'R';
		else return 'U';
		break;
	default:
		if (sol.right == curr_result) return 'L';
		else if (sol.left == curr_result) return 'R';
		else return 'U';
	}
}

solution_t ***create_dp(const int n, const int m, const int k)
{
	solution_t ***dp = (solution_t ***)malloc(sizeof(solution_t **) * (n + 1)); // padding on row = 0
	for (int i = 0; i <= n; ++i)
	{
		helper solution_t **row = dp[i] = (solution_t **)malloc(sizeof(solution_t *) * (m + 2)); // padding on col = 0 and col = m + 1
		for (int j = 0; j <= m + 1; ++j)
		{
			helper solution_t *col = row[j] = (solution_t *)malloc(sizeof(solution_t) * (k + 2)); // padding on wall = 0
			for (int l = 0; l <= k + 1; ++l) col[l] = { INF, INF, INF };
		}
	}

	return dp;
}
void delete_dp(solution_t ***dp, const int n, const int m, const int k)
{
	for (int i = 0; i <= n; ++i)
	{
		helper solution_t **row = dp[i];
		for (int j = 0; j <= m + 1; ++j)
		{
			free(row[j]);
		}
		free(row);
	}
	free(dp);
}

char **create_board(const int n, const int m)
{
	char **board = (char **)malloc(sizeof(char *) * (n + 1));

	for (int i = 0; i <= n; ++i)
	{
		board[i] = (char *)calloc(m + 2, sizeof(char));
	}
	return board;
}
void delete_board(char **board, const int n, const int m)
{
	for (int i = 0; i <= n; ++i)
	{
		free(board[i]);
	}
	free(board);
}

void print_solution(const solution_t sol)
{
	if (sol.down < 0) printf("-/");
	else printf("%d/", sol.down);

	if (sol.left < 0) printf("-/");
	else printf("%d/", sol.left);

	if (sol.right < 0) printf("-\t");
	else printf("%d\t", sol.right);
}
void print_dp(solution_t ***dp, const int n, const int m, const int k)
{
	for (int i = 0; i <= k + 1; ++i)
	{
		printf("wall %d:\n", i);
		for (int j = 0; j <= n; ++j)
		{
			for (int l = 0; l <= m + 1; ++l)
			{
				print_solution(dp[j][l][i]);
			}
			printf("\n");
		}
		printf("\n");
	}
}
void print_board(char **board, const int n, const int m)
{
	for (int i = 1; i <= n; ++i)
	{
		writeS(board[i] + 1);
		_putchar('\n');
	}
}