# mem_disk_speedtest
CLI tool to measure speed of memory and disk using pure C.

## Usage
Just use below command to create directory `bin` and build project:
And you can run testing:

```
make
```

`mem_disk_speedtest` now is in `bin`, and use following command to run testing:

```
% ./bin/mem_disk_speedtest
Disk Test Starting...
Write speed:		1639.04 MB/s
Read speed:		1806.78 MB/s

Memory Test Starting...
Memory bandwidth:	26.72 GB/s
```

**This test will generate 2 files `buffer.txt` and `buffertarget.txt` in work path**. After testing, you can delete them. Why I don't delete them in source code or `make clean`?

Because if deleting these generated files in source code or `make clean`, the write speed is only 400 MB/s, the read speed is also down.
