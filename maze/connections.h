#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "datatypes.h"

/*
* Returns 1 if the connecion includes a 2x2 area, 0 otherwise.
* Arguments:
*     cons - connections to be checked
*     forb_cons - connections that produce 2x2 areas
*/
int is_connection_forbidden(Connections cons, Connections forb_cons);

/* 
* Connects areas separated by a wall.
* Arguments:
*    wall - wall that seperates the areas
*    is_h - whether the wall separates tiles horizontally
*    con_areas - array of masks of connected tiles
*    maze_size - size of the maze
*/
void connect(int wall, int is_h, UInt128Array* con_areas, int maze_size);

#endif
