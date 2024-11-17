// Write a function that returns the height of a binary tree

// Queue:
//                         tail
//                          \|/
// head -> node -> node -> node -> NULL
// Dequeue from head; enqueue at tail

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode_t;

typedef struct QueueNode {
    TreeNode_t* tree_node;
    struct QueueNode* next;
} QueueNode_t;

typedef struct Queue {
    struct QueueNode* head;
    struct QueueNode* tail;
} Queue_t;

Queue_t* create_queue(void) {
    Queue_t* queue = (Queue_t*)malloc(sizeof(Queue_t));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void enqueue(Queue_t* queue, TreeNode_t* node) {
    QueueNode_t* queue_node = (QueueNode_t*)malloc(sizeof(QueueNode_t));
    queue_node->tree_node = node;
    queue_node->next = NULL;
    if (queue->head == NULL) {
        queue->head = queue_node;
        queue->tail = queue_node;
    } else {
        queue->tail->next = queue_node;
        queue->tail = queue_node;
    }
}

TreeNode_t* dequeue(Queue_t* queue) {
    QueueNode_t* queue_node = queue->head;
    if (queue_node == NULL) {
        return NULL;
    }

    if (queue_node->next == NULL) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue_node->next;
    }

    return queue_node->tree_node;
}

bool is_queue_empty(Queue_t* queue) {
    return queue->head == NULL;
}

static TreeNode_t* create_tree_node(int value) {
    TreeNode_t* node = (TreeNode_t*)malloc(sizeof(TreeNode_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void print_tree_node(TreeNode_t* parent_node, TreeNode_t* node) {
    if (node == NULL) {
        if (parent_node == NULL) {
            printf("Node is NULL, root node\n");
        } else {
            printf("Node is NULL, leaf of %i\n", parent_node->value);
        }
    } else {
        if (parent_node == NULL) {  // root node
            printf("Node %i, root node\n", node->value);
        } else {
            printf("Node %i, leaf of %i\n", node->value, parent_node->value);
        }
    }
}

static void print_tree_level_traversal(TreeNode_t* node) {
    if (node == NULL) {
        return;
    }

    Queue_t* queue = create_queue();
    enqueue(queue, node);
    print_tree_node(NULL, node);
    
    while (!is_queue_empty(queue)) {
        TreeNode_t* current_node = dequeue(queue);
        // printf("Node %i\n", current_node->value);
        if (current_node->left != NULL) {
            enqueue(queue, current_node->left);
        }
        if (current_node->right != NULL) {
            enqueue(queue, current_node->right);
        }
        print_tree_node(current_node, current_node->left);
        print_tree_node(current_node, current_node->right);
    }
}

int main() {
    // Level 1
    TreeNode_t* root = create_tree_node(1);
    // Level 2
    root->left = create_tree_node(2);
    root->right = create_tree_node(3);
    // Level 3
    root->left->left = create_tree_node(4);
    root->left->right = create_tree_node(5);
    // root->right->left = create_tree_node(6);
    root->right->right = create_tree_node(7);
    // Level 4
    root->right->right->right = create_tree_node(8);

    print_tree_level_traversal(root);

    return 0;
}