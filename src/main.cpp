// #include <stdio.h>
// #include <time.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include "disktest.h"
// #include "memtest.h"

// int main(int argc, const char * argv[]) {
//     // diskSpeedtest();
//     memSpeedtest();
    
//     return 0;
// }

#include <iostream>
#include <chrono>
#include <cstdlib>

int main()
{
    int l_s = 1;
    for (int i = 0; i <= 10; i++)
    {
        l_s *= 10;
        double l_scalar = 2.0;

        double *l_A = new double[l_s];
        double *l_B = new double[l_s];
        double *l_C = new double[l_s];

        for (int i = 0; i < l_s; ++i)
        {
            l_A[i] = static_cast<double>(std::rand()) / RAND_MAX;
            l_B[i] = static_cast<double>(std::rand()) / RAND_MAX;
            l_C[i] = 0.0;
        }

        auto l_start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < l_s; ++i)
        {
            l_C[i] = l_A[i] + l_scalar * l_B[i];
        }

        auto l_end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> l_duration = l_end_time - l_start_time;

        double l_data_access_speed = 3.0 * l_s * sizeof(double) / l_duration.count() / (1024 * 1024 * 1024);

        std::cout << "STREAM Benchmark: " << l_data_access_speed << " GB/s" << std::endl;

        delete[] l_A;
        delete[] l_B;
        delete[] l_C;
    }

    return 0;
}