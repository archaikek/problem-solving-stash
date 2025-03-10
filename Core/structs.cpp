#include "structs.h"

int ***create_dp(const int k, const int n, const int m)
{
	int ***dp = (int ***)malloc(sizeof(int **) * (n + 1)); // padding on row = 0
	for (int i = 0; i <= n; ++i)
	{
		helper int **wall = dp[i] = (int **)malloc(sizeof(int *) * (k + 2)); // padding on wall = 0
		for (int j = 0; j <= k + 1; ++j)
		{
			helper int *row = wall[j] = (int *)malloc(sizeof(int) * (m + 2)); // padding on column = 0 and column = m + 1
			for (int l = 0; l <= m + 1; ++l) row[l] = INF;
		}
	}

	return dp;
}
void delete_dp(int ***dp, const int k, const int n, const int m)
{
	for (int i = 0; i <= n; ++i)
	{
		helper int **wall = dp[i];
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

void print_dp(int ***dp, const int k, const int n, const int m)
{
	for (int i = 0; i <= k + 1; ++i)
	{
		printf("wall %d:\n", i);
		for (int j = 0; j <= n; ++j)
		{
			helper int *row = dp[j][i];
			for (int l = 0; l <= m + 1; ++l)
			{
				if (row[l] < 0) printf("- ");
				else printf("%d ", row[l]);
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