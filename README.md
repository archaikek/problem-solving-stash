# problem-solving-stash
Repository for codes for competitive programming problem solving and similar.

Different branches contain solutions for different problems, which will be linked in their respective readmes. 

## tpikies-gold-mine
This branch contains the solution for the tpikies_GOLD_MINE task, available at https://stos.eti.pg.gda.pl/index.php?p=show&pid=1551&cid=712 (the link will most likely be unavailable to external users).

### Solution
Use dynamic programming indexed dp[row][column][walls destroyed up to this point][direction this point was reached from] with intial state of dp[n][m][k][dir] being 0 for the starting point of the S tile, and -infinity for every other spot (the code includes some index shifting for simplicity of implementation). dp cell with the highest number is the ending point of the machine's path, and following its neighbours with results 0 or 1 smaller (including their directions) one can recreate the path that gave this result.
