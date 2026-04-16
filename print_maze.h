#include "maze.h"

void print_top_border(maze *m);

void print_cell_contents(maze *m, int x, int y);

void print_bottom_border(maze *m, int y);

void print_intermediate_border(maze *m, int y);

const char *get_border_symbol(bool has_south, bool has_east, bool has_south_next, bool has_east_next);

void print_maze(maze *m);