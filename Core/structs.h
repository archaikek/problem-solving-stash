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

