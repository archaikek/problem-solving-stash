#include "structs.h"

bool operator<(const solution_t &a, const solution_t &b)
{
	return solution_max(a) < solution_max(b);
}

int solution_max(const solution_t sol)
{
	return std::max(sol.down, std::max(sol.left, sol.right));
}

solution_t ***create_dp(const int k, const int n, const int m)
{
	solution_t ***dp = (solution_t ***)malloc(sizeof(solution_t **) * (n + 1)); // padding on row = 0
	for (int i = 0; i <= n; ++i)
	{
		helper solution_t **wall = dp[i] = (solution_t **)malloc(sizeof(solution_t *) * (k + 2)); // padding on wall = 0
		for (int j = 0; j <= k + 1; ++j)
		{
			helper solution_t *row = wall[j] = (solution_t *)malloc(sizeof(solution_t) * (m + 2)); // padding on column = 0 and column = m + 1
			for (int l = 0; l <= m + 1; ++l) row[l] = { INF, INF, INF };
		}
	}

	return dp;
}
void delete_dp(solution_t ***dp, const int k, const int n, const int m)
{
	for (int i = 0; i <= n; ++i)
	{
		helper solution_t **wall = dp[i];
		for (int j = 0; j <= k + 1; ++j)
		{
			free(wall[j]);
		}
		free(wall);
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

void print_dp(solution_t ***dp, const int k, const int n, const int m)
{
	for (int i = 0; i <= k + 1; ++i)
	{
		printf("wall %d:\n", i);
		for (int j = 0; j <= n; ++j)
		{
			helper solution_t *row = dp[j][i];
			for (int l = 0; l <= m + 1; ++l)
			{
				if (row[l].down < 0) printf("-/");
				else printf("%d/", row[l].down);

				if (row[l].left < 0) printf("-/");
				else printf("%d/", row[l].left);

				if (row[l].right < 0) printf("-\t");
				else printf("%d\t", row[l].right);
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
		writeS(board[i]);
		_putchar('\n');
	}
}