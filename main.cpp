#include <iostream>
#include "Core.h"

int main(){
    Core *core = new Core();
    core->print();
    core->insert(34);
    core->print();
    core->insert(55);
    core->print();
    core->insert(6);
    core->print();
    core->insert(90);
    core->print();
    core->pop_front();
    core->print();
    core->insert(34);
    core->print();
    
}