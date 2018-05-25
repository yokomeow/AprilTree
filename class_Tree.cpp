#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include "class_Tree.hpp"

using namespace std;

SimpleTree::SimpleTree()
{
    this->root = NULL;
};

void SimpleTree::destroy(tree_element* cur_elem){
    if (cur_elem != NULL)
    {
        tree_element* r = cur_elem->right;
        tree_element* l = cur_elem->left;
        if(r) destroy(r);
        if(l) destroy(l);
        delete cur_elem;
    }
}

SimpleTree::~SimpleTree()
{
    if(root != NULL)
        destroy(root);
};

int SimpleTree::defHeight(tree_element* cur_elem)
{
    if(!cur_elem) return -1;

    int l = defHeight(cur_elem->left);
    int r = defHeight(cur_elem->right);

    if(!cur_elem->right && !cur_elem->left)
            {
                return cur_elem->height = 0;
            }
    return cur_elem->height = ((l > r)? l : r) + 1;
}

void SimpleTree::fixheight(tree_element* cur_elem)
{
    if(!cur_elem) return;
    defHeight(cur_elem);

    //if(cur_elem->left) fixheight(cur_elem->left);
    //if(cur_elem->right) fixheight(cur_elem->right);
}

int SimpleTree::height(tree_element* p)
{
    return (p? p->height : -1);
}

tree_element* SimpleTree::create(int value)
{
    // Allocate memmory
    tree_element* elem = (tree_element*)malloc(sizeof(tree_element));
    // Set value
    elem->value = value;
    // There is no next element, so set next to NULL
    elem->left = NULL;
    elem->right = NULL;
    elem->parent = NULL;
    elem->height = 0;
    return elem;
}

void SimpleTree::insert(int value)
{
    // Создали элемент физически
    tree_element* elem = this->create(value);
    tree_element* prom = this->root;

    if(this->root == NULL)
    {
        this->root = elem;
        return;
    }
    else this->insert2(prom, elem);
}

tree_element* SimpleTree::insert2(tree_element* prom, tree_element* elem)
{
    if((elem->value < prom->value) && (prom->left == NULL))
    {
        prom->left = elem;
        elem->parent = prom;
        //cout << elem->value << endl;
        //cout << elem->value << ' ' << defHeight(elem) << endl;
        defHeight(this->root);
        return balance(this->root);
    }

    if((elem->value >= prom->value) && (prom->right == NULL))
    {
        prom->right = elem;
        elem->parent = prom;
        //cout << elem->value << endl;
        //cout << elem->value << ' ' << defHeight(elem) << endl;
        defHeight(this->root);
        return balance(this->root);
    }

    if((elem->value < prom->value) && (prom->left != NULL))
    {
        prom = prom->left;
        insert2(prom, elem);
    }

    else if((elem->value >= prom->value) && (prom->right != NULL))
    {
        prom = prom->right;
        insert2(prom, elem);
    }
}

bool SimpleTree::exists(int value)
{
    return ((this->root != NULL)? (this->find(value)) : (NULL));
}

tree_element* SimpleTree::find(int value)
{
    tree_element* cur_element = this->root;
    if(this->root != NULL) return find2(cur_element, value);
    return NULL;
}

tree_element* SimpleTree::find2(tree_element* prom, int value)
{
    if(prom->value == value) return prom;

    if((prom->value >= value) && (prom->left != NULL))
        return find2(prom->left, value);

    if((prom->value <= value) && (prom->right != NULL))
        return find2(prom->right, value);
    return prom;
}

tree_element* SimpleTree::rotateright(tree_element* p) // правый поворот вокруг p
{
    cout << "rotate right" << endl;
    tree_element* q = p->left;
    q->parent = p->parent;
    p->left = q->right;
    if(q->right) q->right->parent = p;
    q->right = p;
    
    p->parent = q;
    defHeight(p);
    defHeight(q);
    //q->parent = NULL;
    if(!q->parent) this->root = q;
    else q->parent->left = q;
    return q;
}

tree_element* SimpleTree::rotateleft(tree_element* q) // левый поворот вокруг q
{
    cout << "rotate left" << endl;
    tree_element* p = q->right;
    p->parent = q->parent;
    q->right = p->left;
    if(p->left) p->left->parent = q;
    p->left = q; 
    q->parent = p;
    //q->right->parent = NULL;
    defHeight(q);
    defHeight(p);
    if(p->parent == NULL) this->root = p;
    else p->parent->right = p;
    return p;
}

