#include "solving.h"
#include "datatypes.h"
#include <stdio.h>


int compare_nodes(const void* a, const void* b) {
    const Node* node_a = *(Node**) a;
    const Node* node_b = *(Node**) b;
    if(node_b == NULL)
        return -1;
    if (node_a == NULL || node_a->weight > node_b->weight)
        return 1;
    if (node_a->weight < node_b->weight)
        return -1;
    return 0;
}

int node_to_id(Node* node, int maze_size) {
    return node->y * maze_size + node->x;
}

double solve_maze(Connections cons,
                  Connections* final_cons,
                  double* weights,
                  int maze_size,
                  int start_x,
                  int end_x) {
    Node* head = malloc(sizeof(Node));
    Node* node;
    head->x = start_x;
    head->y = 0;
    head->weight = weights[node_to_id(head, maze_size)];
    uint128 visited_mask = 0b0;
    double lowest_weight = head->weight;

    while(head->x != end_x || head->y != maze_size - 1) {
        Node* node_arr[4] = {NULL, NULL, NULL, NULL};
        int id = node_to_id(head, maze_size);
        int conditions[4] = {
            head->x < maze_size - 1 && cons.h[id - id / maze_size],
            head->y < maze_size - 1 && cons.v[id],
            head->x > 0 && cons.h[id - id / maze_size - 1],
            head->y > 0 && cons.v[id - maze_size],
        };
        int x_arr[4] = { head->x + 1, head->x    , head->x - 1, head->x     };
        int y_arr[4] = { head->y    , head->y + 1, head->y    , head->y - 1 };
        for(int i = 0; i < 4; i++) {
            if(!conditions[i]) continue;
            Node* node = malloc(sizeof(Node));
            node->x = x_arr[i];
            node->y = y_arr[i];
            uint128 pos_mask = (uint128) 0b1 << node_to_id(node, maze_size);
            if(visited_mask & pos_mask) continue;
            node->parent = head;
            node->weight = head->weight + weights[node_to_id(node, maze_size)];
            visited_mask |= pos_mask;
            node_arr[i] = node;
        }
        qsort(node_arr, 4, sizeof(Node*), compare_nodes);
        for(int i = 0; i < 4; i++) {
            if(node_arr[i] == NULL) break;
            node = head;
            while(node->next && node->next->weight < node_arr[i]->weight)
                node = node->next;
            node_arr[i]->next = node->next;
            node->next = node_arr[i];
        }
        head = head->next;
    }
    node = head;
    while(node->parent) {
        Node* a = node;
        Node* b = node->parent;
        if(a->x == b->x)
            final_cons->v[MIN(a->y, b->y) * maze_size + a->x] = 1;
        else
            final_cons->h[MIN(a->x, b->x) + a->y * (maze_size - 1)] = 1;
        node = node->parent;
    }
    return head->weight;
}
