#include "structs.h"

// this is intentionally inverted so that std::set puts the highest results first
bool operator<(const result_t &a, const result_t &b) 
{
	if (a.result == b.result) return a.cost < b.cost;
	return a.result > b.result;
}