#ifndef SOLVING_H
#define SOLVING_H

#include <stdlib.h>
#include <stdio.h>
#include "datatypes.h"

#define MIN(a, b) (a < b ? a : b)

/*
* Returns the index of a node in a maze of a given size
* Arguments:
*     node - pointer to a node
*     maze_size - size of a maze
*/
int node_to_id(Node* node, int maze_size) ;

/*
* Solves a maze.
* Arguments:
*     maze - pointer to a maze to be solved
*/
void solve_maze(Maze* maze);

#endif
