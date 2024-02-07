# mem_disk_speedtest
Commandline tool to test speed of memory and disk.

## Usage
You can use GCC or Clang to compile this tool, but please remember add `-O3` flag. Because we need compiler to optimizate code.

```
cc -O3 src/main.c -o mem_disk_speedtest
```

And you can run testing:

```
./mem_disk_speedtest
```
 
This test will generate 2 files `buffer.txt` and `buffertarget.txt`. After testing, you can delete them. 

But why I don't delete them in source code or `build.sh`?

Because if deleting these generated files in source code or `build.sh`, the write speed is only 400 MB/s, the read speed is also down.
