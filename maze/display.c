#include "display.h"

void print_maze(Maze maze) {
    int vi = 0;
    int hi = 0;
    char* character;
    printf("Lightest path weight: %f\n", maze.path_weight);
    for (int i = 0; i <= maze.size; i++) {
        for (int j = 0; j <= maze.size; j++) {
            character = i == 0 || i == maze.size ? WALL_CHARACTER : " ";
            character = i == 0 && j == maze.start_x ? "|" : character;
            character = i == maze.size && j == maze.end_x ? "|" : character;
            if (i != 0 && i != maze.size && j != maze.size) {
                character = maze.cons.v[vi] ? " " : WALL_CHARACTER;
                character = maze.path.v[vi] ? "|" : character;
                vi++;
            }
            printf("%s", WALL_CHARACTER);
            if (j != maze.size) printf("%s", character);
        }
        printf("\n");
        if (i == maze.size) return;
        for (int j = 0; j <= maze.size; j++) {
            character = j == 0 || j == maze.size ? WALL_CHARACTER : " ";
            if (j != 0 && j != maze.size) {
                character = maze.cons.h[hi] ? " " : WALL_CHARACTER;
                character = maze.path.h[hi] ? "-" : character;
                hi++;
            }
            printf("%s", character);
            if (j != maze.size)
                printf("%d", (int) maze.weights[i * maze.size + j]);
        }
        printf("\n");
    }
}
