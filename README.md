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
./bin/mem_disk_speedtest
```

**This test will generate 2 files `buffer.txt` and `buffertarget.txt` in work path**. After testing, you can delete them. Why I don't delete them in source code or `make clean`?

Because if deleting these generated files in source code or `make clean`, the write speed is only 400 MB/s, the read speed is also down.
