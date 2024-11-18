// Implement stack using linked list

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node_t;

typedef struct Stack {
    Node_t* head;
} Stack_t;

Stack_t* stack_create(void) {
    Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));
    stack->head = NULL;
    return stack;
}

int stack_peek(Stack_t* stack) {
    return stack->head->value;
}

Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

void stack_push(Stack_t* stack, int value) {
    Node_t* node = create_node(value);
    node->next = stack->head;
    stack->head = node;
}

void stack_pop(Stack_t* stack) {
    Node_t* node = stack->head;
    stack->head = node->next;
    free(node);
}

void print_stack_nodes(Stack_t* stack) {
    Node_t* node = stack->head;
    while (node != NULL) {
        printf("Node %u\n", node->value);
        node = node->next;
    }
}

bool is_stack_empty(Stack_t* stack) {
    return (stack->head == NULL);
}

int main()
{
    Stack_t* stack = stack_create();

    // Push elements onto the stack
    stack_push(stack, 11);
    stack_push(stack, 22);
    stack_push(stack, 33);
    stack_push(stack, 44);

    printf("Stack nodes:\n");
    print_stack_nodes(stack);

    // Print top element of the stack
    printf("Top element is %d\n", stack_peek(stack));

    while (!is_stack_empty(stack)) {
        printf("Popping element %d\n", stack_peek(stack));
        stack_pop(stack);
    }

    if (is_stack_empty(stack)) {
        // Print success in green font using ANSI escape sequence
        printf("\033[32m" "Stack is empty" "\033[0m\n");
    } else {
        // Print error in red font using ANSI escape sequence
        printf("\033[31mERROR: Stack is not empty\033[0m\n");
    }

    return 0;
}
