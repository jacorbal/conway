/**
 * @file conway.c
 *
 * @brief Conway's game of life implementation
 */

/* System includes */
#include <stdbool.h>
#include <stdlib.h>

/* Local includes */
#include <conway.h>


/* Initializes Conway's universe */
int conway_init(conway_t *conway, int num_rows, int num_cols)
{
    int i;

    conway->universe = (cell_t **) malloc(sizeof(cell_t *) * num_rows);
    if (conway->universe == NULL) {
        return 1;
    }

    for (i = 0; i < num_rows; ++i) {
        conway->universe[i] = (cell_t *) malloc(sizeof(cell_t) * num_cols);
        if (conway->universe[i] == NULL) {
            return 2;
        }
    }

    conway->num_rows = num_rows;
    conway->num_cols = num_cols;
    conway_reset(conway);

    return 0;
}


/* Deallocated used memory in a Conway's data type */
void conway_destroy(conway_t *conway)
{
    int i;

    for (i = 0; i < conway->num_rows; ++i) {
        free(conway->universe[i]);
    }
    free(conway->universe);
}


/* Resets conway's universe setting to false each item of the array */
void conway_reset(conway_t *conway)
{
    int i, j;

    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            conway->universe[i][j].alive = false;
        }
    }
}


void conway_random(conway_t *conway, unsigned int seed)
{
    int i, j;

    srand(seed);
    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            conway->universe[i][j].alive = rand() % 2;
        }
    }
}


/* Returns the number of neighbors to a given point */
int conway_neighbors(conway_t *conway, int x, int y)
{
    int i, j;
    int cx, cy;
    int neighbors = 0;

    for (i = -1; i < 2; ++i) {
        for (j = -1; j < 2; ++j) {
            if (i || j) {
                cx = (conway->num_rows + x + i) % conway->num_rows;
                cy = (conway->num_cols + y + j) % conway->num_cols;
                if (conway->universe[cx][cy].alive) {
                    neighbors++;
                }
            }
        }
    }

    return neighbors;
}


/* Checks if there's no life in a Conway's board */
bool conway_is_null(conway_t *conway)
{
    int i, j;

    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            if (conway->universe[i][j].alive) {
                return false;
            }
        }
    }

    return true;
}


/* Calculates the next generation for a Conway universe */
void conway_evolve(conway_t *conway)
{
    int i, j;
    int neighbors;

    /* Prepare cells for next generation*/
    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            neighbors = conway_neighbors(conway, i, j);

            if (conway->universe[i][j].alive &&
                    (neighbors < 2 || neighbors > 3)) {
                    conway->universe[i][j].state = CELL_EXPIRING;
            }
            if (!conway->universe[i][j].alive && neighbors == 3) {
                    conway->universe[i][j].state = CELL_RISING;
            }
        }
    }

    /* Evolve to the next generation */
    for (i = 0; i < conway->num_rows; ++i) {
        for (j = 0; j < conway->num_cols; ++j) {
            switch (conway->universe[i][j].state) {
                case CELL_RISING:
                    conway->universe[i][j].alive = true;
                    break;

                case CELL_EXPIRING:
                    conway->universe[i][j].alive = false;
                    break;

                case CELL_NORMAL:
                default:
                    break;
            }
            conway->universe[i][j].state = CELL_NORMAL;
        }
    }
}

