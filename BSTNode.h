// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 05/13/2022 pragma once modification by Prof Sipantzi
// This is the file to include for access to the complete binary node
// template implementation

#include "book.h"
#include "BinNode.h"

#pragma once

// Simple binary tree node implementation
template <typename Key, typename E>
class BSTNode : public BinNode<E> {
private:
  Key k;                  // The node's key
  E it;                   // The node's value
  BSTNode* lc;            // Pointer to left child
  BSTNode* rc;            // Pointer to right child
  bool leftBit : 1;       //leftbit, if 1 indiciates child, if 0 indicates thread
  bool rightBit : 1;      //rightbit, if 1 indicates child, if 0 indicates thread
public:
    // Two constructors -- with and without initial values
    BSTNode() { lc = rc = NULL; }
    BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL)
    {
        k = K; //variables from Sipantzi included here aswell
        it = e;
        lc = l;
        rc = r;
    }
    ~BSTNode() {}             // Destructor

    // Functions to set and return the value and key
    E& element() { return it; }
    void setElement(const E& e) { it = e; }
    Key& key() { return k; }
    void setKey(const Key& K) { k = K; }

    // Functions to set and return the children
    inline BSTNode* left() const { return lc; }
    void setLeft(BinNode<E>* b) 
    { 
        lc = (BSTNode*)b; 
        
    }
    inline BSTNode* right() const { return rc; }
    void setRight(BinNode<E>* b) { 
        rc = (BSTNode*)b; 
    }

    //These are the setter and getter functions for left and rightbit
    void setLB(bool lb)
    {
        leftBit = lb;
    }
    bool getLB()
    {
        return leftBit;
    }
    void setRB(bool rb)
    {
        rightBit = rb;
    }
    bool getRB()
    {
        return rightBit;
    }
  // Return true if it is a leaf, false otherwise
  bool isLeaf() { return (lc == NULL) && (rc == NULL); }
};
