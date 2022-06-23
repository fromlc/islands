# islands

Given a 2D array map of 1 cells (island) and 0 cells (ocean), count the contiguous islands.
A 1 cell belongs to an island iff it is a vertical or horizontal neighbor to another 1 cell.

## Method: 2 passes

### Pass 1: Approximate total island count as the sum of all row island counts.

- Build shadow array `id` so each horizontally contiguous 1 cell has same id.
- DEBUG only array `rowtotal[MAP_ROWS]` holds count of islands in that row.

For example: `map[0] = {1,0,1,1,0,1} => id[0] = {1,0,2,2,0,3}, rowtotal[0] = 3.`

### Pass 2: Examine each island in row.

- If any non-zero cell id has a non-zero neighbor above, decrement island total for each new row island neighbor.
