#include "common_defines.h"
#include "fast_io.h"
#include "structs.h"
#include "dp_functions.h"

#include <cstdlib>

int main()
{
	int n, m, k, mode;
	readUI(&k);
	readUI(&n);
	readUI(&m);
	
	char **board = create_board(n, m);
	int ***dp = create_dp(k, n, m);

	for (int i = 1; i <= n; ++i)
	{
		readS(board[i] + 1);
	}
	readUI(&mode);

	generate_solution(board, dp, k, n, m);
	debug print_dp(dp, k, n, m);

	print_board(board, n, m);

	delete_dp(dp, k, n, m);
	delete_board(board, n, m);
	return 0;
}

/*
2
4 7
...@S@@
...@@@@
....@..
....@..
1
*/