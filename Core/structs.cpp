#include "structs.h"

// this is intentionally inverted so that std::set puts the highest results first
bool operator<(const result_t &a, const result_t &b) 
{
	if (a.result == b.result) return a.cost < b.cost;
	return a.result > b.result;
}

std::set<result_t> ***create_results(const int n, const int m)
{
	std::set<result_t> ***results = (std::set<result_t> ***)malloc(sizeof(std::set<result_t> **) * (n + 1)); // 1-indexed for consistency
	
	for (int i = 0; i <= n; ++i)
	{
		std::set<result_t> **result = results[i] = (std::set<result_t> **)malloc(sizeof(std::set<result_t> *) * (m + 2)); // 1 column of padding on both sides
		for (int j = 0; j <= m + 1; ++j)
		{
			result[j] = new std::set<result_t>();
		}
	}

	return results;
}
void delete_results(std::set<result_t> ***results, const int n, const int m)
{
	for (int i = 0; i <= n; ++i)
	{
		std::set<result_t> **result = results[i];
		for (int j = 0; j <= m + 1; ++j)
		{
			delete result[j];
		}
		free(result);
	}
	free(results);
}

char **create_board(const int n, const int m)
{
	char **board = (char **)malloc(sizeof(char *) * (n + 1));

	for (int i = 0; i <= n; ++i)
	{
		char *row = board[i] = (char *)malloc(sizeof(char) * (m + 2));
	}
}
void delete_board(char **board, const int n, const int m)
{
	for (int i = 0; i <= n; ++i)
	{
		free(board[i]);
	}
	free(board);
}