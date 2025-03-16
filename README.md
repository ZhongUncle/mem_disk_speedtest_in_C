# mem_disk_speedtest
CLI tool to measure speed of memory and disk using pure ~C~C++ (use C++ is easier).

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

# Update
I change logic of code to test speed.

First, I want to use a utilized malloc and file I/O function to get peak bandwidth, it works bad.

So, I use multi-threads to do that, it works better.

# Notices
It is heavy work and will uses about 24GB memory and disk for test.

# Next
Maybe change code to full C++ is better.
