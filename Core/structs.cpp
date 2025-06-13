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
	delete graph->edges;
	free(graph);
}