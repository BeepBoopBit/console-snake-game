#include "includes.h"

void stuff(){
    std::cout << "watermelon" << std::endl;
}


int main(){
    std::thread water(stuff);

    return 0;
}