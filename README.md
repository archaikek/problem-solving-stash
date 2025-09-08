# problem-solving-stash
Repository for codes for competitive programming problem solving and similar.

Different branches contain solutions for different problems, which will be linked in their respective readmes. 

## tpikies-mm-shelters
Solution of the problem 'tpikies_mm_shelters' from https://stos.eti.pg.gda.pl/index.php?p=show&pid=1556&cid=712. The contest will most likely be unavailable to outsiders.

### Solution
Convert the points and their coordinates into a fully-connected graph, where each vertex corresponds to each point on the plane, and the edges are weighted by the distance between the two points. Sort the edges by weight and start selecting them by bisection. 

After selecting an edge, temporarily remove all heavier edges from the graph, and check if the remaining graph contains a dominating set of size at most k - by definition this set will neighbour with every other vertex in the graph, and by construction all the distances will be no greater than the selected edge. 

Since this is a hard task, for each vertex extend its neighbour set to include the neighbours of its neighbours, so that in the newly made graph each vertex neighbours with other vertices, if in the original graph they were neighbours or had a common neighbour. In this extended graph look for a maximal independent set of size at most k. *Note: this neighbour set extension effectively means that for each vertex, it and its original neighbour set create a clique in the new graph. This means that if the original graph had a dominating set of size k, the extended graph is covered by k cliques, and thus __no__ maximal independent set may contain more than that many vertices.*

Finding any such independent set in an extended graph is a proof that a dominating set of size at most k exists, and therefore guarantees that the independent set gives a solution no greater than twice the optimal solution.

Note: since we begin with a fully-connected graph, cutting the edges off at double the considered solution produces a graph that retains all those useful properties (if we consider some cutoff weight w, the extended graph from cutoff w will be a subgraph of another graph made from cutoff 2w without the extension), so a simple bisection in search of a graph with a maximal independent set of size at most k will also produce a 2-apx solution.