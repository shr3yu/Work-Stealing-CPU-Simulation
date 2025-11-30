#include <iostream>

class Core{
    public:
    int size; // number of tasks in queque
    int capacity; // total tasks that can be stored
    int *deque;

    Core();// initalize array to be of size n
    ~Core();

    void insert(int task);
    int pop_front();
    int pop_back();

    //debugging
    void print();
    
    private:
    int front;
    int rear; 
    void resize();

};