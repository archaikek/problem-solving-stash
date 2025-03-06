#include "common_defines.h"
#include "fast_io.h"
#include "structs.h"

#include <cstdlib>

int main()
{
	int n, m, k, mode;
	int start_row, start_col;
	scanf("%d%d%d", &k, &n, &m);
	
	char **board = (char **)malloc(sizeof(char *) * (n + 1)); // have the tables 1-indexed
	for (int i = 0; i < n; ++i)
	{
		board[i] = (char *)malloc(sizeof(char) * (m + 2));

	}
	return 0;
}