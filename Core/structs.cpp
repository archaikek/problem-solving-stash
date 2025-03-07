#include "structs.h"

int ***create_dp(const int k, const int n, const int m)
{
	int ***dp = (int ***)malloc(sizeof(int **) * (k + 2)); // padding on wall_count = 0
	for (int i = 0; i <= k + 1; ++i)
	{
		helper int **wall = dp[i] = (int **)malloc(sizeof(int *) * (n + 1)); // padding on row = 0
		for (int j = 0; j <= n; ++j)
		{
			helper int *row = wall[j] = (int *)calloc(m + 2, sizeof(int));
		}
	}

	// all results on wall_count = 0 should be illegal
	helper int **wall0 = dp[0];
	for (int i = 0; i <= n; ++i)
	{
		helper int *row = wall0[i];
		for (int j = 0; j <= m; ++j)
		{
			row[j] = INF;
		}
	}

	// all results on row = 0 should be illegal
	for (int i = 0; i <= k + 1; ++i)
	{
		helper int *row = dp[i][0];
		for (int j = 0; j <= m + 1; ++j)
		{
			row[j] = INF;
		}
	}

	// all results on columns 0 and m + 1 should be illegal
	for (int i = 0; i <= k + 1; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			dp[i][j][0] = dp[i][j][m + 1] = INF;
		}
	}

	return dp;
}
void delete_dp(int ***dp, const int k, const int n, const int m)
{
	for (int i = 0; i <= k; ++i)
	{
		helper int **wall = dp[i];
		for (int j = 0; j <= n; ++j)
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
		board[i] = (char *)malloc(sizeof(char) * (m + 2));
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