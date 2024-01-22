#include "array4096.h"

#define N 1e3
void diskWriteSpeed(int fd) {
    clock_t start = clock();

    for (int i=0; i<N; i++) {
        write(fd, arr4096, 4096);
    }
    
    clock_t end = clock();
    float speed = 4096.0f*N/(end-start);

    printf("4K write speed: %.2f MB/s\n", speed);
}


#define BUFSIZE 4096*16

void diskReadSpeed(int src, int tar) {
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

    printf("4K read speed: %.2f MB/s\n", speed);
}

void diskSpeedtest() {
    printf("Disk Test Starting...\n");
    //必须要确定每次测试都是新建的测试文件，不然会导致速度过低或者过高
    int fd = open("buffer.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    //硬盘写入测试
    diskWriteSpeed(fd);
    close(fd);
    
    int src_fd = open("buffer.txt", O_RDONLY);
    int tar_fd = open("buffertarget.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    //硬盘读取测试
    diskReadSpeed(src_fd, tar_fd);
    close(src_fd);
    close(tar_fd);
    //如果删除缓冲文件的话会写入速度会只有400MB/s，读取速度也有所下降
//    remove("buffer.txt");
//    remove("buffertarget.txt");
}
