// This example creates a linked list and prints its nodes.

#include "linked_list_lib.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Node_t* head     = create_node(1);
    head->next       = create_node(2);
    head->next->next = create_node(3);

    Node_t* node = head;
    while (node != NULL) {
        printf("Node %u\n", node->value);
        node = node->next;
    }

    return 0;
}
