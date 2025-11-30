#include <iostream>
#include "CPU.h"

int main(){

    CPU *processing_core = nullptr;
    std::string cmd;
    int n;
    int task;
    int core;

    // Variables
    while (std::cin >> cmd){
        if(cmd == "ON"){
            std::cin >> n;
            if (processing_core != nullptr){
                std::cout << "failure" << std::endl;
            } else {
                processing_core = new CPU (n);
                std::cout << "success" << std::endl;
            }
        } else if (cmd == "SPAWN"){
            std::cin >> task;
            processing_core->spawn(task);
            // processing_core->printCPU();
        } else if(cmd == "RUN"){
            std::cin >> core;
            processing_core->run(core);
            // processing_core->printCPU();
           
        } else if (cmd == "SLEEP"){
            std::cin >> core;
            processing_core->sleep(core);
            // processing_core->printCPU();
          
        } else if (cmd == "SHUTDOWN"){
           processing_core->shutdown();
        //    processing_core->printCPU();
        }else if (cmd == "SIZE"){
            std::cin >> core;
            processing_core->size(core);
            // processing_core->printCPU();
          
        }else if (cmd == "CAPACITY"){
            std::cin >> core;
            processing_core->capacity(core);
            // processing_core->printCPU();
        }else {
           break;
        }
    }

    //Clean up memory 
    if (processing_core != nullptr){
        delete processing_core;
    }

    return 0;
}