#include <iostream>
#include "CPU.h"

int main(){
    CPU danny(3);
    danny.printCPU();
    danny.spawn(2);
    danny.printCPU();
    danny.spawn(20);
    danny.printCPU();
    danny.spawn(28);
    danny.printCPU();
    danny.spawn(24);
    danny.printCPU();
    danny.spawn(26);
    danny.printCPU();
    danny.sleep(0);
}