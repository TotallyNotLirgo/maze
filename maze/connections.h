#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "datatypes.h"

int is_connection_forbidden(Connections cons, Connections forb_cons);

void connect(int wall, int is_h, UInt128Array* con_areas, int maze_size);

#endif
