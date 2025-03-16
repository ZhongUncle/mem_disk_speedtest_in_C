# mem_disk_speedtest
CLI tool to measure speed of memory and disk using pure C.

## Usage
Just use below command to create directory `bin` and build project:

```
make
```

`mem_disk_speedtest` now is in `bin`, and use following command to run testing:

```
% ./bin/mem_disk_speedtest
Disk Test Starting...
Write speed:		1613.74 MB/s
Read speed:		1656.79 MB/s

Memory Test Starting...
Memory bandwidth:	27.53 GB/s
```


# Notices
It is heavy work and will uses about 24GB memory and disk for test.
