#include "memtest.h"
#include "memread.h"

void memread(node_t *node) {
    for (int i=1; i < NODES; i++) {
        node = node->next;
    }
}
