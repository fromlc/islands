/*
 * islands.c
 * 
 * Author: Linda Carver
 *
 * Created on June 14, 2018, 8:34 AM
 */
 
#define DEBUG 

#include <stdio.h>
#include <stdlib.h>

#define MAP_ROWS 3
#define MAP_COLS 6
#define ID_COLS  MAP_COLS + 1

/*   
 *   Problem statement: Given a 2D array map of 1 cells (island) and 0 cells
 *      (ocean), count the contiguous islands.
 *          A 1 cell belongs to an island iff it is a vertical or horizontal
 *          neighbor to another 1 cell.
 * 
 *   Method: 2 passes
 *      Pass 1: Build shadow array id so each horizontally contiguous 1 cell
 * 			has same id.  DEBUG only array rowtotal[MAP_ROWS] holds count of
 * 			islands in that row.
 *              Example: map[0] = {1,0,1,1,0,1} => id[0] = {1,0,2,2,0,3},
 *                                                 rowtotal[0] = 3.
 *          Approximate total islands as sum of all row island counts.
 *      Pass 2: Examine each island in row.
 *          If any non-zero cell id has a non-zero neighbor above,
 *          decrement island total for each new row island neighbor.
 *      
 */
      
int main(int argc, char** argv) {
    
// Map of islands input: 1 is island, 0 is ocean
    static const int map[MAP_ROWS][MAP_COLS] = {{1,0,1,1,0,1},{1,1,0,0,1,1},{0,1,1,1,1,0}};

// Shadow array id
    int id[MAP_ROWS][MAP_COLS] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};

// Output total island count
    int total = 0;

#ifdef DEBUG
// Track row island count
	int rowtotal[MAP_ROWS] = {0,0,0};
#endif
	
// Loop vars
    int i, j;
    
// Pass 2 neighbor id flag
	int neighbor = 0;
    
#ifdef DEBUG
// Print map array
	printf("input map array:\n");
	
    for (i = 0; i < MAP_ROWS; i++) {
        
        for (j = 0; j < MAP_COLS; j++) {
			printf("%d ", map[i][j]);
		}

		printf("\n");
	}

	printf("\n");
	printf("shadow array id after pass1:\n");
#endif
	
// Pass 1: prepare shadow array id
    for (i = 0; i < MAP_ROWS; i++) {
        
        for (j = 0; j < MAP_COLS-1; j++) {

			// on 0 -> 1 transition or row start, bump total and row island count
            if ((map[i][j] == 0 && map[i][j+1] == 1) ||
				(j == 0 && map[i][0] == 1)) {
					
                total++;
#ifdef DEBUG                
                rowtotal[i]++;
#endif                
			}
			
			// on 1, assign row island id
            if (map[i][j] == 1) {
                id[i][j] = total;
			}
			
#ifdef DEBUG
			printf("%d ", id[i][j]);
#endif	
        }

			if (map[i][MAP_COLS-1] == 1) {
				id[i][MAP_COLS-1] = total;
			}

#ifdef DEBUG
		printf("%d rowtotal=%d\n", id[i][MAP_COLS-1], rowtotal[i]);
#endif			
    }

#ifdef DEBUG
	printf("\npass1 total=%d\n", total);
	printf("\nshadow array id after pass2:\n");

    for (j = 0; j < MAP_COLS; j++) {
		printf("%d ", id[0][j]);
	}
	
	printf("rowtotal=%d\n", rowtotal[0]);
#endif			

// Pass 2: eliminate double-counted islands, start with second row
	for (i = 1; i < MAP_ROWS; i++) {

		// reset neighbor id flag on new row
		neighbor = 0;
		
		for (j = 0; j < MAP_COLS; j++) {
			
// is this a nonzero cell with a newly discovered nonzero neighbor row island above?
			if (id[i][j] != 0 && id[i-1][j] != 0 && id[i-1][j] != neighbor) {
				
				// yes -> track which neighbor row island is above
				neighbor = id[i-1][j];
#ifdef DEBUG				
				id[i][j] = neighbor;
				rowtotal[i]--;
#endif
				// yes -> un-count this neighbor row island
				total--;
			}
			// reset neighbor id flag after each row island
			else if (id[i][j] == 0) {
				neighbor = 0;
			}
#ifdef DEBUG
			printf("%d ", id[i][j]);
#endif	
		}

#ifdef DEBUG
		printf("rowtotal=%d\n", rowtotal[i]);
#endif			
	}

#ifdef DEBUG
	printf("\npass2 total=%d", total);
#endif
			
    return total;
}

