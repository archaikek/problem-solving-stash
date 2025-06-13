#pragma once
#include "common_defines.h"
#include "structs.h"
#include <algorithm>

void generate_solution(char **board, solution_t ***dp, const int n, const int m, const int k);
int backtrack(char **board, solution_t ***dp, const int n, const int m, const int k);

void run_brute_force(char **board, const int n, const int m, const int k);