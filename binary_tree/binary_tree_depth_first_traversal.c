// Write a function for binary tree depth first traversal

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node_t;

static Node_t* create_node(int value) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static void print_tree_depth_first_traversal(Node_t* node) {
    if (node == NULL) {
        return;
    }

    printf("Node %i\n", node->value);
    print_tree_depth_first_traversal(node->left);
    print_tree_depth_first_traversal(node->right);
}

int main() {
    // Level 1
    Node_t* root = create_node(1);
    // Level 2
    root->left = create_node(2);
    root->right = create_node(3);
    // Level 3
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    root->right->left = create_node(6);
    root->right->right = create_node(7);
    // Level 4
    root->right->right->right = create_node(8);

    print_tree_depth_first_traversal(root);

    return 0;
}