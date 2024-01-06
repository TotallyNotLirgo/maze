#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze/display.h"
#include "maze/datatypes.h"
#include "maze/generation.h"
#include "maze/solving.h"


int main(int argc, char** argv)
{
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
    srand(time(NULL));
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
    Connections final_cons = {
        .len = size,
        .h = calloc(size, sizeof(int)),
        .v = calloc(size, sizeof(int))
    };
    double* weights = malloc(sizeof(double*) * maze_size * maze_size);
    for(int i = 0; i < maze_size * maze_size; i++){
        weights[i] = (double) rand() / RAND_MAX;
    }
    int start_x = (double) rand() / RAND_MAX * maze_size;
    int end_x = (double) rand() / RAND_MAX * maze_size;
    double len;
    generate_maze(maze_size, &cons);
    len = solve_maze(cons, &final_cons, weights, maze_size, start_x, end_x);
    print_maze(cons, maze_size, final_cons, weights, start_x, end_x, len);
}
