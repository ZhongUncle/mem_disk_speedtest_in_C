#include "array4096.h"


#define N 1e3
void memWriteSpeed(int fd) {
    clock_t start = clock();

    for (int i=0; i<N; i++) {
        write(fd, arr4096, 4096);
    }
    
    clock_t end = clock();
    float speed = 4096.0f*N/(end-start);

    printf("4K write speed: %f MB/s\n", speed);
}


#define BUFSIZE 4096*16

void memReadSpeed(int src, int tar) {
    int n;
    clock_t start = clock();

    char buf[BUFSIZE];
    while ((n=read(src, buf, BUFSIZE)) > 0) {
        if (write(tar, buf, n) != n) {
            printf("write error");
        }
    }
    clock_t end = clock();
    float speed = 4096.0*N/(end-start);

    printf("4K read speed: %f MB/s\n", speed);
}

