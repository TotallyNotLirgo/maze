#ifndef SOLVING_H
#define SOLVING_H

#include "datatypes.h"
#include <stdlib.h>
#include <float.h>

#define MIN(a, b) (a < b ? a : b)

int node_to_id(Node* node, int maze_size) ;

int compare_nodes(const void* a, const void* b);

double solve_maze(
    Connections cons,
    Connections* final_cons,
    double* weights,
    int maze_size,
    int start_x,
    int end_x
);

#endif
