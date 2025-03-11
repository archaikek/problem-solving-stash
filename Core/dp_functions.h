#pragma once
#include "common_defines.h"
#include "structs.h"

void generate_solution(char **board, solution_t ***dp, const int n, const int m, const int k);
int backtrack(char **board, solution_t ***dp, const int n, const int m, const int k);