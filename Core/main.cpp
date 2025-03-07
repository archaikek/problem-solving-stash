#include "common_defines.h"
#include "fast_io.h"
#include "structs.h"

#include <cstdlib>

int main()
{
	int n, m, k, mode;
	int start_col;
	readUI(&k);
	readUI(&n);
	readUI(&m);
	
	char **board = create_board(n, m);
	int ***dp = create_dp(k, n, m);

	debug
	{
		for (int i = 0; i <= k + 1; ++i)
		{
			printf("wall %d:\n", i);
			helper int **wall = dp[i];
			for (int j = 0; j <= n; ++j)
			{
				helper int *row = wall[j];
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

	helper char *start_row = board[1];
	for (int j = 1; j <= m; ++j)
	{
		board[1][j] = getchar();
		if (board[1][j] == 'S') start_col = j;
	}
	getchar();
	for (int i = 2; i <= n; ++i)
	{
		readS(board[i]);
	}
	readUI(&mode);


	delete_dp(dp, k, n, m);
	delete_board(board, n, m);
	return 0;
}