// Write a function that returns the height of a binary tree

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

static int get_height(Node_t* node) {
    if (node == NULL) {
        return 0;
    }

    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    int max_height = (left_height > right_height) ? left_height : right_height;
    return max_height + 1;
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

    printf("Height of the binary tree: %i\n", get_height(root));

    return 0;
}