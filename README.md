# problem-solving-stash
Repository for codes for competitive programming problem solving and similar.

Different branches contain solutions for different problems, which will be linked in their respective readmes. 

## spoj-ms2025-webisl
Branch for the solution of the Web islands problem at https://www.spoj.com/MS2025/problems/WEBISL/ (which is probably unavailable to outsiders)

### Solution
Use Tarjan's algorithm to find strongly connected components in the graph, and then a find-and-union-like approach to reindex them to the lowest index of a node in a given SCC