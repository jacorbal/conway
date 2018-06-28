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
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Local includes */
#include <conway.h>
#include <conwayio.h>

#define VERSION "1.0b\0"

#define ERROR_BAD_SIZE       3
#define ERROR_NEEDED_SIZE    4
#define ERROR_NEGATIVE_DELAY 5


/* Prototypes */
void run(conway_t *board, int generations, int delay);
void fprint_help(FILE *fp);
void fprint_version(FILE *fp);
void exit_with_reason(int error_code, char *error_msg);


/* Main entry */
int main(int argc, char *argv[])
{
    conway_t board;
    int num_rows = 20, num_cols = 75;
    int generations = -1;
    int delay = 1;/*seconds*/
    bool randomize = false;
    char *filename = NULL;
    char *token = NULL;
    int c;

    /* Options:
     *   -d  Delay seconds between iterations, or 0 for none
     *   -g  Maximum number of generations, or -1 to infinite
     *   -s  Board size in "nxm" format
     *   -r  Randomize board
     *   -f  File to get board from, or stdin (implicit dimensions)
     *   -h  Show help
     *   -v  Show version
     */
    const char *short_opt = "d:g:f:s:rhv";
    struct option long_opt[] = {
        {"delay",   required_argument,  NULL,   'd'},
        {"file",    required_argument,  NULL,   'f'},
        {"gens",    required_argument,  NULL,   'g'},
        {"size",    required_argument,  NULL,   's'},
        {"random",  no_argument,        NULL,   'r'},
        {"version", no_argument,        NULL,   'v'},
        {"help",    no_argument,        NULL,   'h'},
    };

    while ((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch (c) {
            case -1:
            case 0:
                break;
            case 'd':
                delay = atoi(optarg);
                if (delay < 0) {
                    exit_with_reason(ERROR_NEGATIVE_DELAY,
                        "Delay time must be unsinged integer.");
                }
                break;
            case 'g':
                generations = atoi(optarg);
                break;
            case 'f':
                filename = optarg;                                // TODO
                exit_with_reason(-1, "Feature not implemented yet. Use '-r' option :(");
                break;
            case 's':
                if ((token = strtok(optarg, "x"))) {
                    num_cols = atoi(token);
                    if ((token = strtok(NULL, "x"))) {
                        num_rows = atoi(token);
                    }
                }
                if (num_rows <= 0 || num_cols <= 0) {
                    exit_with_reason(ERROR_BAD_SIZE,
                            "Enter size in 'mxn' format (positive values).");
                }
                break;
            case 'r':
                randomize = true;
                if (num_rows <= 0 || num_cols <= 0) {
                    exit_with_reason(ERROR_NEEDED_SIZE,
                            "Needed size before using random option.");
                }
                break;
            case 'v':
                fprint_version(stdout);
                return 0;
            case 'h':
                fprint_help(stdout);
                return 0;
            case '?':
            default:
                fprint_help(stdout);
                return 1;
        }
    }

    conway_init(&board, num_rows, num_cols);

    if (randomize) {
        conway_random(&board, time(NULL));
    } else if (filename) {
    }

    run(&board, generations, delay);
    conway_destroy(&board);
    return 0;
}


void run(conway_t *board, int generations, int delay)
{
    conway_draw_universe(board);/* 0th generation */
    while (conway_has_life(board) && generations) {
        sleep(delay);
        conway_evolve(board);
        conway_draw_universe(board);
        if (generations > 0) {
            generations--;
        }
    }
}


void fprint_help(FILE *fp)
{
    fprintf(fp,"Options:\n");
    fprintf(fp, "  --delay, -d   Delay seconds between iterations, or 0 for none\n");
    fprintf(fp, "  --gens, -g    Maximum number of generations, or -1 to infinite\n");
    fprintf(fp, "  --size, -s    Board size in \"nxm\" format\n");
    fprintf(fp, "  --random, -r  Randomize board\n");
    fprintf(fp, "  --file, -f    File to get board from, or stdin (implicit dimensions)\n");
    fprintf(fp, "  --help, -h    Show help and exits\n");
    fprintf(fp, "  --version -v  Show version and exits\n");
    fprintf(fp, "\n");
    fprintf(fp, "Default values:\n");
    fprintf(fp, "  * delay: 1 second\n");
    fprintf(fp, "  * generations: infinite\n");
    fprintf(fp, "  * size: 75x20\n");
    fprintf(fp, "\n");
}


void fprint_version(FILE *fp)
{
    fprintf(fp, "Version: %s\n", VERSION);
}


void exit_with_reason(int error_code, char *error_msg)
{
    fprintf(stderr, "Error: %s\n", error_msg);
    exit(error_code);
}


/*
    // Glider
    conway_alive(&board, 3, 14);
    conway_alive(&board, 4, 16);
    conway_alive(&board, 5, 14);
    conway_alive(&board, 5, 15);
    conway_alive(&board, 5, 16);

    // Tetra-blinker
    conway_alive(&board, 16, 22);
    conway_alive(&board, 17, 22);
    conway_alive(&board, 18, 22);
    conway_alive(&board, 14, 24);
    conway_alive(&board, 14, 25);
    conway_alive(&board, 14, 26);
    conway_alive(&board, 20, 24);
    conway_alive(&board, 20, 25);
    conway_alive(&board, 20, 26);
    conway_alive(&board, 16, 28);
    conway_alive(&board, 17, 28);
    conway_alive(&board, 18, 28);
*/

