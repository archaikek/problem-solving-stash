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

int int_max(const int a, const int b);
int solution_max(const solution_t sol, const char dir);
char get_solution_direction(const solution_t sol, const int curr_result, const char curr_dir);

solution_t ***create_dp(const int n, const int m, const int k);
void delete_dp(solution_t ***dp, const int n, const int m, const int k);

char **create_board(const int n, const int m);
void delete_board(char **board, const int n, const int m);

void print_solution(const solution_t sol);
void print_dp(solution_t ***dp, const int n, const int m, const int k);
void print_board(char **board, const int n, const int m);

