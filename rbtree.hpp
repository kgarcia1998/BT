#ifndef __RBTREE__
#define __RBTREE__

#include <tree.hpp>
#include <rbnode.hpp>

template <typename T>
class RBTree : public Tree<T>
{
public:
    RBNode<T> *root;

    RBTree(const T key);
    void insert(const T val);
    void fixup(RBNode<T> *x);
    void left(RBNode<T> *x);
    void right(RBNode<T> *x);
};

template <typename T>
RBTree<T>::RBTree(const T key) : Tree<T>{key} {}

template <typename T>
void RBTree<T>::insert(const T val)
{

    RBNode<T> *y = nullptr;
    RBNode<T> *x = root;
    RBNode<T> *z = new RBNode<T>(val);
    while (x != nullptr)
    {
        y = x;
        if (z->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr)
    {
        root = z;
    }
    else if (z->data < y->data)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->right = nullptr;
    z->left = nullptr;
    z->color = Color::RED;
    fixup(z);
}

template <typename T>
void RBTree<T>::fixup(RBNode<T> *z)
{

    while (z->parent->color == Color::RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode<T> *y = z->parent->parent->right;
            if (y->color == Color::RED)
            {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->right)
            {
                z = z->parent;
                left(z);
            }
            z->parent->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            right(z->parent->parent);
        }
        else
        {
            RBNode<T> *y = z->parent->parent->left;
            if (y->color == Color::RED)
            {
                z->parent->color = Color::BLACK;
                y->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                z = z->parent->parent;
            }
            else if (z == z->parent->left)
            {
                z = z->parent;
                right(z);
            }
            z->parent->color = Color::BLACK;
            z->parent->parent->color = Color::RED;
            left(z->parent->parent);
        }
    }
    root->color = Color::BLACK;
}
template <typename T>
void RBTree<T>::left(RBNode<T> *x)
{
    RBNode<T> *y = nullptr;
    if (x->right->left)
    {
        y->right = x->right->left;
    }
    y->left = x->left;
    y->data = x->data;
    y->color = x->color;
    x->data = x->right->data;
    x->left = y;
    if (y->left)
    {
        y->left->parent = y;
    }
    if (y->right)
    {
        y->right->parent = y;
    }
    y->parent = x;
    if (x->right->right)
    {
        x->right = x->right->right;
    }
    else
    {
        x->right = nullptr;
    }
    if (x->right)
    {
        x->right->parent = x;
    }
}
template <typename T>
void RBTree<T>::right(RBNode<T> *x)
{
    RBNode<T> *y = nullptr;
    if (x->left->right)
    {
        y->left = x->left->right;
    }
    y->right = x->right;
    y->data = x->data;
    y->color = x->color;
    x->data = x->left->data;
    x->right = y;
    if (y->right)
    {
        y->right->parent = y;
    }
    if (y->left)
    {
        y->left->parent = y;
    }
    y->parent = x;
    if (x->left->left)
    {
        x->left = x->left->left;
    }
    else
    {
        x->left = nullptr;
    }
    if (x->left)
    {
        x->left->parent = x;
    }
}

#endif
