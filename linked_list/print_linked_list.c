// GCC for VSCode setup guide: https://code.visualstudio.com/docs/cpp/config-mingw
// To execute the program built from this file, do Ctrl-Shift-P, select
// C/C++:Run C/C++ File. You should see the output in a new TERMINAL window.
// If you click on the "play"/triangle button with "Run Code" selected in the
// upper right-hand corner of the window, it will build and run the program,
// but the output will go to the OUTPUT window instead of the TERMINAL window.

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
