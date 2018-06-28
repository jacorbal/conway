/**
 * @file conwayio.c
 *
 * @brief Conway's board printing functions
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

