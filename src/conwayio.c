/**
 * @file conwayio.c
 *
 * @brief Conway's board printing functions
 */

/* System includes */
#include <stdio.h>

/* Local includes */
#include <conway.h>
#include <conwayio.h>


/* Prints Conway's board to a file */
void conway_fdraw_universe(FILE *fp, conway_t *conway)
{
    size_t i, j;

    fprintf(fp, "\n");
    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            if (conway->universe[i][j].alive) {
                fprintf(fp, "O");
            } else {
                fprintf(fp, "-");
            }
        }
        fprintf(fp, "\n");
    }
}


/* Prints Conway's neighbors board to a file */
void conway_fdraw_neighbors(FILE *fp, conway_t *conway)
{
    size_t i, j;
    int neighbors;

    fprintf(fp, "\n");
    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            neighbors = conway_neighbors(conway, i, j);
            fprintf(fp, "%d", neighbors);
        }
        fprintf(fp, "\n");
    }
}

