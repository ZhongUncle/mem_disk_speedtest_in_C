// 改成CPP了
#include <time.h>
#include <thread>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

//由于这个值会被多个线程操作，所以要告诉编译器可能随时被改变，不稳定的（volatile）
//多线程一般都会用这个关键字
volatile size_t acum = 0;

// template <bool prefetch>
uint64_t sum(const uint8_t *data, size_t start, size_t end, size_t cache_line_size = 1) {
    uint64_t sum = 0;
    /**
     * 为什么这里要跳过cache_line_size大小呢？
     * 因为当我们访问一个地址的时候，如果这个地址不在缓存里，那么会去缓存里读取整一行，写入则是写入一整行。
     * 如果不跳过，那么在获取一行之后，一直在操作cache，而不是读取内存，这样获取的带宽当然很小了。
     * 你可能会错误的想，CPU那么快，那么多核心，这不应该也能测出来带宽吗？但不是，如果不跳的话，时间相当于
     * 内存读-cache写-计算-cache读，带宽利用率就下去了，测出来当然不满了。
     * 从侧面也可以看出来，cache可以让带宽使用率下降25倍，所以GPU的cache也很重要，这点太牛了。
     */
    for (size_t i = start; i < end; i += cache_line_size) {
        sum += data[i];
    }
    acum += sum;
    return acum;
}
// template <bool prefetch>
double estimate_bandwidth(size_t threads_count, const uint8_t* data, size_t data_volume) {
    std::vector<std::thread> threads;
    threads.reserve(threads_count);

    // 计算一个线程计算的段大小
    size_t segment_length = data_volume / threads_count;
    
    // cache_line_size一般为64Byte
    size_t cache_line_size = 64;

    //开始计时和分配内存
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if(threads_count == 1) {
        // sum<prefetch>(data, 0, segment_length, cache_line_size);
        sum(data, 0, segment_length, cache_line_size);
    } else {
        for (size_t i = 0; i < threads_count; i++) {
            // threads.emplace_back(sum<prefetch>, data, segment_length*i, segment_length*(i+1), cache_line_size);
            threads.emplace_back(sum, data, segment_length*i, segment_length*(i+1), cache_line_size);
        }
        for (std::thread &t : threads) {
            t.join();
        }
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);

    //计算带宽
    return data_volume/1e9/duration;
}


void memSpeedtest() {
    //测试数据
    size_t data_volume = 2*1024*1024*1024ULL; // 2 GB
    std::vector<uint8_t> data(data_volume);
    for (size_t i = 0; i < data_volume; i++) {
        data[i] = 1;
    }
    // std::thread::hardware_concurrency()可以获取当前设备CPU最大线程数量
    int threadNums = std::thread::hardware_concurrency();
    // 存放结果
    std::vector<double> results(threadNums, 0);
    // 运行3次，选最大的一次
    size_t N = 5;
    
    for(size_t threads = 1; threads <= threadNums; threads++) {
        // double bandwidth = estimate_bandwidth<false>(threads, data.data(), data_volume);
        double bandwidth = estimate_bandwidth(threads, data.data(), data_volume);
        for(size_t i = 0; i < N; i++) {
            // double curBandwidth = estimate_bandwidth<false>(threads, data.data(), data_volume);
            double curBandwidth = estimate_bandwidth(threads, data.data(), data_volume);
            if(curBandwidth > bandwidth) {
                bandwidth = curBandwidth;
            }
        }
        // 线程数量和内存带宽 GB/s
        results.insert(results.end(), bandwidth);
        // printf("%lu %.1f\n", threads, bandwidth);
    }

    auto maxBandwidth = std::max_element(results.begin(),results.end());
    std::cout << *maxBandwidth << std::endl;
}





// #include "memtest.h"
// #include "memread.h"

