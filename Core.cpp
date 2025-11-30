#include <iostream>
#include "Core.h"

Core::Core(): size(0), capacity(4), rear(-1), front(-1){ // initalize to capacity 4
    //create a new array of size n
    deque = new int[capacity]; 

    //initialize array to 0 (done for debugging purposes)
    for (int i = 0; i < capacity; i++){
        deque[i] = 0;
    }
}

Core::~Core(){
    delete[] deque;
    deque = nullptr;
}

void Core::insert(int task){
    if (size == 0){ // if queue is initially empty
        front = 0; 
        rear=0;
    } else {
        rear = (rear + 1) % capacity;
    }

    deque[rear] = task;
    size++;

    resize();
    
};

int Core::pop_front(){
    int task = deque[front];

    deque[front] = 0; //reset the value for better debugging readability

    // if there is a single element to remove
    if (rear == front){
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % capacity; //shift the front 
    }

    size--;
    resize();
    return task;
}


int Core::pop_back(){
    int task = deque[rear];

    deque[rear] = 0; // set for degbugging

    //For a single element in the list
    if (rear == front){
        front = -1;
        rear = -1;
    } else {
        rear = (rear - 1 + capacity) % capacity; //shift the front, plus capacity: might become negative 
    }

    size--;
    resize();
    return task;
}

void Core::resize(){
    int j=0;
    if (size <= (capacity/4) && capacity > 2){ // this ensures that when resized, the capacity 2 isn't halved
        int *new_deque = new int[capacity/2];
        for (int i = front; i != rear; i = (i+1) % capacity){
            new_deque[j] = deque[i];
            j++;
        }
        new_deque[j] = deque[rear]; // copy last element

        // make rest 0, for debugging
        for (int i = j+1; i < capacity/2; i++){
            new_deque[i] = 0;
        }

        delete[] deque;
        front = 0;
        rear = size -1;
        capacity = capacity /2;
        deque = new_deque;
    }else if(size == capacity){
        int *new_deque = new int[capacity*2];
        for (int i = front; i != rear; i = (i+1) % capacity){   
            new_deque[j] = deque[i];
            j++;
        }
        new_deque[j] = deque[rear]; // copy last element

        // make rest 0, for debugging
        for (int i = j+1; i < capacity*2; i++){
            new_deque[i] = 0;
        }
        delete[] deque;
        front = 0;
        rear = size -1;
        capacity = capacity * 2;
        deque = new_deque;
    }
    return;
}


//debugging
void Core::print(){
    std::cout<< "[ " ;
    for( int i =0; i < capacity; i++){
        std::cout << " " << deque[i] << ", ";
    }
    std::cout<< " ] " << "Size: " << size <<  " Capacity: " << capacity << " Rear: " << rear << " Front: " << front << std::endl; 
}
