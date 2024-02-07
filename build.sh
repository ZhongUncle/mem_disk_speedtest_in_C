#!/bin/zsh
cc -c -O0 src/memtest.c -o src/memtest.o
cc -O3 src/main.c src/memtest.o -o mem_disk_speedtest

./mem_disk_speedtest

# Remove generated files
rm ./mem_disk_speedtest src/memtest.o
## If deleting buffer files, the write speed is only 400 MB/s, read speed is also down.
rm ./buffer.txt buffertarget.txt
