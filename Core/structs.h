#pragma once
#include "common_defines.h"
#include "fast_io.h"
#include <set>

#define INF (1<<31)

typedef struct
{
	int down, left, right;
} solution_t;
bool operator<(const solution_t &a, const solution_t &b);

int solution_max(const solution_t sol);

solution_t ***create_dp(const int k, const int n, const int m);
void delete_dp(solution_t ***dp, const int k, const int n, const int m);

char **create_board(const int n, const int m);
void delete_board(char **board, const int n, const int m);

void print_dp(solution_t ***dp, const int k, const int n, const int m);
void print_board(char **board, const int n, const int m);

