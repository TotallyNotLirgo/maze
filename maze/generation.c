#include "generation.h"

void generate_maze(int maze_size, Connections* cons) {
    int size = maze_size * maze_size;
    UInt128Array con_areas = {
        .array = malloc(size * sizeof(uint128)),
        .len = size
    };
    size = 2 * (maze_size - 1) * (maze_size - 1);
    Connections forb_cons = {
        .len = size,
        .v = malloc(size * sizeof(int)),
        .h = malloc(size * sizeof(int))
    };
    int j = 0;
    for (int i = 0; i < cons->len; i++) {
        if ((i + 1) % maze_size != 0) {
            forb_cons.v[j] = i;
            forb_cons.v[j + 1] = i + 1;
            j += 2;
        }
        if (i <= cons->len - maze_size) {
            forb_cons.h[2 * i] = i;
            forb_cons.h[2 * i + 1] = i + maze_size - 1;
        }
    }
    for (int i = 0; i < con_areas.len; i++)
        con_areas.array[i] = (uint128) 1 << i;

    while (con_areas.len > 1) {
        int next_wall = ((double) rand() / RAND_MAX) * (cons->len * 2);
        int is_h = next_wall >= cons->len;
        next_wall %= cons->len;
        Connections tmp = {
            .v = malloc(cons->len * sizeof(int)),
            .h = malloc(cons->len * sizeof(int)),
            .len = cons->len
        };
        memcpy(tmp.h, cons->h, cons->len * sizeof(int));
        memcpy(tmp.v, cons->v, cons->len * sizeof(int));
        int* t = is_h ? tmp.h : tmp.v; 
        t[next_wall] = 1;
        if (is_connection_forbidden(tmp, forb_cons)) continue;
        *cons = tmp;
        connect(next_wall, is_h, &con_areas, maze_size);
    }
}
