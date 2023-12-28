#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "disktest.h"
#include "memtest.h"

int main(int argc, const char * argv[]) {
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
    //如果删除的话会写入速度会只有400MB/s，读取速度也有所下降
//    remove("buffer.txt");
//    remove("buffertarget.txt");
    //未完成
//    copyMemoryBandwidth();
    return 0;
}

