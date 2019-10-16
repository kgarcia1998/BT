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

    while (z != root && z->parent->color == Color::RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBNode<T> *y = z->parent->parent->right;
            if (y == nullptr)
            {
                if (z == z->parent->right)
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
                if (y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
            }
        }
        else
        {
            RBNode<T> *y = z->parent->parent->left;
            if (y == nullptr)
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    right(z);
                }
                z->parent->color = Color::BLACK;
                z->parent->parent->color = Color::RED;
                left(z->parent->parent);
            }
            else
            {
                if (y->color == Color::RED)
                {
                    z->parent->color = Color::BLACK;
                    y->color = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;
                }
            }
        }
    }
    root->color = Color::BLACK;
}
template <typename T>
void RBTree<T>::left(RBNode<T> *x)
{
    RBNode<T> *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
template <typename T>
void RBTree<T>::right(RBNode<T> *x)
{
    RBNode<T> *y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

#endif
