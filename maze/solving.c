#include "solving.h"


int node_to_id(Node* node, int size) {
    return node->y * size + node->x;
}

void solve_maze(Maze* maze) {
    Node* head = malloc(sizeof(Node));
    Node* node;
    head->x = maze->start_x;
    head->y = 0;
    head->weight = maze->weights[node_to_id(head, maze->size)];
    uint128 visited_mask = 0;

    while (head->x != maze->end_x || head->y != maze->size - 1) {
        Node* node_arr[4] = {NULL, NULL, NULL, NULL};
        int id = node_to_id(head, maze->size);
        int conditions[4] = {
            head->x < maze->size - 1 && maze->cons.h[id - id / maze->size],
            head->y < maze->size - 1 && maze->cons.v[id],
            head->x > 0 && maze->cons.h[id - id / maze->size - 1],
            head->y > 0 && maze->cons.v[id - maze->size],
        };
        int x_arr[4] = { head->x + 1, head->x    , head->x - 1, head->x     };
        int y_arr[4] = { head->y    , head->y + 1, head->y    , head->y - 1 };
        for (int i = 0; i < 4; i++) {
            if (!conditions[i]) continue;
            Node* node = malloc(sizeof(Node));
            node->x = x_arr[i];
            node->y = y_arr[i];
            uint128 pos_mask = (uint128) 1 << node_to_id(node, maze->size);
            if (visited_mask & pos_mask) continue;
            node->parent = head;
            node->weight = head->weight;
            node->weight += maze->weights[node_to_id(node, maze->size)];
            visited_mask |= pos_mask;
            node_arr[i] = node;
        }
        for (int i = 0; i < 4; i++) {
            if (node_arr[i] == NULL) continue;
            node = head;
            while (node->next && node->next->weight < node_arr[i]->weight)
                node = node->next;
            node_arr[i]->next = node->next;
            node->next = node_arr[i];
        }
        head = head->next;
    }
    node = head;
    while (node->parent) {
        Node* a = node;
        Node* b = node->parent;
        if (a->x == b->x)
            maze->path.v[MIN(a->y, b->y) * maze->size + a->x] = 1;
        else
            maze->path.h[MIN(a->x, b->x) + a->y * (maze->size - 1)] = 1;
        node = node->parent;
    }
    maze->path_weight = head->weight;
}
