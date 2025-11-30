#include <iostream>
#include "Core.h"

class CPU{
    private:
    int num_cores; //number of cores running in the CPU
    Core * cores;

    //helper functions
    int least_work(int core = -1); // returns the index of the core that has the least amount of tasks lined up
    int most_work(int core);
    void steal(int core);
    
    public:
    CPU(int n);
    ~CPU();

    //commands needed
    void spawn(int task);
    void run(int core);
    void sleep(int core);
    void shutdown();
    void size(int core);
    void capacity(int core);

    //debugging
    void printCPU();

};