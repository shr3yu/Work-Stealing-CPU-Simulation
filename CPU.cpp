#include <iostream>
#include "CPU.h"

CPU::CPU (int n): num_cores(n){
    //creates an array of cores
    cores = new Core[n];
}

CPU::~CPU (){
    delete [] cores;
    cores = nullptr;
}

//major functions
void CPU::spawn(int task){
    //check if task id is non-positive
    if (task > 0){
        // insert to the core with the lowest number of work
        int assigned_core = least_work();
        cores[assigned_core].insert(task);

        std::cout << "core " << assigned_core << " assigned task " << task << std::endl;

    } else{
        std::cout << "failure" << std::endl;
    }
}

void CPU::run(int core){
    if (core< 0 || core>= num_cores){
        std::cout << "failure" << std::endl;
        return;
    } 

    // if there is no tasks to be ran in that queue
    if (cores[core].size == 0){
        std::cout << "core " << core << " has no tasks to run" << std::endl;
        steal(core);
        return;
    }
    
    // run the task: pop front of queue
    int poped_task = cores[core].pop_front();
    std::cout << "core " << core << " is running task " << poped_task << std::endl;

    // check if the queue is empty after running the task
    if (cores[core].size == 0){
        steal(core);
    }

}
void CPU::steal(int core){
// check if the queue is empty after running the task
    //assign work from the core with the largest amount of work to do
    // pop off back and then insert
    int biggest_core = most_work(core);
    if (cores[biggest_core].size != 0){ // check if the core has tasks before stealing
        int stolen_task = cores[biggest_core].pop_back();
        cores[core].insert(stolen_task);
    }
}

void CPU::sleep(int core){
    if (core< 0 || core>= num_cores){
        std::cout << "failure" << std::endl;
        return;
    } 

    // if there is no tasks to assign
    if (cores[core].size == 0){
        std::cout << "core " << core << " has no tasks to assign" << std::endl;
        return;
    }

    // distributes core's tasks to remaining cores
    // assign task to core with the least amount of work untill all tasks are reassigned

    // the assigned core can not be its own core
    while (cores[core].size > 0){
        int popped_task = cores[core].pop_back();
        int assigned_core = least_work(core);
        cores[assigned_core].insert(popped_task);
        std::cout << "task "<< popped_task << " assigned to core " << assigned_core << " "; 
    }
    std::cout << std::endl;
}

void CPU::shutdown(){
    bool removed = false;

    // pop all remaining tasks
    for (int i =0; i < num_cores; i++){
        while (cores[i].size>0){
            removed = true;
            int popped_task = cores[i].pop_front();
            std::cout << "deleting task " << popped_task << " from core "<< i << " ";
        }
    }
    if(removed){
        std::cout << std::endl;
    }

    if (!removed){
        std::cout << "no tasks to remove" << std::endl;
    }
}

void CPU::size(int core){
    if (core< 0 || core>= num_cores){
        std::cout << "failure" << std::endl;
        return;
    } 

    std::cout << "size is " << cores[core].size << std::endl;
}

void CPU::capacity(int core){
    if (core< 0 || core>= num_cores){
        std::cout << "failure" << std::endl;
        return;
    } 

    std::cout << "capacity is " << cores[core].capacity << std::endl;
}

//helper functions
int CPU::least_work(int core){
    int core_id = (core == 0) ? 1 : 0;
    int lowest_size = cores[core_id].size;

    for (int i = 0; i < num_cores; i++) {
        if (i == core) continue; // Skip the passed-in core
        
        int current_size = cores[i].size;
        if (current_size < lowest_size) {
            lowest_size = current_size;
            core_id = i;
        }
    }

    return core_id;
}

int CPU::most_work(int core){
    int core_id = (core == 0) ? 1 : 0;
    int biggest_size = cores[core_id].size;

    for (int i = 0; i < num_cores; i++){
        if (i == core) continue; // Skip the passed-in core

        int current_size = cores[i].size;
        if (current_size > biggest_size){
            biggest_size = current_size;
            core_id = i;
        }
    }

    return core_id;
}


//debugging
void CPU::printCPU(){
    for (int i =0; i < num_cores; i++){
        cores[i].print();
    }
}