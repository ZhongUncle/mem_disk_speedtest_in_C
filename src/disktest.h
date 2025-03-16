#include "array4096.h"

#include <fcntl.h>
#include <unistd.h>
#include <thread>

#define ThreadNums 8

#define N 1e6

void diskWriteTest(FILE *fd)
{
    int retw = 0;

    for (int i = 0; i < N; i++)
    {
        size_t written = fwrite(arr4096, sizeof(char), 4096, fd);
    }
}

void diskWriteSpeed()
{
    // close disk buffer
    FILE *fd1 = fopen("./buffers/buffer1.txt", "w+");
    FILE *fd2 = fopen("./buffers/buffer2.txt", "w+");
    FILE *fd3 = fopen("./buffers/buffer3.txt", "w+");
    FILE *fd4 = fopen("./buffers/buffer4.txt", "w+");
    FILE *fd5 = fopen("./buffers/buffer5.txt", "w+");
    FILE *fd6 = fopen("./buffers/buffer6.txt", "w+");
    // setvbuf(fd, (char *)NULL, _IONBF, 0);

    std::vector<std::thread> threads;
    threads.reserve(ThreadNums);

    threads.emplace_back(diskWriteTest, fd1);
    threads.emplace_back(diskWriteTest, fd2);
    threads.emplace_back(diskWriteTest, fd3);
    threads.emplace_back(diskWriteTest, fd4);
    threads.emplace_back(diskWriteTest, fd5);
    threads.emplace_back(diskWriteTest, fd6);


    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Disk write test
    for (std::thread &t : threads)
    {
        t.join();
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec - start.tv_nsec) / ((double)1e9) + (double)(end.tv_sec - start.tv_sec);
    double speed = 6*4096.0 * N / duration / 1e6;

    printf("Write speed:\t\t%.2f MB/s\n", speed);

    fclose(fd1);
    fclose(fd2);
    fclose(fd3);
    fclose(fd4);
    fclose(fd5);
    fclose(fd6);
}

#define BUFSIZE 4096

void diskReadSpeed()
{
    // close disk buffer
    FILE *fd1 = fopen("./buffers/buffer1.txt", "r");
    FILE *fd2 = fopen("./buffers/buffer2.txt", "r");
    FILE *fd3 = fopen("./buffers/buffer3.txt", "r");
    FILE *fd4 = fopen("./buffers/buffer4.txt", "r");
    FILE *fd5 = fopen("./buffers/buffer5.txt", "r");
    FILE *fd6 = fopen("./buffers/buffer6.txt", "r");
    setvbuf(fd1, (char *)NULL, _IONBF, 0);
    setvbuf(fd2, (char *)NULL, _IONBF, 0);
    setvbuf(fd3, (char *)NULL, _IONBF, 0);
    setvbuf(fd4, (char *)NULL, _IONBF, 0);
    setvbuf(fd5, (char *)NULL, _IONBF, 0);
    setvbuf(fd6, (char *)NULL, _IONBF, 0);

    std::vector<std::thread> threads;
    threads.reserve(ThreadNums);

    char *buf1, *buf2, *buf3, *buf4, *buf5, *buf6;
    buf1 = (char*)calloc(4096*1e6, sizeof(char));
    buf2 = (char*)calloc(4096*1e6, sizeof(char));
    buf3 = (char*)calloc(4096*1e6, sizeof(char));
    buf4 = (char*)calloc(4096*1e6, sizeof(char));
    buf5 = (char*)calloc(4096*1e6, sizeof(char));
    buf6 = (char*)calloc(4096*1e6, sizeof(char));

    threads.emplace_back(fread, buf1, sizeof(char), 4096 * 1e6, fd1);
    threads.emplace_back(fread, buf2, sizeof(char), 4096 * 1e6, fd2);
    threads.emplace_back(fread, buf3, sizeof(char), 4096 * 1e6, fd3);
    threads.emplace_back(fread, buf4, sizeof(char), 4096 * 1e6, fd4);
    threads.emplace_back(fread, buf5, sizeof(char), 4096 * 1e6, fd5);
    threads.emplace_back(fread, buf6, sizeof(char), 4096 * 1e6, fd6);


    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    // Disk read test
    for (std::thread &t : threads)
    {
        t.join();
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec - start.tv_nsec) / ((double)1e9) + (double)(end.tv_sec - start.tv_sec);
    double speed = 6*4096.0 * N / duration / 1e6;

    printf("Read speed:\t\t%.2f MB/s\n", speed);

    fclose(fd1);
    fclose(fd2);
    fclose(fd3);
    fclose(fd4);
    fclose(fd5);
    fclose(fd6);
}

void diskSpeedtest()
{
    printf("Disk Test Starting...\n");
    diskWriteSpeed();
    diskReadSpeed();
}