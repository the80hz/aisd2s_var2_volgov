#include <iostream>
#include "set.h"

// generator
size_t lcg(){
    static size_t x = 0;
    x = (1021*x+24631) % 116640;
    return x;
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