// static void init_alloc() {
//     if (start_ == NULL) {
//         int rc = posix_memalign(&start_, 32, SIMPLE_ALLOCATOR_SIZE);
//         if (rc != 0) {
//             printf("Error allocating %ld bytes for allocator!", SIMPLE_ALLOCATOR_SIZE);
//             exit(1);
//         }
//         memset(start_, 0, SIMPLE_ALLOCATOR_SIZE);
//         cur_ = start_;
//         end_ = start_ + SIMPLE_ALLOCATOR_SIZE;
//         printf("Start Address: %p, End Address: %p\n", start_, end_);
//     }
// }

// static void* simple_alloc(size_t size) {
//     if (cur_ + size <= end_) {
//       void *ptr = cur_;
//       cur_ += size;
//       counter_++;
//       return ptr;
//     } else {
//        printf("Error allocating %ld bytes!", size);
//     }
//     return NULL;
// }

// node_t *new_node(node_t *prev, const char *payload, size_t size) {
//     node_t *n = (node_t *) simple_alloc(sizeof(node_t));
//     if (n == NULL) {
//         printf("Error allocating %ld bytes for struct node!", sizeof(node_t));
//         exit(1);
//     }
//     // Copy the payload into the node
//     memcpy(n->buffer, payload, size);
//     n->next = NULL;

//     if (prev) {
//         prev->next = n;
//     }
//     return n;
// }

// void free_nodes(node_t *n) {
//     if (!n) return;
//     while (n->next) {
//         node_t *next = n->next;
//         free(n);
//         n = next;
//     }
// }

// void memSpeedtest() {
//     printf("\nMemory Test Starting...\n");
    
//     init_alloc();
//     // 1024 bytes
//     const char text[] = "This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text This is a text 123";
//     // printf("%ld\n", strlen(text));
//     node_t *node0 = new_node(NULL, text, strlen(text));
//     node_t * node = node0;
    
//     struct timespec start, end;
//     thread tr[28];
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     for (int i=0; i < NODES/28; i++) {
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//         thread (node = new_node(node, text, strlen(text)));
//     }
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double duration = (double)(end.tv_nsec-start.tv_nsec)/((double) 1e9) + (double)(end.tv_sec-start.tv_sec);
//     double size = 1024000000/1e9;
//     double speed = size/duration;
//     printf("Write/Copy Speed: %.2f GB/s\n", speed);

//     struct timespec rstart, rend;
//     clock_gettime(CLOCK_MONOTONIC, &rstart);
//     node->next = node0;
//     memread(node0);
//     clock_gettime(CLOCK_MONOTONIC, &rend);
//     double rduration = (double)(rend.tv_nsec-rstart.tv_nsec)/((double) 1e9) + (double)(rend.tv_sec-rstart.tv_sec);
//     double rspeed = size/rduration;
//     printf("Read Speed: %.2f GB/s\n\n", rspeed);

//     free(start_);
// }

// // #include <stdint.h>
// // #include <stdlib.h>
// // #include <stdio.h>
// // #include <string.h>
// // #include <stddef.h>
// // #include <sys/time.h>

// // typedef struct __attribute__((packed)) node {
// //     char buffer[24];
// //     struct node *next;
// // } node_t;

// // #define NODES                     1000000
// // #define SIMPLE_ALLOCATOR_SIZE     100000000UL

// // static void *start_ = NULL;
// // static void *cur_ = NULL;
// // static void *end_ = NULL;
// // static size_t counter_ = 0;



// // int main() {
// //     init_alloc();
// //     const char text[] = "This is a text";
// //     node_t *node0 = new_node(NULL, text, strlen(text));

// //     node_t * node = node0;
// //     struct timeval start, end;
// //     gettimeofday(&start, NULL);
// //     for (int i=1; i < NODES; i++) {
// //         node = new_node(node, text, strlen(text));
// //     }
// //     gettimeofday(&end, NULL);

// //     int duration = ((end.tv_sec - start.tv_sec) * 1000000) + (end.tv_usec - start.tv_usec);
// //     printf("%d Nodes creation took %d us\n", NODES, duration);

// //     free(start_);
// // }

