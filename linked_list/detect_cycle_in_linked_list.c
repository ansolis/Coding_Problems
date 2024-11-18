// This example detects a cycle in a linked list
// and finds the starting node of the cycle.
// See Floyd's cycle-finding algorithm.

// The solution is based on the fast and low pointers (hare and tortoise)
// where the slow pointer advances one step at a time and the fast pointer
// advances two steps at a time. If they meet before a next == NULL pointer
// is reached, then there is a cycle.
//
//                       n
//            |-----------------------|
//      a    \|/                      |
// | 1 | -> | 2 | -> | 3 | -> | 4 | --|
//             |<-----b------->| /|\         //
//                                |
//     Meeting point of slow and fast
//

// See this explanation for the algorithm:
// https://www.geeksforgeeks.org/how-does-floyds-slow-and-fast-pointers-approach-work/

// Slow pointer traveled from head to meeting point:  a + n*i + b steps
// To travel to the node where the cycle starts, it needs to travel
// n*i - k steps.
// Another pointer can reach the point where the cycle starts in a steps
// or a + n*j steps. They are equal numbers of steps modulo n:
// mod(a + n*i) = mod(n*j - b)
// a = n*z - b
// Therefore, the two pointers, the slow pointer starting at position
// where it met with the fast pointer, and the other pointer starting at
// head node will meet at the same node that's the start of the cycle.

#include <stdbool.h>
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
    head->next->next->next = create_node(4);
    head->next->next->next->next = head->next; // Close the cycle at node 2

    Node_t* slow_node = head;
    Node_t* fast_node = head;
    bool cycle_detected = false;

    // Detect cycle
    while (slow_node != NULL && fast_node != NULL && fast_node->next != NULL) {
        slow_node = slow_node->next;
        fast_node = fast_node->next->next;
        if (slow_node == fast_node) {
            printf("Cycle detected at node %u\n", slow_node->value);
            cycle_detected = true;
            break;
        }
    }

    if (!cycle_detected) {
        printf("No cycle detected\n");
        return 0;
    }

    // Determine the starting node of the cycle.
    Node_t* node = head;
    while (node != slow_node) {
        node = node->next;
        slow_node = slow_node->next;
    }

    printf("Starting node of the cycle is: %u\n", node->value);

    return 0;
}
