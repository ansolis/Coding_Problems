#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          value;
    struct Node* next;
} Node_t;

static Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value  = value;
    node->next   = NULL;
    return node;
}

static Node_t* create_linked_list(int values[], int size) {
    Node_t* head = NULL;
    Node_t* node = NULL;
    Node_t* prev = NULL;

    for (int i = 0; i < size; i++) {
        node = create_node(values[i]);
        if (prev != NULL) {
            prev->next = node;
        }
        head = (head == NULL) ? node : head;
        prev = node;
    }

    return head;
}

void delete_linked_list(Node_t** head) {
    Node_t* node = *head;
    Node_t* next = NULL;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }

    *head = NULL;
}

int get_node_count(Node_t* head) {
    Node_t* node       = head;
    int     node_count = 0;

    while (node != NULL) {
        node_count++;
        node = node->next;
    }

    return node_count;
}

void print_linked_list_nodes(Node_t* head) {
    Node_t* node = head;
    while (node != NULL) {
        printf("Node %u\n", node->value);
        node = node->next;
    }
}
