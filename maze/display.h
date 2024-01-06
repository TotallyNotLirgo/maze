#ifndef DISPLAY_H
#define DISPLAY_H

#include "datatypes.h"
#include <stdio.h>

#define WALL_CHARACTER "█"

void print_maze(
    Connections cons,
    int maze_size,
    Connections final_cons,
    double* weights,
    int start_x,
    int end_x,
    double len
);

#endif
