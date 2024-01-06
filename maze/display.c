#include "display.h"

void print_maze(Connections cons,
                int maze_size,
                Connections final_cons,
                double* weights,
                int start_x,
                int end_x,
                double len){
    int vi = 0;
    int hi = 0;
    int i, j;
    char* character;
    printf("Shortest path length: %f\n", len);
    for (i = 0; i <= maze_size; i++) {
        for (j = 0; j <= maze_size; j++) {
            character = i == 0 || i == maze_size ? WALL_CHARACTER : " ";
            if(i == 0 && j == start_x || i == maze_size && j == end_x)
                character = "|";
            else if (i != 0 && i != maze_size && j != maze_size) {
                character = cons.v[vi] ? " " : WALL_CHARACTER;
                character = final_cons.v[vi] ? "|" : character;
                vi++;
            }
            printf("%s", WALL_CHARACTER);
            if (j != maze_size) printf("%s", character);
        }
        printf("\n");
        if (i == maze_size) return;
        for (j = 0; j <= maze_size; j++) {
            character = j == 0 || j == maze_size ? WALL_CHARACTER : " ";
            if (j != 0 && j != maze_size) {
                character = cons.h[hi] ? " " : WALL_CHARACTER;
                character = final_cons.h[hi] ? "-" : character;
                hi++;
            }
            printf("%s", character);
            if(j != maze_size)
                printf("%d",(int) (10 * weights[i * maze_size + j]));
        }
        printf("\n");
    }
}
