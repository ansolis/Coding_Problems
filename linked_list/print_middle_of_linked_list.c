// Print the middle element of a linked list

#include "linked_list_lib.c"

#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

Node_t* find_middle_node(Node_t* head) {
    Node_t* node       = head;
    Node_t* slow_node  = head;
    int     node_count = 0;

    while (node != NULL) {
        node = node->next;
        node_count++;
        if ((node_count % 2 == 0) && (node != NULL)) {
            slow_node = slow_node->next;
        }
    }

    return slow_node;
}

Node_t* find_middle_node_faster(Node_t* head) {
    Node_t* node      = head;
    Node_t* fast_node = head;

    while ((node != NULL) && (fast_node != NULL) && (fast_node->next != NULL) &&
           (fast_node->next->next != NULL)) {
        node      = node->next;
        fast_node = fast_node->next->next;
    }

    return node;
}

int main() {
    int     values[] = {1, 2, 3, 4, 5};
    Node_t* head     = create_linked_list(values, ARR_SIZE(values));
    print_linked_list_nodes(head);

    int node_count = get_node_count(head);
    printf("Number of nodes: %i\n", node_count);

    Node_t* slow_middle_node = find_middle_node(head);
    printf("Middle node (slow): %i\n", slow_middle_node->value);

    Node_t* fast_middle_node = find_middle_node_faster(head);
    printf("Middle node (fast): %i\n", fast_middle_node->value);

    delete_linked_list(&head);

    return 0;
}
