#ifndef DATATYPES_H
#define DATATYPES_H

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

typedef struct _node {
    double weight;
    int x;
    int y;
    struct _node* parent;
    struct _node* next;
} Node;

#endif
