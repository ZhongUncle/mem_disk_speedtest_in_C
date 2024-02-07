#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

typedef struct node {
    // Speed in 1 or 8 is highest, but 16 is normal case.
    char buffer[16];
    struct node *next;
} node_t;

#define NODES                     10000000
#define SIMPLE_ALLOCATOR_SIZE     1000000000UL

static void *start_ = NULL;
static void *cur_ = NULL;
static void *end_ = NULL;
static size_t counter_ = 0;

static void init_alloc() {
    if (start_ == NULL) {
        int rc = posix_memalign(&start_, 64, SIMPLE_ALLOCATOR_SIZE);
        if (rc != 0) {
            printf("Error allocating %ld bytes!", SIMPLE_ALLOCATOR_SIZE);
            exit(1);
        }
        memset(start_, 0, SIMPLE_ALLOCATOR_SIZE);
        cur_ = start_;
        end_ = start_ + SIMPLE_ALLOCATOR_SIZE;
        printf("Start Address: %p, End Address: %p\n", start_, end_);
    }
}

static void* simple_alloc(size_t size) {
    if (cur_ + size <= end_) {
      void *ptr = cur_;
      cur_ += size;
      counter_++;
      return ptr;
    } else {
       printf("Error allocating %ld bytes!", size);
    }
    return NULL;
}

node_t *new_node(node_t *prev, const char *payload, size_t size) {
    node_t *n = (node_t *) simple_alloc(sizeof(node_t));
    if (n == NULL) {
        printf("Error allocating %ld bytes for struct node!", sizeof(node_t));
        exit(1);
    }
    memcpy(n->buffer, payload, size);
    n->next = NULL;

    if (prev) {
        prev->next = n;
    }
    return n;
}

void free_nodes(node_t *n) {
    if (!n) return;
    while (n->next) {
        node_t *next = n->next;
        free(n);
        n = next;
    }
}

void memSpeedtest() {
    printf("\nMemory Test Starting...\n");
    
    init_alloc();
    // 16 bytes
    const char text[] = "123456789012345";
    node_t *node0 = new_node(NULL, text, strlen(text));
    node_t * node = node0;
    
    node_t *node2 = new_node(NULL, text, strlen(text));
    node_t * node3 = node2;
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i=0; i < NODES; i++) {
        node = new_node(node, text, strlen(text));
    }
    for (int i=0; i < NODES; i++) {
        node3 = new_node(node3, text, strlen(text));
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    double speed = 2/duration;
    printf("Write/Copy Speed: %.2f GB/s\n", speed);

    struct timespec rstart, rend;
    node->next = node0;
    node3->next = node2;
    clock_gettime(CLOCK_MONOTONIC, &rstart);
    for (int i=0; i < NODES; i++) {
        node = node->next;
    }
    for (int i=0; i < NODES; i++) {
        node3 = node3->next;
    }
    clock_gettime(CLOCK_MONOTONIC, &rend);
    double rduration = (double)(rend.tv_nsec-rstart.tv_nsec)/((double) 1e9) + (double)(rend.tv_sec-rstart.tv_sec);
    
    double rspeed = 2/rduration;
    printf("Read Speed: %.2f GB/s\n", rspeed);
}

