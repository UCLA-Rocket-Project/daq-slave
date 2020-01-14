#include "AVLtree.h"
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
/* AVL class definition */

void AVLtree::rebalance(AVLnode *n) {
    setBalance(n);
 
    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }
 
    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}
 

AVLnode* AVLtree::rotateLeft(AVLnode *a) {
    AVLnode *b = a->right;
    b->parent = a->parent;
    a->right = b->left;
 
    if (a->right != NULL)
        a->right->parent = a;
 
    b->left = a;
    a->parent = b;
 
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
 
    setBalance(a);
    setBalance(b);
    return b;
}
 

AVLnode* AVLtree::rotateRight(AVLnode *a) {
    AVLnode *b = a->left;
    b->parent = a->parent;
    a->left = b->right;
 
    if (a->left != NULL)
        a->left->parent = a;
 
    b->right = a;
    a->parent = b;
 
    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }
 
    setBalance(a);
    setBalance(b);
    return b;
}
 

AVLnode* AVLtree::rotateLeftThenRight(AVLnode *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}
 

AVLnode* AVLtree::rotateRightThenLeft(AVLnode *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}
 

int AVLtree::height(AVLnode *n) {
    if (n == NULL)
        return -1;
    return 1 + MAX(height(n->left), height(n->right));
}
 

void AVLtree::setBalance(AVLnode *n) {
    n->balance = height(n->right) - height(n->left);
}


AVLtree::AVLtree(void) : root(NULL) {}
 

AVLtree::~AVLtree(void) {
    delete root;
}
 

bool AVLtree::insert(uint16_t addr, uint16_t val) {
    if (root == NULL) {
        root = new AVLnode(addr, val, NULL);
    }
    else {
        AVLnode
            *n = root,
            *parent;
 
        while (true) {
            if (n->key.addr == addr)
                return false;
 
            parent = n;
 
            bool goLeft = n->key > addr;
            n = goLeft ? n->left : n->right;
 
            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode(addr, val, parent);
                }
                else {
                    parent->right = new AVLnode(addr, val, parent);
                }
 
                rebalance(parent);
                break;
            }
        }
    }
 
    return true;
}

Register *AVLtree::seek(uint16_t addr) {
    AVLnode *head = root;
    while(head != nullptr) {
        if(head->key.addr == addr) {
            return &(head->key);
        }
        else if(addr < head->key.addr) {
            head = head->left;
        }
        else {
            head = head->right;
        }
    }
    return nullptr;
}