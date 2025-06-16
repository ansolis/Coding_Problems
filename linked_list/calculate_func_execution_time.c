
// Exclusive Time of Functions
// See
// https://www.educative.io/module/page/mwo3kDt63j7JqRLX1/10370001/5670721236369408/5491122682593280
// We are given an integer number, n, representing the number of functions
// running in a single-threaded CPU, and an execution log, which is essentially
//  a list of strings. Each string has the format
//  {function id}:{"start" | "end"}:{timestamp}, indicating that the function
//  with function id either started or stopped execution at the time identified by the timestamp
//  value. Each function has a unique ID between 0 and n-1. Compute the exclusive time of the
//  functions in the program.

// Example 1:
// log:  [‘0:start:0’, ‘1:start:6’, ‘1:end:6’, ‘0:end:7’]
// Output: [7, 1]
//
// Example 2:
// log:  [‘0:start:0’, ‘1:start:3’, ‘1:end:6’, ‘0:end:10’]
// Output: [7, 4]

#include "linked_list_lib.c"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// typedef struct Node {
//     int          value;
//     struct Node* next;
//     struct Node* rand;
// } Node_t;

typedef struct Stack {
    Node_t* top; // Linked list head node used as the top of the stack
} Stack_t;

// #define NODE_COUNT   5
#define ARR_SIZE(a)  (sizeof(a) / sizeof(a[0]))

// Stack implementation with linked list
Stack_t* stack_create(void) {
    Stack_t* stack = (Stack_t*)malloc(sizeof(Stack_t));
    stack->top     = NULL;
    return stack;
}

int stack_push(Stack_t* stack, int val) {
    if (stack == NULL) {
        return -1;
    }
    stack->top = insert_linked_list_val(stack->top, val);
    return 0;
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

#define START  1
#define STOP   0
#define ENCODE_DATA_AS_INT32(fxn, ts, time_adj) \
                                        ((((uint8_t)(fxn)) << 16) | \
                                        (((uint8_t)(ts)) << 8) | \
                                        ((uint8_t)(time_adj)))
#define DECODE_FXN_FROM_INT32(data)     ((uint8_t)((data) >> 16))
#define DECODE_TS_FROM_INT32(data)      ((uint8_t)((data) >> 8))
#define DECODE_TADJ_FROM_INT32(data)    ((uint8_t)(data))

int fxn_push(Stack_t* stack, int fxn_id, int ts, int time_adj) {
    return stack_push(stack, ENCODE_DATA_AS_INT32(fxn_id, ts, time_adj));
}

int fxn_pop(Stack_t* stack, int* fxn_id, int* ts, int* time_adj) {
    int val   = 0;
    int error = stack_pop(stack, &val);
    if (error != 0) {
        return error;
    }

    if (fxn_id != NULL) {
        *fxn_id = DECODE_FXN_FROM_INT32(val);
    }

    if (ts != NULL) {
        *ts = DECODE_TS_FROM_INT32(val);
    }

    if (time_adj != NULL) {
        *time_adj = DECODE_TADJ_FROM_INT32(val);
    }

    return error;
}

int fxn_peek(Stack_t* stack, int* fxn_id, int* ts) {
    int val   = 0;
    int error = stack_peek(stack, &val);
    if (error != 0) {
        return error;
    }

    if (fxn_id != NULL) {
        *fxn_id = DECODE_FXN_FROM_INT32(val);
    }

    if (ts != NULL) {
        *ts = DECODE_TS_FROM_INT32(val);
    }

    return error;
}

int main() {
    typedef struct {
        int  fxn_id;
        bool state; // 0 = stop, 1 = start
        int  ts;    // timestamp
        int  time_adj;
    } Log_t;

    int fxn_id;
    int ts;
    int time_adj;

    // Execution schedule for functions f1, f2, f3, f4:
    //
    // ts:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
    // f1:  ===            ====                                        ===================
    // f2:     ============
    // f3:                     ============                    ========
    // f4:                                 ====================
    Log_t log[] = {
        {1, START, 11},
        {2, START, 12},
        {2, STOP,  14},
        {3, START, 16},
        {4, START, 19},
        {4, STOP,  23},
        {3, STOP,  25},
        {1, STOP,  30}
    };

    Stack_t* stack         = stack_create();
    int      fxn_runtime   = 0;
    int      total_runtime = 0;

    for (int i = 0; i < ARR_SIZE(log); i++) {
        log[i].time_adj = 0;

        if (log[i].state == START) {
            fxn_push(stack, log[i].fxn_id, log[i].ts, 0);
        } else if (log[i].state == STOP) {
            // Let's confirm that the last started function is the same as the one being stopped
            if (fxn_peek(stack, &fxn_id, NULL) == 0) {
                if (fxn_id != log[i].fxn_id) {
                    printf("ERROR: Stop function: %i doesn't match start function %i\n",
                           log[i].fxn_id, fxn_id);
                    return -1;
                }
            } else {
                printf("ERROR: Stop log entry without a start at index %i\n", i);
                printf("  Current function ID: %i\n", log[i].fxn_id);
                printf("  Last log function ID: %i\n", fxn_id);
                return -1;
            }

            // Since the current function just stopped running, pop it off the stack
            // and calculate its runtime
            (void)fxn_pop(stack, &fxn_id, &ts, &time_adj);
            fxn_runtime = log[i].ts + 1 - ts - time_adj;
            printf("Function %i runtime: %i\n", log[i].fxn_id, fxn_runtime);

            // Update lost time for the previous function on the stack, if one exists
            int total_runtime = log[i].ts + 1 - ts;
            if (fxn_pop(stack, &fxn_id, &ts, &time_adj) == 0) {
                time_adj += total_runtime;
                // printf(" - New adj for f%i: %i\n", fxn_id, time_adj);
                fxn_push(stack, fxn_id, ts, time_adj);
            }
        } else {
            printf("ERROR: Invalid start/stop state in the log: %i\n", log[i].state);
        }
    }

    printf("\n");

    return 0;
}
