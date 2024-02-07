#include "array4096.h"

#define N 1e3
void diskWriteSpeed(int fd) {
    int retw = 0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i=0; i<N; i++) {
        retw = write(fd, arr4096, 4096);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    float speed = 4096.0*N/duration/1e6;

    printf("Write speed: %.2f MB/s\n", speed);
}


#define BUFSIZE 4096*16

void diskReadSpeed(int src, int tar) {
    int n;
    char buf[BUFSIZE];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    while ((n=read(src, buf, BUFSIZE)) > 0) {
        if (write(tar, buf, n) != n) {
            printf("write error");
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    float speed = 4096.0*N/duration/1e6;
    
    printf("Read speed: %.2f MB/s\n", speed);
}

void diskSpeedtest() {
    printf("Disk Test Starting...\n");
    int fd = open("buffer.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // Disk write test
    diskWriteSpeed(fd);
    close(fd);
    
    int src_fd = open("buffer.txt", O_RDONLY);
    int tar_fd = open("buffertarget.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // Disk read test
    diskReadSpeed(src_fd, tar_fd);
    close(src_fd);
    close(tar_fd);
    // If deleting buffer files here, write speed is only 400 MB/s, read speed is also down.
//    remove("buffer.txt");
//    remove("buffertarget.txt");
}
