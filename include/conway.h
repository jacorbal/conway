/**
 * @file conway.h
 *
 * @brief Conway's game of life declaration
 */

#ifndef CONWAY_H
#define CONWAY_H

/* System includes */
#include <stdbool.h>


/**
 * @enum cell_state
 *
 * @brief Possible states regarding next generation
 */
enum cell_state {CELL_NORMAL, CELL_RISING, CELL_EXPIRING};

/**
 * @typedef cell_t
 *
 * @brief Conway's cell data
 */
typedef struct {
    bool alive;             /***< Current state */
    enum cell_state state;  /***< Next generation state */
} cell_t;


/**
 * @typedef conway_t
 *
 * @brief Conway structure
 */
typedef struct {
    int num_rows;       /***< Vertical size of the universe */
    int num_cols;       /***< Horizontal size of the universe */
    cell_t **universe;  /***< Cellular disposition in the universe */
} conway_t;


/* Public interface */
/**
 * @brief Initializes Conway's universe
 *
 * @param conway   Board to initialize
 * @param num_rows Number of rows
 * @param num_cols Number of columns
 *
 * @return 0 if success, otherwise if memory cannot be allocated (1 when
 *         allcoating rows, 2 when allocatin columns)
 */
int conway_init(conway_t *conway, int num_rows, int num_cols);

/**
 * @brief Deallocated used memory in a Conway's data type
 *
 * @param conway Conway structure to destroy
 */
void conway_destroy(conway_t *conway);

/**
 * @brief Resets Conway's universe setting to @c false each cell
 *
 * @param conway Conway universe to reset
 */
void conway_reset(conway_t *conway);

/**
 * @brief Resets Conway's universe setting every cell to a random value
 *
 * @param conway Conway universe to randomize
 * @param seed   Seed for a new sequence of pseudo-random values
 */
void conway_random(conway_t *conway, unsigned int seed);

/**
 * @brief Returns the number of neighbors to a given point
 *
 * @param conway Conway's structure
 * @param x      Abscise
 * @param y      Ordinate
 *
 * @return Number of neighbors for a given point
 */
int conway_neighbors(conway_t *conway, int x, int y);

/**
 * @brief Checks if there's no life in a Conway's board
 *
 * @param conway Conway universe to check
 *
 * @return @c true if null board, or otherwise
 */
bool conway_is_null(conway_t *conway);

/**
 * @brief Calculates the next generation for a Conway universe
 *
 * @param conway Board to evolve
 */
void conway_evolve(conway_t *conway);

/**
 * @brief Macro that evaluates to the total number of rows
 */
#define conway_rows(conway) conway.num_rows

/**
 * @brief Macro that evaluates to the total number of columns
 */
#define conway_cols(conway) conway.num_cols

/**
 * @brief Macro that evaluates to the life of the Universe
 *
 * @see conway_is_null
 */
#define conway_has_life(conway) !conway_is_null(conway)

/**
 * @brief Spawns life in (x, y)
 */
#define conway_alive(conway, x, y) ((conway)->universe[x][y].alive = true)

/**
 * @brief Kills life in (x, y)
 */
#define conway_dead(conway, x, y) ((conway)->universe[x][y].alive = false)


#endif  /* ! CONWAY_H */

