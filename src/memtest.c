#include "memtest.h"
#include "memread.h"

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
    // 8 bytes
    const char text[] = "123456789012345";
    node_t *node0 = new_node(NULL, text, strlen(text));
    node_t * node = node0;
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i=0; i < NODES; i++) {
        node = new_node(node, text, strlen(text));
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    double size = 2.4;
    double speed = size/duration;
    printf("Write/Copy Speed: %.2f GB/s\n", speed);

    struct timespec rstart, rend;
    clock_gettime(CLOCK_MONOTONIC, &rstart);
    node->next = node0;
    memread(node0);
    clock_gettime(CLOCK_MONOTONIC, &rend);
    double rduration = (double)(rend.tv_nsec-rstart.tv_nsec)/((double) 1e9) + (double)(rend.tv_sec-rstart.tv_sec);
    double rsize = 0.8;
    double rspeed = rsize/rduration;
    printf("Read Speed: %.2f GB/s\n\n", rspeed);
}

