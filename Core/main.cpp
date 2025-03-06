#include "common_defines.h"
#include "fast_io.h"
#include "structs.h"

#include <cstdlib>

int main()
{
	int n, m, k, mode;
	int start_col;
	scanf("%d%d%d", &k, &n, &m);
	
	char **board = create_board(n, m);
	std::set<result_t> ***results = create_results(n, m);

	helper char *start_row = board[1];
	for (int j = 1; j <= m; ++j)
	{
		board[1][j] = getchar();
		if (board[1][j] == 'S') start_col = j;
	}
	return 0;
}