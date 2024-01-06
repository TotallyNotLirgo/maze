#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "maze/datatypes.h"
#include "maze/display.h"
#include "maze/generation.h"
#include "maze/solving.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments.\n");
        fprintf(stderr, "For more info: %s --help\n", argv[0]);
        return 1;
    }
    if (!strcmp(argv[1], "--help")) {
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
    Maze maze;
    maze.size = maze_size;

    maze.cons.len = maze.size * maze.size - maze.size;
    maze.cons.h = calloc(maze.cons.len, sizeof(int));
    maze.cons.v = calloc(maze.cons.len, sizeof(int));

    maze.path.len = maze.size * maze.size - maze.size;
    maze.path.h = calloc(maze.path.len, sizeof(int));
    maze.path.v = calloc(maze.path.len, sizeof(int));

    maze.weights = malloc(sizeof(double*) * maze.size * maze.size);
    srand(time(NULL));
    generate_maze(&maze);
    solve_maze(&maze);
    print_maze(maze);
}
