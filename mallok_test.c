/*
 * eduardk_hw6.c
 *
 *  Created on: Feb 27, 2018
 *  Author: Eduard Klimenko
 *
 *  This program tests the heap. Run the test and look at the output
 *   to see what is being tested (has many print statements explaining).
 */

#include "mallok.h"
#include <memory.h>

int main(int argc, char*argv[]) {
    char *ptrs[105] = { NULL }, *temp;
    create_pool(1000);
    int mallocCount = 0, failCount = 0;
    for (; mallocCount < 100;) {
        ptrs[mallocCount] = my_malloc(10);
        if (ptrs[mallocCount])
            mallocCount++;
    }
    printf("Allocated %d blocks of 10 bytes!\n", mallocCount);
    printf("Trying to allocate 1 more time! (this should fail).\n");
    ptrs[mallocCount + 1] = my_malloc(10);
    failCount = ptrs[mallocCount + 1] != NULL;
    printf("101th block is null! (false = 0) Result: %d\n", ptrs[100] == NULL);
    printf("End of test 1, number of failures: %d\n\n", failCount);
    free_pool();
    for (int i = 0; i < 105; i++)
        ptrs[mallocCount] = NULL;
    //printheap();
    failCount = 0;
    mallocCount = 0;

// **************************************************************
    create_pool(1000);
    for (int numTrials = 0; numTrials < 20; numTrials++) {
        //printheap();
        for (mallocCount = 0; mallocCount < 5;) {
            ptrs[mallocCount] = my_malloc(200);
            if (ptrs[mallocCount]) {
                mallocCount++;
            } else
                failCount++;
            //printf("%d\n", mallocCount);
        }
        //printheap();
        for (mallocCount = 0; mallocCount < 5; mallocCount++) {
            my_free(ptrs[mallocCount]);
            //printf("%d\n", mallocCount);
        }
        //printheap();
        for (mallocCount = 0; mallocCount < 5; mallocCount++) {
            ptrs[mallocCount] = NULL;
        }
        //printheap();
    }
    printf("Allocated and reallocated 5 blocks of 200 bytes 20 times!\n");
    printf("End of test 2, number of failures: %d\n\n", failCount);
    free_pool();
    for (int i = 0; i < 5; i++)
        ptrs[mallocCount] = NULL;
    //printheap();
    failCount = 0;
    mallocCount = 0;

    // **************************************************************
    create_pool(1000);
    for (mallocCount = 0; mallocCount < 5;) {
        ptrs[mallocCount] = my_malloc(200);
        if (ptrs[mallocCount]) {
            mallocCount++;
        } else
            failCount++;
        //printf("%d\n", mallocCount);
    }
    printf("Allocated %d blocks of 200 bytes!\n", mallocCount);
    printf("Freed middle block!\n");
    //printheap();
    my_free(ptrs[2]);
    ptrs[2] = NULL;
    ptrs[2] = my_malloc(210);
    printf("Allocating 210, is middle block is null? (false = 0) Result: %d\n",
            ptrs[2] == NULL);
    failCount += ptrs[2] != NULL;
    ptrs[2] = my_malloc(150);
    printf("Allocated 150, is middle block is null? (false = 0) Result: %d\n",
            ptrs[2] == NULL);
    failCount += ptrs[2] == NULL;
    //printheap();
    ptrs[5] = my_malloc(60);
    printf("Allocated 60, is block is null? (false = 0) Result: %d\n",
            ptrs[5] == NULL);
    failCount += ptrs[5] != NULL;
    ptrs[5] = my_malloc(50);
    printf("Allocated 50, is block is null? (false = 0) Result: %d\n",
            ptrs[5] == NULL);
    failCount += ptrs[5] == NULL;
    //printheap();
    printf("End of test 3, number of failures: %d\n\n", failCount);
    free_pool();
    for (int i = 0; i < 5; i++)
        ptrs[mallocCount] = NULL;
    //printheap();
    failCount = 0;
    mallocCount = 0;

    // **************************************************************
    create_pool(1000);
    for (mallocCount = 0; mallocCount < 5;) {
        ptrs[mallocCount] = my_malloc(200);
        if (ptrs[mallocCount]) {
            mallocCount++;
        } else
            failCount++;
        //printf("%d\n", mallocCount);
    }
    printf("Allocated %d blocks of 200 bytes!\n", mallocCount);
    //printheap();
    memset(ptrs[0], 'A', 200);
    for (temp = ptrs[0]; temp < ptrs[0] + 200; ++temp)
        failCount += *temp != 'A';
    printf("Filled first block with A's and checked each byte\n");
    memset(ptrs[1], 'B', 200);
    for (temp = ptrs[1]; temp < ptrs[1] + 200; ++temp)
        failCount += *temp != 'B';
    printf("Filled second block with B's and checked each byte\n");
    memset(ptrs[2], 'C', 200);
    for (temp = ptrs[2]; temp < ptrs[2] + 200; ++temp)
        failCount += *temp != 'C';
    printf("Filled third block with C's and checked each byte\n");
    memset(ptrs[3], 'D', 200);
    for (temp = ptrs[3]; temp < ptrs[3] + 200; ++temp)
        failCount += *temp != 'D';
    printf("Filled fourth block with D's and checked each byte\n");
    memset(ptrs[4], 'E', 200);
    for (temp = ptrs[4]; temp < ptrs[4] + 200; ++temp)
        failCount += *temp != 'E';
    printf("Filled fifth block with E's and checked each byte\n");
    printf("End of test 4, number of failures: %d\n\n", failCount);
    free_pool();
    for (int i = 0; i < 5; i++)
        ptrs[mallocCount] = NULL;
    //printheap();
    failCount = 0;
    mallocCount = 0;
    temp = NULL;

    // **************************************************************
    create_pool(1000);
    // 1 1000 byte block
    ptrs[0] = my_malloc(1000);
    printf("Allocated 1000, is block is null? (false = 0) Result: %d\n",
            ptrs[0] == NULL);
    failCount += ptrs[0] == NULL;
    //printheap();
    my_free(ptrs[0]);
    ptrs[0] = NULL;
    //printheap();
    //4  250 byte blocks
    for (mallocCount = 0; mallocCount < 4;) {
        ptrs[mallocCount] = my_malloc(250);
        if (ptrs[mallocCount]) {
            mallocCount++;
        } else
            failCount++;
        //printf("%d\n", mallocCount);
    }
    for (mallocCount = 0; mallocCount < 4; mallocCount++) {
        my_free(ptrs[mallocCount]);
        //printf("%d\n", mallocCount);
    }
    //printheap();
    for (mallocCount = 0; mallocCount < 4; mallocCount++) {
        ptrs[mallocCount] = NULL;
    }
    printf("Allocated and returned %d blocks of 250 bytes!\n", mallocCount);
    // 10 100 byte blocks
    for (mallocCount = 0; mallocCount < 10;) {
        ptrs[mallocCount] = my_malloc(100);
        if (ptrs[mallocCount]) {
            mallocCount++;
        } else
            failCount++;
        //printf("%d\n", mallocCount);
    }
    for (mallocCount = 0; mallocCount < 10; mallocCount++) {
        my_free(ptrs[mallocCount]);
        //printf("%d\n", mallocCount);
    }
    //printheap();
    for (mallocCount = 0; mallocCount < 10; mallocCount++) {
        ptrs[mallocCount] = NULL;
    }
    printf("Allocated and returned %d blocks of 10 bytes!\n", mallocCount);
    printf("End of test 5, number of failures: %d\n\n", failCount);
    free_pool();
    for (int i = 0; i < 5; i++)
        ptrs[mallocCount] = NULL;
    //printheap();
    failCount = 0;
    mallocCount = 0;

    // **************************************************************
    printf("Did not create a heap!\n");
    ptrs[0] = my_malloc(1000);
    printf("Allocated 1000, is block is null? (false = 0) Result: %d\n",
            ptrs[0] == NULL);
    failCount += ptrs[0] != NULL;
    printf("End of test 6, number of failures: %d\n\n", failCount);
    return 0;
}
