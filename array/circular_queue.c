// Implement a simple circular queue

#include <stdlib.h>  // For malloc, free
#include <string.h>  // For memset, memcpy
#include <stdbool.h> // For bool type
#include <stdint.h>  // For uint8_t

typedef struct CircularQueue {
    void*       data;          // Pointer to the data array
    int         front;         // First element position in the queue
    int         size;          // Number of elements in the queue
    int         capacity;      // Maximum number of elements that fit in the queue
    int         element_size;  // The size of a storage element in bytes
    LockObject* lock;          // The lock object used by mutexes
    bool        initialized;   // Flag indicating the queue has been initialized
} CircularQueue_t;

/**
 * @brief Initializes the queue object
 *
 * @param queue     Pointer to an uninitialized circular queue object
 * @param capacity  Queue capacity to allocate
 *
 * @return  0 on success; error code otherwise
 *
 * @note    The application is responsible for ensuring the function is
 *          only called once for a given circular queue object.
 *          Also, the application must ensure this is the first API call
 *          for the circular queue before the circular queue object is passed
 *          to any other API in this module.
 */
int circular_queue_init(CircularQueue_t* queue, int capacity, int element_size) {
    if (queue == NULL || capacity <= 0 || element_size <= 0) {
        return -1;
    }

    // Initialize to a known-zero state. This sets initialized=false, size=0, etc.
    memset(queue, 0, sizeof(CircularQueue_t));

    queue->lock = CreateLockObject();
    if (queue->lock == NULL) {
        // The lock was not created
        return -1;
    }

    queue->data = malloc(capacity * element_size);
    if (queue->data == NULL) {
        ReleaseLockObject(queue->lock); // Clean up the created lock
        return -1;
    }

    queue->front = 0;
    queue->size = 0;
    queue->capacity = capacity;
    queue->element_size = element_size;

    // All operations on this circular queue will be allowed once
    // the initialized flag is set to true
    queue->initialized = true;

    return 0;
}

/**
 * @brief Uninitializes the queue object.
 *
 * @param queue   Pointer to the circular queue
 *
 * @return  0 on success; error code otherwise
 */
int circular_queue_deinit(CircularQueue_t* queue) {
    if (queue == NULL || !queue->initialized) {
        return -1;
    }

    // Don't proceed until other API functions have
    // released the circular queue handle.
    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    queue->initialized = false;

    if (queue->data != NULL) {
        free(queue->data);
        queue->data = NULL;
    }

    // Don't release the lock allowing other APIs in another thread
    // to run with an invalid handle; release the lock object instead
    // thus causing mutex_take() in other API functions to fail.
    // mutex_give(queue->lock);
    ReleaseLockObject(queue->lock);
    queue->lock = NULL;

    return 0;
}

/**
 * @brief Enqueues an element into an initialized circular queue
 *
 * @param queue    Pointer to the circular queue
 * @param element  Pointer to the element to enqueue
 *
 * @return  0 on success; error code otherwise
 */
int circular_enqueue(CircularQueue_t* queue, void* element) {
    if (queue == NULL || element == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    int location_index = (queue->front + queue->size) % queue->capacity;
    void* dest_addr = (uint8_t*)(queue->data) + (location_index * queue->element_size);
    memcpy(dest_addr, element, queue->element_size);

    if (queue->size < queue->capacity) {
        queue->size++;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }

    mutex_give(queue->lock);
    return 0;
}

/**
 * @brief Dequeues an element from an initialized circular queue
 *
 * @param queue    Pointer to the circular queue
 * @param element  Pointer to the buffer where to place the dequeued element
 *
 * @return  0 on success; error code otherwise
 */
int circular_dequeue(CircularQueue_t* queue, void* element) {
    if (queue == NULL || element == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    if (queue->size == 0) {
        mutex_give(queue->lock);
        return -1;
    }

    int data_offset = queue->front * queue->element_size;
    uint8_t* element_addr = (uint8_t*)queue->data + data_offset;
    memcpy(element, element_addr, queue->element_size);

    // Advance the front pointer by 1 and decrease the size.
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;

    mutex_give(queue->lock);
    return 0;
}

/**
 * @brief Returns whether the circular queue is full
 *
 * @param queue    Pointer to the circular queue
 * @param is_full  Pointer to place the is_full flag
 *
 * @return  -1 on error; 0 on success
 */
int circular_queue_is_full(CircularQueue_t* queue, bool* is_full) {
    if (queue == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    *is_full = queue->size == queue->capacity;

    mutex_give(queue->lock);
    return 0;

}

/**
 * @brief Returns whether the circular queue is empty
 *
 * @param queue    Pointer to the circular queue
 * @param is_empty  Pointer to place the is_empty flag
 *
 * @return  -1 on error; 0 on success
 */
int circular_queue_is_empty(CircularQueue_t* queue, bool* is_empty) {
    if (queue == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    *is_empty = queue->size == 0;

    mutex_give(queue->lock);
    return 0;
}

/**
 * @brief Returns the size of the queue (number of elements in the queue)
 *
 * @param queue    Pointer to the circular queue
 * @param size     Pointer to where to place the returned size
 *
 * @return  -1 on error; 0 on success
 */
int circular_queue_get_size(CircularQueue_t* queue, int* size) {
    if (queue == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    *size = queue->size;

    mutex_give(queue->lock);
    return 0;
}

/**
 * @brief Returns the element at the front of the circular queue
 *
 * @param queue    Pointer to the circular queue
 * @param element  Pointer to the buffer where to place the dequeued element
 *
 * @return  0 on success; error code otherwise
 */
int circular_queue_peek(CircularQueue_t* queue, void* element) {
    if (queue == NULL || element == NULL) {
        return -1;
    }

    if (mutex_take(queue->lock) != 0) {
        return -1;
    }

    if (!queue->initialized) {
        mutex_give(queue->lock);
        return -1;
    }

    if (queue->size == 0) {
        mutex_give(queue->lock);
        return -1;
    }

    int data_offset = queue->front * queue->element_size;
    uint8_t* element_addr = (uint8_t*)queue->data + data_offset;
    memcpy(element, element_addr, queue->element_size);

    mutex_give(queue->lock);
    return 0;
}
