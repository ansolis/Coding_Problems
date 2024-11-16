// Print the middle element of a linked list

#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct Node {
    int          value;
    struct Node* next;
} Node_t;

static Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value = value;
    node->next = NULL;
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

void print_linked_list_nodes(Node_t* head) {
    Node_t* node = head;
    while (node != NULL) {
        printf("Node %u\n", node->value);
        node = node->next;
    }
}

int get_node_count(Node_t* head) {
    Node_t* node = head;
    int node_count = 0;

    while (node != NULL) {
        node_count++;
        node = node->next;
    }

    return node_count;
}

Node_t* find_middle_node(Node_t* head) {
    Node_t* node = head;
    int node_count = 0;
    Node_t* slow_node = head;

    while (node != NULL) {
        node = node->next;
        node_count++;
        if ((node_count % 2 == 0) && (node != NULL)) {
            slow_node = slow_node->next;
        }
    }

    return slow_node;
}

int main()
{
    int values[] = {1, 2, 3, 4, 5};
    Node_t* head = create_linked_list(values, ARR_SIZE(values));
    print_linked_list_nodes(head);
    
    int node_count = get_node_count(head);
    printf("Number of nodes: %i\n", node_count);

    Node_t* middle_node = find_middle_node(head);
    printf("Middle node: %i\n", middle_node->value);

    return 0;
}
