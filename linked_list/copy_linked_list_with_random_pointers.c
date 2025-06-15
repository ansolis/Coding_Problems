
// Given a linked list with each node having an additional pointer
// pointing to a random node, create a copy of the linked list that
// preserves the same link order.

//                |------------------------|
//                |                       \|/
// |------|    |------|    |------|    |------|
// |   1  | -> | curr | -> | next | -> |      | ---
// |------|    |------|    |------|    |------|
//    |                       /|\                  //
//    |------------------------|

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          value;
    struct Node* next;
    struct Node* rand;
} Node_t;

#define NODE_COUNT   5
#define ARR_SIZE(a)  (sizeof(a) / sizeof(a[0]))

static Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value  = value;
    node->next   = NULL;
    return node;
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

static Node_t* create_linked_list(int values[], int rand[], int size) {
    Node_t* head = NULL;
    Node_t* node = NULL;
    Node_t* prev = NULL;
    Node_t* nodes[NODE_COUNT];
    int     count = 0;

    for (int i = 0; i < size; i++) {
        node = create_node(values[i]);
        if (prev != NULL) {
            prev->next = node;
        }
        head           = (head == NULL) ? node : head;
        prev           = node;
        nodes[count++] = node;
    }

    for (int i = 0; i < size; i++) {
        if (i < NODE_COUNT) {
            nodes[i]->rand = nodes[rand[i] - 1];
        }
    }

    return head;
}

void print_linked_list_nodes(Node_t* head) {
    Node_t* node = head;
    while (node != NULL) {
        printf("Node %i, rand = %i\n", node->value, node->rand->value);
        node = node->next;
    }
}

Node_t* copy_list(Node_t* head) {
    Node_t* node = head;
    Node_t* new_head;
    Node_t* new_node;

    if (!head) {
        return NULL;
    }

    // Original linked list (N is the next pointer, R is the random
    // node pointer):
    //
    //     |-------------------------------------------|
    //     |           |---------------------------|   |
    //    \|/          |R                         \|/  |R
    // |------|      |------|      |------|      |------|
    // |   1  | ---> |   2  | ---> |  3   | ---> |  4   | ---...
    // |------|      |------|      |------|      |------|
    //    |R                         /|\                  //
    //    |---------------------------|
    //
    // After we create a new node 1' and point its next pointer
    // to node 2 (what 1->next was pointing to) and point 1' node's
    // rand pointer to 3 (what 1->rand was pointing to), and point
    // node 1 rand pointer to 1', this becomes:
    //                  |---------------------------|
    //                  |                          \|/
    // |------|      |------|      |------|      |------|
    // |   1  |   |->|  2   | ---> |  3   | ---> |  4   | ---
    // |------|   |  |------|      |------|      |------|
    //   |N  |R   |                   /|\                     //
    //   |   -----|--------------------|
    //  \|/       |                    |
    // |------|N---                    |
    // |      |                        |
    // |  1'  |R------------------------
    // |------|

    while (node != NULL) {
        new_node       = create_node(node->value);
        new_node->next = node->next;
        new_node->rand = node->rand;
        node->next     = new_node;
        node           = new_node->next;
    }

    //
    // Do the same for all new nodes 2', 3', etc, and this becomes:
    //     |---------------------------------------------------------|
    //    \|/                                                        |
    // |------|         |------|         |------|         |------|   |
    // |   1  |   |---->|  2   |   |---->|  3   |   |---->|  4   |   |
    // |------|   |     |------|   |     |------|   |     |------|   |
    //     |N     |         |N     |      /|\ |N    |      /|\ |N    |
    //     |      |      |-----------------|  |     |       |  |     |
    //     |      |      |  |      |          |     |       |  |     |
    //     |      |      |  |      |      |-----------------|  |     |
    //     |      N      |  |      N      |   |     |N         |    \|/
    //     |   |-----|  R|  |   |-----|  R|   |  |-----|       |  |-----|
    //     --->|  1' |----  --->|  2' |----   -->|  3' |       -->|  4' |
    //         |-----|          |-----|          |-----|          |-----|

    // Do another pass to point new node's next pointer to the next new
    // node and new node's rand pointer to the next of what they're pointing
    // to now. We get new nodes that look like the original nodes.

    new_node = head->next;
    while ((new_node != NULL) && (new_node->next != NULL)) {
        new_node->next = new_node->next->next;
        new_node->rand = new_node->rand->next;
        new_node       = new_node->next;
    }

    return head->next;
}

int main() {
    int values[NODE_COUNT] = {1, 2, 3, 4, 5};
    int rand[NODE_COUNT]   = {3, 5, 1, 2, 4};

    Node_t* head = create_linked_list(values, rand, ARR_SIZE(values));
    print_linked_list_nodes(head);

    int node_count = get_node_count(head);
    printf("Number of nodes: %i\n", node_count);

    Node_t* new_linked_list = copy_list(head);
    if (new_linked_list != head) {
        printf("A new linked list was created\n");
    }
    print_linked_list_nodes(new_linked_list);

    return 0;
}
