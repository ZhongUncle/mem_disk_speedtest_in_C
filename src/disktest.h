#include "array4096.h"

#include <fcntl.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <chrono>

#define ThreadNums 6

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
    setvbuf(fd1, (char *)NULL, _IONBF, 0);
    setvbuf(fd2, (char *)NULL, _IONBF, 0);
    setvbuf(fd3, (char *)NULL, _IONBF, 0);
    setvbuf(fd4, (char *)NULL, _IONBF, 0);
    setvbuf(fd5, (char *)NULL, _IONBF, 0);
    setvbuf(fd6, (char *)NULL, _IONBF, 0);

    std::vector<std::thread> threads;
    threads.reserve(ThreadNums);

    threads.emplace_back(diskWriteTest, fd1);
    threads.emplace_back(diskWriteTest, fd2);
    threads.emplace_back(diskWriteTest, fd3);
    threads.emplace_back(diskWriteTest, fd4);
    threads.emplace_back(diskWriteTest, fd5);
    threads.emplace_back(diskWriteTest, fd6);


    auto start = std::chrono::system_clock::now();
    // Disk write test
    for (std::thread &t : threads)
    {
        t.join();
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    double speed = 6*4096.0*N / elapsed.count() * 1e9 / 1e6;

    printf("time: %.1ld, Write speed:\t\t%.2f MB/s\n", elapsed.count(), speed);

    fclose(fd1);
    fclose(fd2);
    fclose(fd3);
    fclose(fd4);
    fclose(fd5);
    fclose(fd6);
}

#define BUFSIZE 4096

// void diskReadTest(char* buf, int n, int size, FILE* fd)
// {
//     fread(buf, n, size, fd);
// }

void diskReadSpeed()
{
    // close disk buffer
    FILE *fd1 = fopen("./buffers/buffer1.txt", "r");
    // FILE *fd2 = fopen("./buffers/buffer2.txt", "r");
    // FILE *fd3 = fopen("./buffers/buffer3.txt", "r");
    // FILE *fd4 = fopen("./buffers/buffer4.txt", "r");
    // FILE *fd5 = fopen("./buffers/buffer5.txt", "r");
    // FILE *fd6 = fopen("./buffers/buffer6.txt", "r");
    setvbuf(fd1, (char *)NULL, _IONBF, 0);
    // setvbuf(fd2, (char *)NULL, _IONBF, 0);
    // setvbuf(fd3, (char *)NULL, _IONBF, 0);
    // setvbuf(fd4, (char *)NULL, _IONBF, 0);
    // setvbuf(fd5, (char *)NULL, _IONBF, 0);
    // setvbuf(fd6, (char *)NULL, _IONBF, 0);

    std::vector<std::thread> threads;
    threads.reserve(ThreadNums);

    char *buf1, *buf2, *buf3, *buf4, *buf5, *buf6;
    buf1 = (char*)calloc(4096*N, sizeof(char));
    // buf2 = (char*)calloc(4096*N, sizeof(char));
    // buf3 = (char*)calloc(4096*N, sizeof(char));
    // buf4 = (char*)calloc(4096*N, sizeof(char));
    // buf5 = (char*)calloc(4096*N, sizeof(char));
    // buf6 = (char*)calloc(4096*N, sizeof(char));

    threads.emplace_back(fread, buf1, sizeof(char), (long)(4096 * N), fd1);
    // threads.emplace_back(fread, buf2, sizeof(char), (long)(4096 * N), fd2);
    // threads.emplace_back(fread, buf3, sizeof(char), (long)(4096 * N), fd3);
    // threads.emplace_back(fread, buf4, sizeof(char), (long)(4096 * N), fd4);
    // threads.emplace_back(fread, buf5, sizeof(char), (long)(4096 * N), fd5);
    // threads.emplace_back(fread, buf6, sizeof(char), (long)(4096 * N), fd6);


    auto start = std::chrono::system_clock::now();
    // Disk read test
    // for (std::thread &t : threads)
    // {
    //     t.join();
    // }
    int n = fread(buf1, sizeof(char), 4096 * N, fd1);

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    double speed = 4096.0*N / elapsed.count() * 1e9 / 1e6;

    printf("Time: %.1ld, Read speed:\t\t%.2f MB/s\n", elapsed.count(), speed);

    fclose(fd1);
    // fclose(fd2);
    // fclose(fd3);
    // fclose(fd4);
    // fclose(fd5);
    // fclose(fd6);

    // remove("buffers/buffer1.txt");
    // remove("buffers/buffer2.txt");
    // remove("buffers/buffer3.txt");
    // remove("buffers/buffer4.txt");
    // remove("buffers/buffer5.txt");
    // remove("buffers/buffer6.txt");
}

void diskSpeedtest()
{
    printf("Disk Test Starting...\n");
    diskWriteSpeed();
    diskReadSpeed();
}