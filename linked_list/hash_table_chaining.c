// Implement a hash table with chaining

// Value = 44, key/index = hash = 44 % 5 = 4
// Value = 12, key/index = hash = 12 % 5 = 2
// Value = 17, key/index = hash = 17 % 5 = 2
// |---|
// | 1 |
// |---|
// |---|     /--\      /--\         // 
// | 2 | => | 12 | => | 17 |
// |---|     \--/      \--/
// |---|
// | 3 |
// |---|
// |---|     /--\       // Comment cannot be terminated with a backslash
// | 4 | => | 44 |
// |---|     \--/
// |---|
// | 5 |
// |---|

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_TABLE_SIZE 100

typedef struct Node {
    int value;
    struct Node* next;
} Node_t;

static Node_t* hash_table[HASH_TABLE_SIZE];

static int hash_function(int value) {
    return value % HASH_TABLE_SIZE;
}

static Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

static void hash_table_init() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

static void hash_table_insert(int value) {
    int index = hash_function(value);
    Node_t* node = create_node(value);
    if (hash_table[index] == NULL) {
        hash_table[index] = node;
    } else {
        Node_t* current_node = hash_table[index];
        while (current_node->next != NULL) {
            current_node = current_node->next;
        }
        current_node->next = node;
    }
}

static bool hash_table_contains(int value) {
    int index = hash_function(value);
    Node_t* node = hash_table[index];
    while (node != NULL) {
        if (node->value == value) {
            return true;
        }
        node = node->next;
    }
    return false;
}

static void hash_table_delete(int value) {
    int index = hash_function(value);
    Node_t* node = hash_table[index];
    Node_t* prev_node = NULL;
    while (node != NULL) {
        if (node->value == value) {
            if (prev_node == NULL) {
                hash_table[index] = node->next;
            } else {
                prev_node->next = node->next;
            }
            free(node);
            return;
        }
        prev_node = node;
        node = node->next;
    }
}

void hash_table_print(void) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node_t* node = hash_table[i];
        while (node != NULL) {
            printf("Key = %i, value = %i\n", i, node->value);
            node = node->next;
        }
    }
}

int main() {
    hash_table_init();
    hash_table_insert(1);
    hash_table_insert(2);
    hash_table_insert(3);
    hash_table_insert(4);
    hash_table_insert(5);
    hash_table_insert(11);
    hash_table_insert(21);
    hash_table_insert(31);

    hash_table_print();

    if (hash_table_contains(1)) {
        printf("Value = 1 exists in the hash table\n");
    }

    if (hash_table_contains(21)) {
        printf("Value = 21 exists in the hash table\n");
    }

    if (hash_table_contains(45)) {
        printf("Value = 45 exists in the hash table\n");
    }

    hash_table_delete(1);
    hash_table_print();

    hash_table_delete(31);
    hash_table_print();
}