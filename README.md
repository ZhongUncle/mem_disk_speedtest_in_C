# mem_disk_speedtest
Commandline tool to test speed of memory and disk.

## Usage
Just use below command to create directory `bin` and build project:
And you can run testing:

```
make
```

`mem_disk_speedtest` now is in `bin`, and use following command to run testing:

```
% ./mem_disk_speedtest 
Disk Test Starting...
Write speed: 408.70 MB/s
Read speed: 1990.28 MB/s

Memory Test Starting...
Start Address: 0x7fb803700000, End Address: 0x7fb83f0aca00
Write/Copy Speed: 23.69 GB/s
Read Speed: 26.28 GB/s
```

**This test will generate 2 files `buffer.txt` and `buffertarget.txt` in work path**. After testing, you can delete them. Why I don't delete them in source code or `make clean`?

Because if deleting these generated files in source code or `make clean`, the write speed is only 400 MB/s, the read speed is also down.
