#include "structs.h"

graph_t *create_graph(const int size)
{
	graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
	graph->size = size;
	graph->edges = new vector<int>[size];
	return graph;
}
void delete_graph(graph_t *graph)
{
	delete[] graph->edges;
	free(graph);
}

graph_t *create_squared_graph(const graph_t *base, const ii *lengths, const int cutoff)
{
	const int n = base->size;
	graph_t *graph = create_graph(n);

	for (int i = 0; i <= cutoff; ++i) add_edge(graph, lengths[i].ss % n, lengths[i].ss / n);

	return graph;
}