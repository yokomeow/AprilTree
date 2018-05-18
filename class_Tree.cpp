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
    if (root != NULL)
    {
        tree_element* r = root->right;
        tree_element* l = root->left;
        destroy(r);
        destroy(l);
        delete root;
    }
}

SimpleTree::~SimpleTree()
{
    if(root != NULL)
        destroy(root);
};

unsigned char SimpleTree::height(tree_element* p)
{

    return p?p->height:0;
}

int SimpleTree::bfactor(tree_element* p)
{
    return height(p->right)-height(p->left);
}

void SimpleTree::fixheight(tree_element* p)
{
    if (p->right) fixheight(p->right);
    if (p->parent) (p->parent->height)++;

    p = this->root;

    int hr = height(p->right);
    int hl = height(p->left);
    p->height = (hl > hr? hl : hr)+1;

}

tree_element* SimpleTree::rotateright(tree_element* p) // ïðàâûé ïîâîðîò âîêðóã p
{
    cout << "rotate right" << endl;
    tree_element* q = p->left;
    p->left = q->right;
    q->right = p;
    p->parent = q;
    fixheight(p);
    fixheight(q);
   // q->parent = NULL;
    this->root = q;
    return q;
}

tree_element* SimpleTree::rotateleft(tree_element* q) // ëåâûé ïîâîðîò âîêðóã q
{
    cout << "rotate left" << endl;
    tree_element* p = q->right;
    q->right = p->left;
    p->left = q;
    q->parent = p;
    //q->right->parent = NULL;
    fixheight(q);
    fixheight(p);
    p->parent = NULL;
    this->root = p;
    return p;
}

tree_element* SimpleTree::balance(tree_element* p) // áàëàíñèðîâêà óçëà p
{
    fixheight(p);

    if( bfactor(p) > 1 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p) < -1 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }

    return p; // áàëàíñèðîâêà íå íóæíà
}

void SimpleTree::delete_tree(tree_element* cur_elem)
{
    if (cur_elem->left != NULL)
    {
        delete_tree(cur_elem->left);
    }

    if (cur_elem->right != NULL)
    {
       delete_tree(cur_elem->right);
    }

    free(cur_elem);
    cout << "Element deleted" << endl;
}

// Create new element, set its value to 'i', return pointer to new element
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
    elem->height = 1;
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
    else
    {
        this->insert2(prom, elem);
    }
}

tree_element* SimpleTree::insert2(tree_element* prom, tree_element* elem)
{
    //tree_element* output = prom;

    if ((elem->value < prom->value) && (prom->left == NULL))
    {
        prom->left = elem;
        elem->parent = prom;
        cout << elem->value << endl;
        return balance(this->root);
    }

    if ((elem->value >= prom->value) && (prom->right == NULL))
    {
        prom->right = elem;
        elem->parent = prom;
        cout << elem->value << endl;
        return balance(this->root);
    }

    if ((elem->value < prom->value) && (prom->left != NULL))
    {
        prom = prom -> left;
        insert2(prom, elem);
    }

    else if ((elem->value >= prom->value) && (prom->right != NULL))
    {
        prom = prom -> right;
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
    if (this->root != NULL) return find2(cur_element, value);
    return NULL;
}

tree_element* SimpleTree::find2(tree_element* prom, int value)
{
    if (prom->value == value) return prom;

    if ((prom->value != value) && (prom->left != NULL))
        find2(prom->left, value);

    if ((prom->value != value) && (prom->right != NULL))
        find2(prom->right, value);
}

void SimpleTree::print()
{
    tree_element* cur_element = this->root;
    if (this->root != NULL)
    print2(cur_element);
    else return;
}

void SimpleTree::print2(tree_element* cur_element)
{
    if (cur_element-> left != NULL)
    {
        print2(cur_element->left);
    }

    printf("Element: %d ", cur_element->value);
    printf("Height: %d ", cur_element->height);
    if (cur_element->parent != NULL) printf("Parent: %d \n", cur_element->parent->value);

   if (cur_element-> right != NULL)
    {
        print2(cur_element->right);
    }
}

void SimpleTree::remove(int value)
{
    tree_element* elem = this->find(value);
    if (elem == NULL)
    {   printf("\nElement not found\n");
        return;
    }
    tree_element* cur_element = this->root;
    remove2(cur_element, elem);
}

void SimpleTree::remove2(tree_element* prom, tree_element* elem)
{
    if (elem->value < prom->value)
        return remove2(prom->left, elem);
    else if (elem->value > prom->value)
        return remove2(prom->right, elem);
    else
    {
        if (prom->left == NULL && prom->right == NULL)
        {
            if (prom->parent->left == prom)
            prom->parent->left = NULL;
            else
            prom->parent->right = NULL;
            free(prom);
        }
        else
        {
            tree_element* newroot = NULL;

            if (prom->left != NULL)
            {
                newroot = Right(prom->left);
            }

            else
                newroot = Left(prom->right);

             if (prom == this->root)
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
            else if (prom->parent->left == prom)
                prom->parent->left = newroot;
            else
                prom->parent->right = newroot;

            newroot->parent = prom->parent;
            newroot->right = prom->right; 
            newroot->left = prom->left->left;

            free(prom);
        }
    }
}

tree_element* SimpleTree::Left(tree_element* prom)
{
    if (prom == NULL)
        return NULL;
    if (prom->left != NULL)
    {
        return Left(prom->left);
    }
    return prom;
}

tree_element* SimpleTree::Right(tree_element* prom)
{
    if (prom == NULL)
        return NULL;
    if (prom->right != NULL)
    {
        return Right(prom->right);
    }
    return prom;
}
