#include <iostream>
#include <stdio.h>
#include "class_Tree.hpp"
#include "class_C.hpp"

int main()
{
    Container* c = new SimpleTree();

    for(int i = 1; i < 10; i++)
        c->insert(i*i);

    printf("\nTree after creation:\n");
    c->print();

    if(c->exists(25))
        cout << "Search for value 25: found" << endl;

    if(!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "\nTree after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}