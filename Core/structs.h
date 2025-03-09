#pragma once
#include "common_defines.h"
#include <set>

#define INF (1<<31)

int ***create_dp(const int k, const int n, const int m);
void delete_dp(int ***dp, const int k, const int n, const int m);

char **create_board(const int n, const int m);
void delete_board(char **board, const int n, const int m);

void print_dp(int ***dp, const int k, const int n, const int m);
