// THis example creates a linked list and prints its nodes.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node_t;

Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

int main()
{
    Node_t* head = create_node(1);
    head->next = create_node(2);
    head->next->next = create_node(3);

    Node_t* node = head;
    while (node != NULL) {
        printf("Node %u\n", node->value);
        node = node->next;
    }

    return 0;
}
