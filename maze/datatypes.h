#ifndef DATATYPES_H
#define DATATYPES_H

#define uint128 __uint128_t

/*
* array - array of 128 bit unsigned integers
* len - length of the array
*/
typedef struct {
    uint128* array;
    int len;
} UInt128Array;

/*
* v - array of vertical connections of the maze
* h - array of horizontal connections of the maze
* len - length of the arrays
*/
typedef struct {
    int* v;
    int* h;
    int len;
} Connections;

/*
* weight - weight of the node
* x - the node's horizontal position
* y - the node's vertical position
* parent - pointer to a node that this node originates from
* next - pointer to a node with the next biggest weight
*/
typedef struct _node {
    double weight;
    int x;
    int y;
    struct _node* parent;
    struct _node* next;
} Node;

/*
* size - size of the maze (the maze may only be square)
* start_x - starting position (y = 0)
* end_x - end position (y = size - 1)
* weights - array of weights of all the tiles
* cons - connections of the maze
* path - the shortest solution to the maze
* path_weight - sum of weights of the nodes in the path
*/
typedef struct {
    int size;
    int start_x;
    int end_x;
    double* weights;
    Connections cons;
    Connections path;
    double path_weight;
} Maze;

#endif
