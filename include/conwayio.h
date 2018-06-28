/**
 * @file conwayio.h
 *
 * @brief Conway's board printing functions declaration
 */
/*
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CONWAYIO_H
#define CONWAYIO_H

/* System includes */
#include <stdio.h>

/* Local includes */
#include <conway.h>


/**
 * @brief Prints Conway's board to a file
 *
 * @param conway Conway structure
 */
void conway_fdraw_universe(FILE *fp, conway_t *conway);

/**
 * @brief Prints Conway's neighbors board to a file
 *
 * @param conway Conway structure
 */
void conway_fdraw_neighbors(FILE *fp, conway_t *conway);

/**
 * @brief Prints to the standard output Conway's board
 *
 * @see conway_fdraw_universe
 */
#define conway_draw_universe(conway) conway_fdraw_universe(stdout, conway)

/**
 * @brief Prints to the standard output Conway's neighbors board
 *
 * @see conway_fdraw_neighbors
 */
#define conway_draw_neighbors(conway) conway_fdraw_neighbors(stdout, conway)


#endif /* !CONWAYIO_H */

