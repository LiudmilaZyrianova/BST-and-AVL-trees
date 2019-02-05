//Liudmila Zyrianova
//CSCI 335
//10/28/2018
//Programming Assignment 2

#ifndef MY_TREES_MY_TREES_H
#define MY_TREES_MY_TREES_H

#include <iostream>

template <typename T>
class Node {
private:
    T elem;
    Node<T>* left;
    Node<T>* right;
    int height;
public:
    Node () = default;              //Default constructor
    explicit Node (const T& nelem);          //Constructor
    explicit Node (T&& nelem);          //Constructor
    explicit Node (const T& nelem, Node<T>* nleft, Node<T>* nright);   //Modified copy constructor
    explicit Node (T&& nelem, Node<T>* nleft, Node<T>* nright);  //Modified move constructor
    explicit Node (const T& nelem, Node<T>* nleft, Node<T>* nright, int h);   //Modified copy constructor
    explicit Node (T&& nelem, Node<T>* nleft, Node<T>* nright, int h);  //Modified move constructor
    Node (const Node<T>*& n);   //Copy constructor
    Node (Node<T>* && n);  //Move constructor
    Node<T> & operator = (const Node<T>& nnode)= default;              //Copy assignment
    Node<T> & operator = (Node<T>&& nnode) = default;                   //Move assignment
    ~Node() = default;              //Destructor
    T& getValue();                     //Returns reference to the value of the node
    T copyValue() const ;                     //Returns value of the node
    Node<T>*& getLeft() ;                //Returns reference to Node* left
    Node<T>*& getRight() ;                //Returns reference to Node* right
    Node<T>* copyLeft() const;                //Returns Node* left
    Node<T>* copyRight() const;                //Returns Node* right
    int HeightFrom ();          //Recursively finds the height from the current Node to the least close leaf
    int&  AccessHeight ();      //Returns the reference to the field height
};

template <typename T>
class BSTcontainer{
protected:
    Node<T> * root;


    void Clean(Node<T> * & t);          //Recursive destructor
    int Count( Node<T> * & t );         //Recursively returns the number of  Nodes in the subtree pointed by t
    void Print (Node<T> * & t );        //Recursively prints all the elements in the subtree pointed by t in the increasing order.
    Node<T>*& findMax (Node<T>*& np);   //Recursively finds and returns the reference to Node*, where Node has the max value in the subtree.
    Node<T>*& findMin (Node<T>*& np);   //Recursively finds and returns the reference to Node*, where Node has the min value in the subtree.
    Node<T>* Search (const T & val, Node<T> * & t );    //Returns the pointer to Node, which value is searching for in the subtree pointed by t.
    void Insert (const T & val, Node<T> * & t );        //Recursively inserts val in the subtree pointed by t.
    void Insert (T && val, Node<T> * & t );             //Recursively inserts move(val) in the subtree pointed by t.
    void Remove (const T & val, Node<T> * & t);         //Recursively removes val from the subtree pointed by t.
    Node<T>* Copy (const Node<T>* np);                  //Recursively copies the subtree pointed by t.
    virtual void ProcessAfterChange (Node<T> * & t);    //Function maintains the heights of the nodes in case of BST and acts as Balance(t) in case of AVL.

public:
    BSTcontainer();     //Default constructor
    ~BSTcontainer();               //Destructor
    int Height();       //Returns the height of the BST
    T getRootValue();   //Returns the value stored in the root
    int Size();         //Returns the number of items in the container.
    void Print();       //Prints the content of the tree in the ascending order.
    bool Search (const T & val);    //Returns true if the item is in the container. False otherwise.
    Node<T>* operator[](T & val);   //Returns the reference to the item.
    Node<T>* operator[](T && val);  //Returns the reference to the move(item).
    void Insert (const T & val);    //Inserts val into the container.
    void Insert (T && val);         //Inserts move(val) into the container.
    void Remove (const T & val);    //Removes val from the container.
    BSTcontainer<T>& operator=( const BSTcontainer & tree );        //Copy assignment operator.

};

template <typename T>
class AVLcontainer : public BSTcontainer<T>
{
protected:
    void RotateLeft( Node<T> * & n );           //Rotates left child.
    void RotateRight( Node<T> * & n );          //Rotates right child.
    void DoubleLeftRight( Node<T> * & n );      //Rotates firstly the right child of its left child, then its new left child.
    void DoubleRightLeft( Node<T> * & n );      //Rotates firstly the left child of its right child, then its new right child.
    void Balance (Node<T> * & t);               //Balances the subtree pointed by t.
    virtual void ProcessAfterChange (Node<T> * & t); //Function that does nothing in case of BST and acts as Balance(t) in case of AVL.

};

#include "my_trees.cpp"

#endif //MY_TREES_MY_TREES_H
