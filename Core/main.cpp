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
	solution_t ***dp = create_dp(n, m, k);

	for (int i = 1; i <= n; ++i)
	{
		readS(board[i] + 1);
	}
	readUI(&mode);

	generate_solution(board, dp, n, m, k);
	debug print_dp(dp, n, m, k);

	int result = backtrack(board, dp, n, m, k);

	write(result);
	_putchar('\n');
	if (mode == 1) print_board(board, n, m);

	delete_dp(dp, n, m, k);
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