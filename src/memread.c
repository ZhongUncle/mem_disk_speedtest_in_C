#include "memtest.h"
#include "memread.h"

void memread(node_t *node, node_t *node3) {
    for (int i=0; i < NODES; i++) {
        node = node->next;
    }
    for (int i=0; i < NODES; i++) {
        node3 = node3->next;
    }
}
