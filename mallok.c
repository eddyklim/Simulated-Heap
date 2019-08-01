/*
 * eduardk_hw6.c
 *
 *  Created on: Feb 27, 2018
 *  Author: Eduard Klimenko
 *
 *  This program simulates a heap using a linked list.
 */

#include "mallok.h"

// static head node of the linked list
// will always access the list using this pointer
static Block *head = NULL;

/*
 * This function creates the heap. First checks if there is an
 * existing heap and if not, attempt to allocate the requested
 * amount of memory. If allocation was complete, point head to
 * that location, and set default values to the node.
 */
void create_pool(int size) {
    if (head) {
        if (!head->free) {
            //printf("Heap is not free!, can't make a new heap!\n");
            return;
        }
    }
    //printf("Heap is free, making new heap!\n");
    void*newMem = malloc(size);
    // checks if memory was allocated
    if (newMem == NULL) {
        //printf("Error allocating memory for a new heap!\n");
        return;
    }
    if (head) {
        // frees the entire heap
        free(head->address);
        // frees the node
        free(head);
        // sets to null
        head = NULL;
    }
    if (newMem != NULL) {
        // allocates memory to head
        head = (Block*) malloc(sizeof(Block));
        // points to the full block of memory
        head->address = newMem;
        // sets the size allocated
        head->size = size;
        // sets the block to be free
        head->free = 1;
        // sets the next node to null since the pool is only in head
        head->next = NULL;
    }
    //printf("Created heap of size %d\n", size);
}

/*
 * This function allocates "memory" to the heap. Looks for a free block
 * with enough memory, if not found return null. If found, but size
 * requested is smaller than the block size, split the block. Else,
 * set the block status to not free.
 */
void *my_malloc(int size) {
    Block *current;
    current = head;
    //find available block
    while (current != NULL && (current->size < size || !current->free)) {
        current = current->next;
    }
    //find the first block
    if (current != NULL && current->size >= size && current->free) {
        // split block if requested size is smaller than block size
        if (current->size > size) {
            Block *temp;
            temp = (Block*) malloc(sizeof(Block));
            // moves the address to the correct position
            temp->address = (void*) ((char*) current->address + size);
            // sets the new size
            temp->size = current->size - size;
            temp->free = 1;
            temp->next = current->next;
            current->next = temp;
        }
        // sets the block to not free
        current->free = 0;
        current->size = size;
        //printf("allocated memory of size %d\n", size);
        return current->address;
    } else {
        //printf("could not allocate memory of size %d\n", size);
        return NULL;
    }
}

/*
 * This function frees a block of memory from the heap. Looks for the
 * block that was requested to be freed, if not found, return. If found,
 * and the blocks next to it are not free, set the block to free. Else,
 * set the previous node to the next node affectively removing the requested
 * block and grab the next node if it is free also.
 */
void my_free(void *block) {
    Block *prev, *current;
    prev = NULL;
    current = head;
    //look for address
    while (current != NULL && current->address != block) {
        prev = current;
        current = current->next;
    }
    // if not found return
    if (current == NULL)
        return;
    current->free = 1;
    // coalesce previous
    if (prev != NULL && prev->free) {
        prev->size += current->size;
        prev->next = current->next;
        free(current);
        current = prev;
    }
    // coalesce next
    if (current->next != NULL && current->next->free) {
        current->size += current->next->size;
        current->next = current->next->next;
        //free(next);
    }
    current = NULL;
    prev = NULL;
}

/*
 * This function frees the entire pool and sets the head to null.
 * This is done by using the my_free function to free nodes that
 * are not currently free. After iterating through the whole list,
 * this will coalesce the list back into the head. Then free the
 * head's address and the head itself and set to null.
 */
void free_pool() {
    // go through all nodes, if the node is not free, free it.
    // do this until there is a single node
    int count = 1;
    Block *cur, *prev;
    cur = head;
    prev = cur;
    while (cur) {
        if (!prev->free) {
            //printf("block %d isnt free\n", count);
            my_free(prev->address);
        }
        prev = cur;
        cur = cur->next;
        count++;
    }
    free(head->address);
    free(head);
    free(cur);
    head = NULL;
    cur = NULL;
    prev = NULL;
    //printf("freed pool\n");
}

// helper method to print each block size and status
//void printheap() {
//    if (head) {
//        int count = 1;
//        printf("Printing heap!\n");
//        Block *temp;
//        temp = head;
//        do {
//            printf("size of block %d is %d, free: %d\n", count, temp->size,
//                    temp->free);
//            count++;
//            temp = temp->next;
//        } while (temp);
//    } else
//        printf("heap is null\n");
//}
