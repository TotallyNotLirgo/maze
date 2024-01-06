#ifndef GENERATION_H
#define GENERATION_H

#include <stdlib.h>
#include <string.h>
#include "datatypes.h"
#include "connections.h"

/*
* Generates a pseudo random value from 0 to max_value
* Arguments:
*     max_value - upper threshold for the generated value
*/
double random_max(double max_value);
/*
* Generates a maze
* Arguments:
*     maze - pointer to a maze to be generated
*/
void generate_maze(Maze* maze);

#endif
