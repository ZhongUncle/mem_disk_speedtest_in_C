#include "array4096.h"

#include <fcntl.h>
#include <unistd.h>

#define N 1e6
void diskWriteSpeed(FILE* fd) {
    int retw = 0;
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i=0; i<N; i++) {
        size_t written = fwrite(arr4096, sizeof(char), 4096, fd);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    double speed = 4096.0*N/duration/1e6;

    printf("Write speed:\t\t%.2f MB/s\n", speed);
}


#define BUFSIZE 4096

void diskReadSpeed(FILE* fd) {
    int n;
    char *buf;
    buf = (char*)calloc(4096*1e6, sizeof(char));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    n = fread(buf, sizeof(char), 4096*1e6, fd);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
    double speed = 4096.0*N/duration/1e6;
    
    printf("Read speed:\t\t%.2f MB/s\n", speed);
}

void diskSpeedtest() {
    printf("Disk Test Starting...\n");
    //close disk buffer
    FILE* fd = fopen("buffer.txt", "w+");
    // setvbuf(fd, (char *)NULL, _IONBF, 0); 
    // Disk write test
    diskWriteSpeed(fd);
    fclose(fd);
    
    FILE* src_fd = fopen("buffer.txt", "r");
    //close disk buffer
    // setvbuf(src_fd, (char *)NULL, _IONBF, 0);
    // Disk read test
    diskReadSpeed(src_fd);
    fclose(src_fd);
    // If deleting buffer files here, write speed is only 400 MB/s, read speed is also down.
//    remove("buffer.txt");
//    remove("buffertarget.txt");
}