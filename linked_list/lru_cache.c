// Note: This code is not working yet and needs to be debugged

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HASH_CAPACITY  1000

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    uint32_t     value;
} Node_t;

typedef struct {
    void*    hash_table;
    Node_t*  front;
    Node_t*  rear;
    uint32_t capacity;
    uint32_t count;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* lru_cache   = (LRUCache*)malloc(sizeof(LRUCache));
    lru_cache->hash_table = malloc(HASH_CAPACITY * sizeof(LRUCache*));
    LRUCache** table_ptr  = (LRUCache**)lru_cache->hash_table;
    for (int i = 0; i < HASH_CAPACITY; i++) {
        table_ptr[i] = NULL;
    }
    lru_cache->front    = NULL;
    lru_cache->rear     = NULL;
    lru_cache->capacity = capacity;
    lru_cache->count    = 0;
    return lru_cache;
}

void SwapNodeWithFront(LRUCache* obj, int key) {
    Node_t** hash_table = (Node_t**)obj->hash_table;
    Node_t*  node       = hash_table[key];
    if (node == NULL) {
        return;
    }

    // Swap the current node with the node at the front of the queue
    if (node != obj->front) {
        Node_t* node_next      = node->next;
        Node_t* node_prev      = node->prev;
        Node_t* node_prev_next = NULL;
        if (node->prev != NULL)
            node_prev_next = node->prev->next;

        if (obj->rear == node)
            obj->rear = obj->front;

        node->next = obj->front->next;
        node->prev = NULL;

        obj->front->prev = node_prev;
        obj->front->next = node_next;
        if (obj->front->prev != NULL)
            obj->front->prev->next = node_prev_next;
        obj->front = node;
    }
}

int lRUCacheGet(LRUCache* obj, int key) {
    SwapNodeWithFront(obj, key);
    return obj->front->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj == NULL) {
        return;
    }

    // Check if the key is already in the cache
    Node_t** hash_table = (Node_t**)obj->hash_table;
    if (hash_table[key] == NULL) {
        // Not in the cache - add new
        Node_t* new_node = malloc(sizeof(Node_t));
        new_node->prev   = NULL;
        new_node->next   = obj->front;
        new_node->value  = value;
        obj->front       = new_node;
        if (obj->rear == NULL) {
            obj->rear = new_node;
        }
        hash_table[key] = new_node;
    } else {
        // Already in the cache - update value and swap
        // this value with the value in the newest node (front)
        SwapNodeWithFront(obj, key);
        obj->front->value = value;
    }

    obj->count++;
    if (obj->count > obj->capacity) {
        // Per revocation policy, remove the
        // oldest node and update the hash table
        Node_t* oldest_node = obj->rear;
        if (oldest_node->prev != NULL) {
            oldest_node->prev->next = NULL;
        }
        obj->rear = oldest_node->prev;
        free(oldest_node);
        obj->count--;
        hash_table[key] = NULL;
    }
}

void lRUCacheFree(LRUCache* obj) {
    if (obj == NULL) {
        return;
    }

    // while (obj->front != NULL) {
    //     printf("val=%u",obj->front->value);
    //     Node_t* next = obj->front->next;
    //     // free(obj->front);
    //     obj->front = next;
    // }

    free(obj->hash_table);
}

// Source: https://leetcode.com/problems/lru-cache/?envType=problem-list-v2&envId=7p5x763

//  * Your LRUCache struct will be instantiated and called as such:
//  * LRUCache* obj = lRUCacheCreate(capacity);
//  * int param_1 = lRUCacheGet(obj, key);

//  * lRUCachePut(obj, key, value);

//  * lRUCacheFree(obj);

// Example 1:
// Input
// ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// Output
// [null, null, null, 1, null, -1, null, -1, 3, 4]

int main() {
    return -1;
}
