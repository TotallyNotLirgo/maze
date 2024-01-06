#include "connections.h"

int is_connection_forbidden(Connections cons, Connections forb_cons)
{
    for (int i = 0; i < forb_cons.len; i += 2) {
        if (cons.h[forb_cons.h[i]] == 1 && cons.h[forb_cons.h[i + 1]] == 1 &&
            cons.v[forb_cons.v[i]] == 1 && cons.v[forb_cons.v[i + 1]] == 1)
            return 1;
    }
    return 0;
}

void connect(int wall, int is_h, UInt128Array* con_areas, int maze_size)
{
    int a;
    int b;
    int index_a = -1;
    int index_b = -1;
    int offset = 0;
    if (is_h) {
        int section_size = maze_size - 1;
        int offset = wall % (maze_size - 1);
        a = (wall / section_size) * maze_size + offset;
        b = a + 1;
    } else {
        a = wall;
        b = wall + maze_size;
    }
    for (int i = 0; i < con_areas->len; i++) {
        if ((uint128) 1 << a & con_areas->array[i]) 
            index_a = i;
        else if ((uint128) 1 << b & con_areas->array[i])
            index_b = i;
    }
    if (index_a != -1 && index_b != -1) {
        con_areas->array[index_a] |= con_areas->array[index_b];
        for (int i = 0; i < con_areas->len; i++) {
            con_areas->array[i - offset] = con_areas->array[i];
            if (i == index_b) offset = 1;
        }
        con_areas->len -= 1;
    }
}
