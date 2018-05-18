#include <iostream>
#include <stdio.h>

#include "class_C.hpp"

using namespace std;

typedef struct tree_element {
    int value;			// Element value
    struct tree_element* left;
    struct tree_element* right;
    struct tree_element* parent;
    int height;
} tree_element;

class SimpleTree: public Container
{
public:
    SimpleTree();
    ~SimpleTree();
    void insert(int value);
    bool exists(int value);
    void remove(int value);
    void print();

protected:
    tree_element* create(int i);
    tree_element* find(int i);
    tree_element* insert2(tree_element* root, tree_element* elem);
    tree_element* find2(tree_element* root, int value);
    void print2(tree_element* root);
    void delete_tree(tree_element* root);
    void remove2(tree_element* prom, tree_element* elem);
    tree_element* Left(tree_element* prom);
    tree_element* Right(tree_element* prom);
    unsigned char height(tree_element* p);
    int bfactor(tree_element* p);
    void fixheight(tree_element* p);
    tree_element* rotateright(tree_element* p);
    tree_element* rotateleft(tree_element* q);
    tree_element* balance(tree_element* p);
    void destroy(tree_element* cur_elem);

    tree_element* root;

};
