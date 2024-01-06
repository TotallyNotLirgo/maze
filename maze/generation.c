#include "generation.h"

double random_max(double max_value) {
    return (double) rand() / RAND_MAX * max_value;
}

void generate_maze(Maze* maze) {
    int size = maze->size * maze->size;
    for (int i = 0; i < size; i++) {
        maze->weights[i] = random_max(10);
    }
    maze->start_x = random_max(maze->size);
    maze->end_x = random_max(maze->size);
    UInt128Array con_areas = {
        .array = malloc(size * sizeof(uint128)),
        .len = size
    };
    size = 2 * (maze->size - 1) * (maze->size - 1);
    Connections forb_cons = {
        .len = size,
        .v = malloc(size * sizeof(int)),
        .h = malloc(size * sizeof(int))
    };
    int j = 0;
    for (int i = 0; i < maze->cons.len; i++) {
        if ((i + 1) % maze->size != 0) {
            forb_cons.v[j] = i;
            forb_cons.v[j + 1] = i + 1;
            j += 2;
        }
        if (i <= maze->cons.len - maze->size) {
            forb_cons.h[2 * i] = i;
            forb_cons.h[2 * i + 1] = i + maze->size - 1;
        }
    }
    for (int i = 0; i < con_areas.len; i++)
        con_areas.array[i] = (uint128) 1 << i;

    while (con_areas.len > 1) {
        int next_wall = random_max(maze->cons.len * 2);
        int is_h = next_wall >= maze->cons.len;
        next_wall %= maze->cons.len;
        Connections tmp = {
            .len = maze->cons.len,
            .v = malloc(maze->cons.len * sizeof(int)),
            .h = malloc(maze->cons.len * sizeof(int))
        };
        memcpy(tmp.h, maze->cons.h, maze->cons.len * sizeof(int));
        memcpy(tmp.v, maze->cons.v, maze->cons.len * sizeof(int));
        int* t = is_h ? tmp.h : tmp.v; 
        t[next_wall] = 1;
        if (is_connection_forbidden(tmp, forb_cons)) continue;
        maze->cons = tmp;
        connect(next_wall, is_h, &con_areas, maze->size);
    }
}
