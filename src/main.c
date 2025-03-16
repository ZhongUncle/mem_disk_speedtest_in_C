#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include "disktest.h"
// change memtest to C++
#include "memtest.hpp"

int main(int argc, const char * argv[]) {
    diskSpeedtest();
    memSpeedtest();
    
    return 0;
}