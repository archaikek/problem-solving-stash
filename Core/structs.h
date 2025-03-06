#pragma once
#include <set>

typedef enum
{
	UP = 0,
	LEFT = 1,
	RIGHT = 2
} direction_t;

typedef struct
{
	int result, cost;
	direction_t dir;
} result_t;
bool operator<(const result_t &a, const result_t &b);

std::set<result_t> ***create_results(const int n, const int m);
void delete_results(std::set<result_t> ***results, const int n, const int m);

char **create_board(const int n, const int m);
void delete_board(char **board, const int n, const int m);
