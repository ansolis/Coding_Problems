#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          value;
    struct Node* next;
} Node_t;

Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value  = value;
    node->next   = NULL;
    return node;
}

Node_t* create_linked_list(int values[], int size) {
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

Node_t* insert_linked_list_node(Node_t* old_head, Node_t* new_head) {
    if (new_head != NULL) {
        new_head->next = old_head;
    }

    return new_head;
}

Node_t* insert_linked_list_val(Node_t* old_head, int val) {
    Node_t* new_head = create_node(val);
    if (new_head != NULL) {
        new_head->next = old_head;
    }

    return new_head;
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

// Delete node at position pos. pos=0 is for the head (first node)
// and pos=-1 is for the tail (last node).
void delete_linked_list_node(Node_t** head, int pos) {
    if (head == NULL) {
        return;
    }

    Node_t* node      = *head;
    Node_t* next      = (node == NULL) ? NULL : node->next;
    Node_t* next_next = (next == NULL) ? NULL : next->next;

    if (node == NULL) {
        return;
    }

    // Delete the tail (last node)
    if (pos == -1) {
        if (next != NULL) {
            while (next_next != NULL) {
                next_next = next_next->next;
                next      = next->next;
                node      = node->next;
            }

            if (next != NULL) {
                // Now next points to tail and node points to the node before tail
                free(next);
                node->next = NULL;
            }
        } else {
            // All we have left is the head node, so to delete the tail node we
            // have to delete the head node
            pos = 0;
        }
    }

    // Delete the head node
    if (pos == 0) {
        *head = node->next;
        free(node);
    }

    // TODO: Delete a node that's neither head nor tail
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
