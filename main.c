#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WALL_CHARACTER '#'
#define uint128 __uint128_t

typedef struct {
    uint128* array;
    int len;
} UInt128Array;

typedef struct {
    int* v;
    int* h;
    int len;
} Connections;

void
print_maze(Connections cons, int maze_size)
{
    int vi = 0;
    int hi = 0;
    int i, j;
    char character;
    for (i = 0; i <= maze_size; i++) {
        for (j = 0; j <= maze_size; j++) {
            character = i == 0 || i == maze_size ? WALL_CHARACTER : ' ';
            if (i != 0 && i != maze_size && j != maze_size) {
                character = cons.v[vi] == 0 ? WALL_CHARACTER : ' ';
                vi++;
            }
            printf("%c", WALL_CHARACTER);
            if (j != maze_size) printf("%c", character);
        }
        printf("\n");
        if (i == maze_size) return;
        for (j = 0; j <= maze_size; j++) {
            character = j == 0 || j == maze_size ? WALL_CHARACTER : ' ';
            if (j != 0 && j != maze_size) {
                character = cons.h[hi] == 0 ? WALL_CHARACTER : ' ';
                hi++;
            }
            printf("%c ", character);
        }
        printf("\n");
    }
}

int
is_connection_forbidden(Connections cons, Connections forb_cons)
{
    int i;
    for (i = 0; i < forb_cons.len; i += 2) {
        if (cons.h[forb_cons.h[i]] == 1 && cons.h[forb_cons.h[i + 1]] == 1 &&
            cons.v[forb_cons.v[i]] == 1 && cons.v[forb_cons.v[i + 1]] == 1)
            return 1;
    }
    return 0;
}

void
connect(int wall, int is_h, UInt128Array* con_areas, int maze_size)
{
    int a;
    int b;
    int index_a = -1;
    int index_b = -1;
    int i = 0, j = 0;
    if (is_h) {
        int section_size = maze_size - 1;
        int offset = wall % (maze_size - 1);
        a = (wall / section_size) * maze_size + offset;
        b = a + 1;
    } else {
        a = wall;
        b = wall + maze_size;
    }
    for (i = 0; i < con_areas->len; i++) {
        if ((uint128)0b1 << a & con_areas->array[i]) 
            index_a = i;
        else if ((uint128)0b1 << b & con_areas->array[i])
            index_b = i;
    }
    if (index_a != -1 && index_b != -1) {
        con_areas->array[index_a] |= con_areas->array[index_b];
        for (i = 0; i < con_areas->len; i++) {
            con_areas->array[j] = con_areas->array[i];
            if (i != index_b) j++;
        }
        con_areas->len -= 1;
    }
}

int
main(int argc, char** argv)
{
    //////// INITIALIZATION ////////
    if(argc != 2) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        fprintf(stderr, "For more info: %s --help\n", argv[0]);
        return 1;
    }
    if(!strcmp(argv[1], "--help")) {
        printf("Generates and solves a maze\n");
        printf("Usage:\n");
        printf("    %s SIZE\n", argv[0]);
        printf("SIZE - Maze size in range [4, 10]\n");
        return 0;
    }
    int maze_size = atoi(argv[1]);
    if (maze_size > 10 || maze_size < 4) {
        fprintf(stderr, "Maze size not in range [4, 10]\n");
        return 1;
    }

    int size = maze_size * maze_size - maze_size;
    Connections cons = {
        .len = size,
        .h = calloc(size, sizeof(int)),
        .v = calloc(size, sizeof(int))
    };
    size = maze_size * maze_size;
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
    int i, j;
    j = 0;
    for (i = 0; i < cons.len; i++) {
        if ((i + 1) % maze_size != 0) {
            forb_cons.v[j] = i;
            forb_cons.v[j + 1] = i + 1;
            j += 2;
        }
        if (i <= cons.len - maze_size) {
            forb_cons.h[2 * i] = i;
            forb_cons.h[2 * i + 1] = i + maze_size - 1;
        }
    }
    for (i = 0; i < con_areas.len; i++)
        con_areas.array[i] = (uint128) 0b1 << i;
    srand(time(NULL));
    //////// GENERATION ////////
    while (con_areas.len > 1) {
        int next_wall = rand() % (cons.len * 2);
        int is_h = next_wall > cons.len;
        next_wall %= cons.len;
        Connections tmp = {
            .v = malloc(cons.len * sizeof(int)),
            .h = malloc(cons.len * sizeof(int)),
            .len = cons.len
        };
        memcpy(tmp.h, cons.h, cons.len * sizeof(int));
        memcpy(tmp.v, cons.v, cons.len * sizeof(int));
        int* t = is_h ? tmp.h : tmp.v; 
        t[next_wall] = 1;
        if (is_connection_forbidden(tmp, forb_cons)) continue;
        cons = tmp;
        connect(next_wall, is_h, &con_areas, maze_size);
    }
    print_maze(cons, maze_size);
}
