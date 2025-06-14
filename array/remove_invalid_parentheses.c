// Remove the minimum number of parentheses required to make
// parentheses valid (every opening parenthesis has a matching
// closing one).

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int  size;
    int  capacity;
    int* storage;
} Stack_t;

Stack_t* create_stack(int size) {
    Stack_t* stack  = malloc(sizeof(Stack_t));
    stack->storage  = malloc(sizeof(int) * size);
    stack->size     = 0;
    stack->capacity = size;
    return stack;
}

bool stack_is_empty(Stack_t* stack) {
    return (stack->size == 0);
}

int stack_push(Stack_t* stack, int val) {
    if (stack->size == stack->capacity) {
        return -1;
    }

    uint32_t* addr = (uint32_t*)stack->storage + stack->size;
    *addr          = val;
    stack->size++;
    return 0;
}

int stack_pop(Stack_t* stack, int* val) {
    if (stack->size == 0) {
        return -1;
    }

    stack->size--;
    uint32_t* addr = (uint32_t*)stack->storage + stack->size;
    if (val != NULL) {
        *val = *addr;
    }
    return 0;
}

// Mark all invalid parens with '*'
int find_extra_parens(char* str) {
    Stack_t* stack = create_stack(strlen(str));
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(') {
            stack_push(stack, i);
        } else if (str[i] == ')') {
            if (stack_is_empty(stack)) {
                str[i] = '*';
            } else {
                stack_pop(stack, NULL);
            }
        }
    }

    int val = 0;
    while (stack_pop(stack, &val) == 0) {
        str[val] = '*';
    }

    return 0;
}

// Remove all invalid parens replaced with '*'
int remove_extra_parens(char* str) {
    int dst        = 0;
    int src        = 0;
    int skip_count = 0;
    while (str[src] != '\0' && str[dst] != '\0') {
        if (str[src] == '*') {
            src++;
            skip_count++;
        } else {
            str[dst] = str[src];
            src++;
            dst++;
        }
    }

    str[src - skip_count] = '\0';
    return 0;
}

int main(void) {
    char str[] = "a)b((c)d)e)";

    printf("Given string: %s\n", str);

    if (find_extra_parens(str)) {
        printf("Error\n");
    } else {
        printf("Marked invalid parens: %s\n", str);
    }

    if (remove_extra_parens(str)) {
        printf("Error\n");
    } else {
        printf("Removed invalid parens: %s\n", str);
    }

    return 0;
}