tree_element* SimpleTree::balance(tree_element* p) // балансировка узла p
{
        defHeight(p);

    //if(p->right && (p->right->right || p->right->left)) balance(p->right);
    //if(!p->right) return NULL;
    //if(p->right->right) balance(p->right->right);
    if(p->right->right) balance(p->right);

    if(height(p->right) - height(p->left) == 2 && height(p->right->left) <= height(p->right->right))
    {
        rotateleft(p);
        return p;
    }

    if(height(p->right) - height(p->left) == 2 && height(p->right->left) > height(p->right->right))
    {
        rotateright(p->right);
        rotateleft(p);
        return p;
    }

    if(height(p->right) - height(p->right->right) == 2 && height(p->right->left) <= height(p->left))
    {
        rotateright(p);
        return p;
    }

    if(height(p->right) - height(p->right->right) == 2 && height(p->right->left) > height(p->right->right))
    {
        rotateleft(p->left);
        rotateright(p);
        return p;
    }

    return p; // балансировка не нужна
}
tree_element* SimpleTree::balanceleft(tree_element* p) // балансировка узла p
{
    defHeight(p);

    if(p->left) if(p->left->left) balanceleft(p->left);


    if(height(p->right) - height(p->left) == 2 && height(p->right->left) <= height(p->right->right))
    {
        rotateleft(p);
        return p;
    }

    if(height(p->right) - height(p->left) == 2 && height(p->right->left) > height(p->right->right))
    {
        rotateright(p->right);
        rotateleft(p);
        return p;
    }

    if(height(p->left) - height(p->right) == 2)
    {
        rotateright(p);
        return p;
    }

    if(height(p->right) - height(p->right->right) == 2 && height(p->right->left) > height(p->right->right))
    {
        rotateleft(p->left);
        rotateright(p);
        return p;
    }

    //if(p->left) if(p->left->left) balance(p->left->left);

   // if(p->parent) this->root = p->parent;
    return p; // балансировка не нужна
}
void SimpleTree::delete_tree(tree_element* cur_elem)
{
    if (cur_elem->left != NULL)
        delete_tree(cur_elem->left);

    if (cur_elem->right != NULL)
        delete_tree(cur_elem->right);

    free(cur_elem);
    cout << "Element deleted" << endl;
}

void SimpleTree::print()
{
    tree_element* cur_element = this->root;
    if (this->root != NULL)
        print2(cur_element);
    else
        return;
}

void SimpleTree::print2(tree_element* cur_element)
{
    if(cur_element-> left != NULL)
        print2(cur_element->left);

    printf("Element: %d ", cur_element->value);
    printf("Height: %d ", cur_element->height);
    
    if(cur_element->parent != NULL)
        printf("Parent: %d \n", cur_element->parent->value);

   if(cur_element-> right != NULL)
        print2(cur_element->right);
}

void SimpleTree::remove(int value)
{
    tree_element* elem = this->find(value);
    if(elem == NULL)
    {   
        printf("\nElement not found\n");
        return;
    }

    tree_element* cur_element = this->root;
    remove2(cur_element, elem);
}

tree_element* SimpleTree::Left(tree_element* prom)
{
    if(prom == NULL)
        return NULL;
    if(prom->left != NULL)
        return Left(prom->left);
    return prom;
}

tree_element* SimpleTree::Right(tree_element* prom)
{
    if(prom == NULL)
        return NULL;
    if(prom->right != NULL)
        return Right(prom->right);
    return prom;
}

void SimpleTree::remove2(tree_element* prom, tree_element* elem)
{
    if(elem->value < prom->value)
        return remove2(prom->left, elem);
    else if(elem->value > prom->value)
        return remove2(prom->right, elem);
    else
    {
        if(prom->left == NULL && prom->right == NULL)
        {
            if(prom->parent->left == prom)
                prom->parent->left = NULL;
            else
                prom->parent->right = NULL;
            free(prom);
        }
        else
        {
            tree_element* newroot = NULL;

            if(prom->left != NULL)
                newroot = Right(prom->left);
            else
                newroot = Left(prom->right);

            if(prom == this->root)
            {
                newroot->parent = prom->parent;
                newroot->right = prom->right; 
                prom->right->parent = newroot;
                newroot->left = prom->left->left;
                prom->left->left->parent = newroot;
                this->root = newroot;
                free(prom);
                return;
            }
            else if(prom->parent->left == prom)
                prom->parent->left = newroot;
            else
                prom->parent->right = newroot;

            newroot->parent = prom->parent;
            if(newroot->right) newroot->right = prom->right->right; 
            if(newroot->left) newroot->left = prom->left->left;

            free(prom);
        }
    }
}
