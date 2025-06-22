#pragma once
#include "common_defines.h"
#include <vector>
#include <set>

typedef struct
{
	int size;
	vector<int> *edges;
} graph_t;

graph_t *create_graph(const int size);
void delete_graph(graph_t *graph);

inline void add_edge(graph_t *graph, const int src, const int dst)
{
	graph->edges[src].eb(dst);
	graph->edges[dst].eb(src);
}

graph_t *create_squared_graph(const graph_t *base, const ii *lengths, const int cutoff);