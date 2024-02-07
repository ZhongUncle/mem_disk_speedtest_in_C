#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

typedef struct node {
    struct node *next;  // In 64-bit system, it is 8 byte
    // Speed in 1 or 8 is highest, but 16 is normal case.
    char buffer[16];
} node_t;

#define NODES                     10000000
#define SIMPLE_ALLOCATOR_SIZE     1000000000UL

static void *start_ = NULL;
static void *cur_ = NULL;
static void *end_ = NULL;
static size_t counter_ = 0;

void memSpeedtest();
