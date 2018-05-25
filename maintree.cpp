#include <iostream>
#include <stdio.h>
#include "class_Tree.hpp"
#include "class_C.hpp"

class DebugTree : public SimpleTree
{
    void print()
    {
        tree_element* cur_element = this->root;
        //fixheight(cur_element);
        printSubTree(cur_element);
    }

    void printSubTree(tree_element* cur_element)
    {
        cerr << "Element: " << cur_element->value << " ";
        cerr << "Height: " << cur_element->height << " ";
        if(cur_element->parent != nullptr)
            cerr << "Parent: " << cur_element->parent->value << " ";
        else
            cerr << "Parent: -- ";

        if(cur_element->left != nullptr)
            cerr << "Left: " << cur_element->left->value << " ";
        else
            cerr << "Left: -- ";

        if(cur_element->right != nullptr)
            cerr << "Right: " << cur_element->right->value << " ";
        else
            cerr << "Right: -- ";

        cerr << endl;

        if (cur_element-> left != nullptr)
            printSubTree(cur_element->left);

        if (cur_element-> right != nullptr)
            printSubTree(cur_element->right);
    }
};

int main()
{
    Container* c = new DebugTree();

    for(int i = 1; i < 6; i++)
        c->insert(i*i);

    cerr << "Tree after creation:" << endl;
    c->print();

    c->remove(25);
    cerr << "Tree after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}
