// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.
// 05/13/2022 pragma once modification by Prof Sipantzi
// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#pragma once

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key,E> {
private:
  BSTNode<Key,E>* root;   // Root of the BST
  int nodecount;         // Number of nodes in the BST

  // Private "helper" functions
  void clearhelp(BSTNode<Key, E>*);
  BSTNode<Key,E>* inserthelp(BSTNode<Key, E>*,
                              const Key&, const E&);
  BSTNode<Key,E>* deletemin(BSTNode<Key, E>*);
  BSTNode<Key,E>* getmin(BSTNode<Key, E>*);
  BSTNode<Key,E>* removehelp(BSTNode<Key, E>*, const Key&);
  E* findhelp(BSTNode<Key, E>*, const Key&) const;
  void printhelp(BSTNode<Key, E>*, int) const;
  void vist(BSTNode<Key, E>*) const;


public:
  BST() {
      root = NULL;
      nodecount = 0;
  }  // Constructor
  
  //Note from Prof Sipantzi -- I've commented out the destructor
  //since you would have to change clearhelp() to make it work with
  //doubly-threaded trees and that is not part of the assignment.
  //~BST() { clearhelp(root); }            // Destructor

  void clear()   // Reinitialize tree
    { clearhelp(root); root = NULL; nodecount = 0; }

  // Insert a record into the tree.
  // k Key value of the record.
  // e The record to insert.
  void insert(const Key& k, const E& e) {
    root = inserthelp(root, k, e);
    nodecount++;
  }

  // Remove a record from the tree.
  // k Key value of record to remove.
  // Return: The record removed, or NULL if there is none.
  E* remove(const Key& k) {
    E* temp = findhelp(root, k);   // First find it
    if (temp != NULL) {
      root = removehelp(root, k);
      nodecount--;
    }
    return temp;
  }
  // Remove and return the root node from the dictionary.
  // Return: The record removed, null if tree is empty.
  E* removeAny() {  // Delete min value
    if (root != NULL) {
      E* temp = new E;
      *temp = root->element();
      root = removehelp(root, root->key());
      nodecount--;
      return temp;
    }
    else return NULL;
  }

  // Return Record with key value k, NULL if none exist.
  // k: The key value to find. */
  // Return some record matching "k".
  // Return true if such exists, false otherwise. If
  // multiple records match "k", return an arbitrary one.
  E* find(const Key& k) const { return findhelp(root, k); }

  // Return the number of records in the dictionary.
  int size() { return nodecount; }

  void print() const { // Print the contents of the BST
    if (root == NULL) cout << "The BST is empty.\n";
    else printhelp(root, 0);
  }

  void printInOrder() { //print in order function
      BSTNode<Key, E>* current;
      current = root; //setting the current node to root so the tree can be traversed
      while (current->getLB() == 1) //check if bit is 1, meaning it has a child, so while left has a child, it will continue to go left
     {
              current = current->left(); //setting the node to the left node 
     }
      while (current != NULL) //while loop for not NULL, allows the tree to be traversed until a NULL child is found, which breaks the loop
      {
          vist(current); //prints the node it is currently at
          current = findNext(current); //findNext function being set to the node, so the tree can continue to print
      }
  }

  void printReverse() //print reverse function, same logic as inorder, however done in reverse
  {
      BSTNode<Key, E>* current;
      current = root;//setting the current node to root so the tree can be traversed
      while (current->getRB() == 1)//check if bit is 1, meaning it has a child, so while right has a child, it will continue to go right
      {
          current = current->right();//setting the node to the right node 
      }
      while (current != NULL) //while loop for not NULL, allows the tree to be traversed until a NULL child is found, which breaks the loop
      {
          vist(current);//prints the node it is currently at
          current = findPrevious(current); //findPrevious function being set to the node, so the tree can continue to print
      }
  }

  BSTNode<Key, E>* findNext(BSTNode<Key, E>* root) //findNext function, helper function for inorder print to find the next node
  {
      if (root->getRB() == 0) //if statment for the rightBit, if the rightBit is 0, it is a threaded node, 
          //so it will return the pointer to the threaded node, and the inorder print can continue
      {
          return root->right();
      }
      root = root->right(); //set root to its right root
      while (root->getLB() != 0) //while leftbit has a child, set root to its left pointer, i.e. set left to its left child
      {
          root = root->left();
      }
      return root; //return the node,
  }
  BSTNode<Key, E>* findPrevious(BSTNode<Key, E>* root) //findPrevious function, same logic as inorder print, helper to print the nodes in reverse
  {
      if (root->getLB() == 0)//if statment for the rightBit, if the rightBit is 0, it is a threaded node, 
          //so it will return the pointer to the threaded node, and the inorder print can continue
      {
          return root->left(); 
      }
      root = root->left();//set root to its left root
      while (root->getRB() != 0) //while rightbit has a child, set root to its right pointer, i.e. set right to its right child
      {
          root = root->right();
      }
      return root; //return the node
  }
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key,E>* r) const {
    cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
  if (root == NULL) return;
  clearhelp(root->left());
  clearhelp(root->right());
  delete root;
}



// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
    if (root == NULL) //if root is NULL, so if there is not a node, create a new node
    {
        return new BSTNode<Key, E>(k, it, NULL, NULL);
    }
    else //if there is already a node
    {
            if (k < root->key()) //if the new value read in is smaller than the current value, execute here
            {
                if (!root->getLB()) //if there is not a leftbit, so if there is no left child
                {
                    BSTNode<Key, E>* tempNode; //make the new node
                    tempNode = new BSTNode<Key, E>(k, it, NULL, NULL); //constructing the node
                    tempNode->setRight(root); //threading the right pointer back up
                    tempNode->setLeft(root->left()); //pointing the node back at itself
                    root->setLeft(tempNode); //setting the parents left pointer to the new node
                    root->setLB(1); //setting leftbit to 1 to indicate that it has a child
                }
                else //if there is a left child, then move down the branch to the next left child
                {
                    root->setLeft(inserthelp(root->left(), k, it));
                }
            }
            else //if the new value read in is bigger than the current value, execute here
            {
                if (!root->getRB())//if there is not a rightbit, so if there is no right child
                {
                    BSTNode<Key, E>* tempNode;//make the new node
                    tempNode = new BSTNode<Key, E>(k, it, NULL, NULL);//constructing the node
                    tempNode->setLeft(root);//threading the left pointer back up
                    tempNode->setRight(root->right());//pointing the node back at itself
                    root->setRight(tempNode);//setting the parents right pointer to the new node
                    root->setRB(1);//setting rightbit to 1 to indicate that it has a child
                }
                else//if there is a right child, then move down the branch to the next right child
                {
                    root->setRight(inserthelp(root->right(), k, it));
                }
            }
    }
    return root;
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL)
    return rt;
  else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
  if (rt->left() == NULL) // Found min
    return rt->right();
  else {                      // Continue left
    rt->setLeft(deletemin(rt->left()));
    return rt;
  }
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
  if (rt == NULL) return NULL;    // k is not in tree
  else if (k < rt->key())
    rt->setLeft(removehelp(rt->left(), k));
  else if (k > rt->key())
    rt->setRight(removehelp(rt->right(), k));
  else {                            // Found: remove it
    BSTNode<Key, E>* temp = rt;
    if (rt->left() == NULL) {     // Only a right child
      rt = rt->right();         //  so point to right
      delete temp;
    }
    else if (rt->right() == NULL) { // Only a left child
      rt = rt->left();          //  so point to left
      delete temp;
    }
    else {                    // Both children are non-empty
      BSTNode<Key, E>* temp = getmin(rt->right());
      rt->setElement(temp->element());
      rt->setKey(temp->key());
      rt->setRight(deletemin(rt->right()));
      delete temp;
    }
  }
  return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
                              const Key& k) const {
  if (root == NULL) return NULL;          // Empty tree
  if (k < root->key())
    return findhelp(root->left(), k);   // Check left
  else if (k > root->key())
    return findhelp(root->right(), k);  // Check right
  else {
      E* temp = new E;
      *temp = root->element();
      return temp;  // Found it
  }
}


// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {
    if (root == NULL) return;           // Empty tree
    if (root->getLB()) //added check to see if it has a leftbit, indicating it has a child
    {
        printhelp(root->left(), level + 1);
    }
    for (int i = 0; i < level; i++)         // Indent to level
        cout << "  ";
    cout << root->key() << "\n";
    if (root->getRB()) //added check to see if it has a rightbit, indicating it has a child
    {
        printhelp(root->right(), level + 1);
    }
}