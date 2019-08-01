/*
 * eduardk_hw6.c
 *
 *  Created on: Feb 27, 2018
 *  Author: Eduard Klimenko
 *
 *  Header file for this program.
 */

#ifndef MALLOK_H
#define MALLOK_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// node definition
typedef struct Block {
    // corresponding address
    void* address;
    // size of the block
    unsigned size;
    // status (free or in use)
    int free;
    // pointer to the next block
    struct Block *next;
} Block;

void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);
void free_pool();
//void printheap();

#endif
