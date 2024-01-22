#!/bin/zsh

cc -O3 main.c

./a.out

#rm ./a.out

#//如果删除缓冲文件的话会写入速度会只有400MB/s，读取速度也有所下降
#rm ./buffer.txt buffertarget.txt
