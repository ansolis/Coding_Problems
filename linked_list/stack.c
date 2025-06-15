
// Stack implementation using linked lists

#include "linked_list_lib.c"

#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    Node_t* top; // Linked list head node used as the top of the stack
} Stack_t;

// Stack implementation with linked list
Stack_t* stack_create(void) {
    Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));
    stack->top     = NULL;
    return stack;
}

void stack_push(Stack_t* stack, int val) {
    stack->top = insert_linked_list_val(stack->top, val);
}

int stack_peek(Stack_t* stack, int* val) {
    if ((stack != NULL) && (stack->top != NULL)) {
        *val = stack->top->value;
        return 0;
    }

    return -1;
}

int stack_pop(Stack_t* stack, int* val) {
    int err = stack_peek(stack, val);
    if (err == 0) {
        delete_linked_list_node(&stack->top, 0);
        return 0;
    }

    return -1;
}

void stack_print(Stack_t* stack) {
    print_linked_list_nodes(stack->top);
}

int main() {
    Stack_t* stack = stack_create();
    stack_push(stack, 1);
    stack_push(stack, 2);
    stack_push(stack, 3);
    stack_print(stack);
    printf("\n");

    int val = 0;
    if (stack_pop(stack, &val) == 0) {
        printf("Popped: %i\n", val);
        stack_print(stack);
    } else {
        printf("Failed to pop\n");
        stack_print(stack);
    }
    printf("\n");

    if (stack_pop(stack, &val) == 0) {
        printf("Popped: %i\n", val);
        stack_print(stack);
    } else {
        printf("Failed to pop\n");
        stack_print(stack);
    }
    printf("\n");

    if (stack_pop(stack, &val) == 0) {
        printf("Popped: %i\n", val);
        stack_print(stack);
    } else {
        printf("Failed to pop\n");
        stack_print(stack);
    }
    printf("\n");

    if (stack_pop(stack, &val) == 0) {
        printf("Popped: %i\n", val);
        stack_print(stack);
    } else {
        printf("Failed to pop\n");
        stack_print(stack);
    }
    printf("\n");

    return 0;
}
