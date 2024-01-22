#!/bin/zsh

cc -O3 src/main.c -o mem_disk_speedtest

./mem_disk_speedtest

#rm ./mem_disk_speedtest

## If deleting buffer files, the write speed is only 400 MB/s, read speed is also down.
#rm ./buffer.txt buffertarget.txt
