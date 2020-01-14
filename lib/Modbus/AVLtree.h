#ifndef AVLTREE
#define AVLTREE
#include <stdint.h>
#define NULL nullptr
#include "Register.h"
/* AVL node */
class AVLnode {
public:
    Register key;
    int balance;
    AVLnode *left, *right, *parent;
 
    AVLnode(uint16_t a, uint16_t v, AVLnode *p) : key(a, v), balance(0), parent(p),
                        left(NULL), right(NULL) {}
 
    ~AVLnode() {
        delete left;
        delete right;
    }
};
 
/* AVL tree */

class AVLtree {
public:
    AVLtree(void);
    ~AVLtree(void);
    bool insert(uint16_t addr, uint16_t val = 0);
    Register *seek(uint16_t addr);
 
private:
    AVLnode *root;
 
    AVLnode* rotateLeft          ( AVLnode *a );
    AVLnode* rotateRight         ( AVLnode *a );
    AVLnode* rotateLeftThenRight ( AVLnode *n );
    AVLnode* rotateRightThenLeft ( AVLnode *n );
    void rebalance                  ( AVLnode *n );
    int height                      ( AVLnode *n );
    void setBalance                 ( AVLnode *n );
    void clearNode                  ( AVLnode *n );
};
#endif