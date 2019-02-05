//Liudmila Zyrianova
//CSCI 335
//10/28/2018
//Programming Assignment 2

#ifndef MY_TREES_MY_TREES_IMPL__
#define MY_TREES_MY_TREES_IMPL__

#include <iostream>
#include "my_trees.h"

template <typename T>
Node<T>:: Node (const T& nelem): elem(nelem), left (nullptr), right (nullptr), height (1) {};       //Constructor

template <typename T>
Node<T>:: Node (T&& nelem): elem(std:: move(nelem)), left (nullptr), right (nullptr), height (1) {};       //Constructor

template <typename T>
Node<T>:: Node (const T& nelem, Node<T>* nleft, Node<T>* nright): elem(nelem), left (nleft), right (nright), height (1) {};       //Modified copy constructor

template <typename T>
Node<T>:: Node (T&& nelem, Node<T>* nleft, Node<T>* nright): elem(std::move(nelem)), left (nleft), right (nright), height (1) {};       //Modified move constructor

template <typename T>
Node<T>:: Node (const T& nelem, Node<T>* nleft, Node<T>* nright, int h): elem(nelem), left (nleft), right (nright), height(h) {};       //Modified copy constructor

template <typename T>
Node<T>:: Node (T&& nelem, Node<T>* nleft, Node<T>* nright, int h): elem(std::move(nelem)), left (nleft), right (nright), height(h) {};       //Modified move constructor

template <typename T>
Node<T>:: Node (const Node<T>*& n): elem(n->elem), left (n->left), right (n->right), height(n->height) {};       //Modified move constructor

template <typename T>
Node<T>:: Node (Node<T>*&& n): elem(std::move(n->elem)), left (std::move(n->left)), right (std::move(n->right)), height(std::move(n->height)) {};       //Modified move constructor

template <typename T>
T& Node<T>:: getValue(){            //Returns reference to the value of the node
    return (this->elem);
};

template <typename T>
T Node<T>:: copyValue() const{      //Returns value of the node
    return (this->elem);
};

template <typename T>
Node<T>*& Node<T>:: getLeft() {     //Returns reference to Node* left
    return (this->left);
};

template <typename T>
Node<T>*& Node<T>:: getRight(){     //Returns reference to Node* right
    return (this->right);
};

template <typename T>
Node<T>* Node<T>:: copyLeft() const {       //Returns Node* left
    return (this->left);
};

template <typename T>
Node<T>* Node<T>:: copyRight() const{       //Returns Node* right
    return (this->right);
};

template <typename T>
int  Node<T>::HeightFrom() {                //Recursively finds the height from the current Node to the least close leaf
    int h = 0;
    if (this != nullptr) {
        h++;
        h += std:: max(this->getLeft()->HeightFrom(), this->getRight()->HeightFrom());
    }
    return h;
}

template <typename T>
int& Node<T>::AccessHeight() {          //Returns the reference to the field height
    return this->height;
};











template <typename T>
BSTcontainer<T>::BSTcontainer(): root(nullptr) {};            //Constructor

template <typename T>
void BSTcontainer<T>::Clean(Node<T> * & t) {            //Recursive destructor
    if (t != nullptr){
        Clean(t->getLeft());
        Clean(t->getRight());
        delete t;
    }
    t = nullptr;
};

template <typename T>
BSTcontainer<T>::~BSTcontainer() {            //Destructor
    Clean (root);
};

template <typename T>
int  BSTcontainer<T>::Height() {            //Returns the height of the BST
    if (this->root == nullptr) {
        return 0;
    } else {
        int h = this->root->AccessHeight();
        return h;
    }

}

template <typename T>
T BSTcontainer<T>:: getRootValue(){         //Returns the value stored in the root
    return (root->getValue());

};

template <typename T>
int BSTcontainer<T>::Count( Node<T> * & t ){        //Recursively returns the number of  Nodes in the subtree pointed by t
    int sum = 0;
    if (t != nullptr) {
        sum += Count(t->getLeft());
        sum += Count(t->getRight());
        return sum + 1;
    } else {
        return 0;
    }

};

template <typename T>
int BSTcontainer<T>::Size(){    //Returns the number of items in the container.
    return Count(root);
};

template <typename T>
void BSTcontainer<T>::Print(Node<T> * & t) {        //Recursively prints all the elements in the subtree pointed by t in the increasing order.
    if (t != nullptr) {
        if (t->getLeft()!= nullptr) {
            Print(t->getLeft());
        }
        std::cout << t->getValue() << ' ';
        if (t->getRight()!= nullptr) {
            Print(t->getRight());
        }
    }
};

template <typename T>
void BSTcontainer<T>::Print() {     //Prints the content of the tree in the ascending order.
    return Print (root);
};



template <typename T>
Node<T>*& BSTcontainer<T>:: findMax(Node<T> * & np) {       //Recursively finds and returns the reference to Node*, where Node has the max value in the subtree.
    if (np != nullptr) {
        if (np->getRight()!= nullptr) {
            return findMax(np->getRight());
        } else {
            return np;
        }
    } else return np;
};

template <typename T>
Node<T>*& BSTcontainer<T>:: findMin(Node<T> * &np) {        //Recursively finds and returns the reference to Node*, where Node has the min value in the subtree.
    if (np != nullptr) {
        if (np->getLeft()!= nullptr) {
            return findMin(np->getLeft());
        } else {
            return np;
        }
    } else return np;
};

template <typename T>
Node<T>* BSTcontainer<T>:: Search (const T & val, Node<T> * & t) {      //Returns the pointer to Node, which value is searching for in the subtree pointed by t.
    if (t == nullptr) { return nullptr; }
    else if( val < t->getValue())
        return Search( val, t->getLeft() );
    else if( val > t->getValue() )
        return Search( val, t->getRight() );
    else {return t;} // Match
};

template <typename T>
bool BSTcontainer<T>:: Search (const T & val) {     //Returns true if the item is in the container. False otherwise.
    if (Search (val, root) == nullptr){
        return false;
    } else {
        return true;
    }
};

template <typename T>
Node<T>* BSTcontainer<T>::operator[](T& val)        //Returns the reference to the item.
{
    if (Search (val, root) == nullptr){
        return nullptr;
    } else {
        return Search (val, root);
    }
}

template <typename T>
Node<T>* BSTcontainer<T>::operator[](T&& val)       //Returns the reference to the move(item).
{
    if (Search (val, root) == nullptr){
        return nullptr;
    } else {
        return Search (val, root);
    }
}

template <typename T>
void BSTcontainer<T>::Insert (const T & val, Node<T> * & t ) {      //Recursively inserts val in the subtree pointed by t.
    if (t == nullptr) {
        t = new Node<T>(val);
    } else if ( val < t->getValue()) {
        Insert( val, t->getLeft() );
    } else if ( val > t->getValue() ) {
        Insert( val, t->getRight() );
    } else if ( val == t->getValue()){
        std::cout<<"The attempt to insert "<< val<<" was ignored because the tree already contains this element.\n";
    }

    ProcessAfterChange(t);
};

template <typename T>
void BSTcontainer<T>::Insert (const T & val) {              //Insert val into the container.
    Insert (val, root);
};

template <typename T>
void BSTcontainer<T>::Insert (T && val, Node<T> * & t ) {           //Recursively inserts move(val) in the subtree pointed by t.
    if (t == nullptr) {
        t = new Node<T>(std:: move(val));
    } else if ( val < t->getValue()) {
        Insert( val, t->getLeft() );
    } else if ( val > t->getValue() ) {
        Insert( val, t->getRight() );
    } else if ( val == t->getValue()){
        std::cout<<"The attempt to insert "<< val<<" was ignored because the tree already contains this element.\n";
    }
    ProcessAfterChange(t);
};

template <typename T>
void BSTcontainer<T>::Insert (T && val) {           //Insert move(val) into the container.
    Insert (std:: move(val), root);
};

template <typename T>
void BSTcontainer<T>::Remove (const T & val, Node<T> * & t ) {          //Recursively removes val from the subtree pointed by t.
    if (t == nullptr) {
        //No item found of the tree is empty
        std::cout<<"The attempt to remove "<< val<<" was ignored because either the tree is empty or the tree doesn't contain this element.\n";
    } else if( val < t->getValue()) {
        Remove( val, t->getLeft() );
    } else if( val > t->getValue() ){
        Remove( val, t->getRight() );
    } else if ( val == t->getValue() ) {
        if ( (t->getLeft() == nullptr) && (t->getRight() == nullptr) ){         //Node pointed by t has no children.
            Node<T>* temp = t;
            t = nullptr;
            delete temp;
        } else if ( (t->getLeft() == nullptr) && (t->getRight() != nullptr) ){  //Node pointed by t has only right child.
            Node<T>* temp = t;
            t = t->getRight();
            delete temp;
        } else if ( (t->getLeft() != nullptr) && (t->getRight() == nullptr) ) { //Node pointed by t has only left child.
            Node<T>* temp = t;
            t = t->getLeft();
            delete temp;
        } else if ( (t->getLeft() != nullptr) && (t->getRight() != nullptr) ) { //Node pointed by t has two children.
            t->getValue() = (findMax(t->getLeft()))->getValue();
            Remove(t->getValue(), t->getLeft());
        }
    }
    ProcessAfterChange(t);
};

template <typename T>
void BSTcontainer<T>::Remove (const T & val) {      //Removes val from the container.
    Remove(val, root);
};

template <typename T>
Node<T>* BSTcontainer<T>::Copy( const Node<T>* np ) {               //Recursively copies the subtree pointed by t.
    if (np != nullptr){
        Node<T>* newNode = new Node<T> (np->copyValue(), Copy (np->copyLeft()),Copy (np->copyRight()));
        return newNode;
    } else {
        return nullptr;
    }
}

template <typename T>
void BSTcontainer<T>:: ProcessAfterChange (Node<T> * & t){      //Function that does nothing in case of BST and acts as Balance(t) in case of AVL.
    if (t== nullptr) {
        return;
    } else {
        int h1 = (t->getLeft() == nullptr) ? 0 : (t->getLeft()->AccessHeight());      //Height of left child
        int h2 = (t->getRight() == nullptr) ? 0 : (t->getRight()->AccessHeight());   //Height of right child
        t->AccessHeight() = std::max(h1, h2) + 1;     //New height of t
    }

};

template <typename T>
BSTcontainer<T>& BSTcontainer<T>::operator=( const BSTcontainer & tree ) {      //Copy assignment operator.
    Clean (root);
    root = Copy(tree.root);
    return *this;
}










template <typename T>
void AVLcontainer<T>:: RotateLeft( Node<T> * & n )          //Rotates left child.
{
    if (n== nullptr)
        return;
    else {
        Node<T> *leftCh = n->getLeft();
        n->getLeft() = leftCh->getRight();
        leftCh->getRight() = n;
        n->AccessHeight() = std:: max( (   (n->getLeft()== nullptr) ? 0 : (n->getLeft()->AccessHeight())   ) , (   (n->getRight()== nullptr) ? 0 :(n->getRight()->AccessHeight())   ) ) + 1;
        leftCh->AccessHeight() = std::max( (  (leftCh->getLeft()== nullptr) ? 0 : (leftCh->getLeft()->AccessHeight())   ) , ( n->AccessHeight()) ) + 1;
        n = leftCh;
    }
}

template <typename T>
void AVLcontainer<T>:: RotateRight( Node<T> * & n )         //Rotates right child.
{
    if (n== nullptr)
        return;
    else {
        Node<T> *rightCh = n->getRight();
        n->getRight() = rightCh->getLeft();
        rightCh->getLeft() = n;
        n->AccessHeight() = std:: max( (   (n->getRight()== nullptr) ? 0 : (n->getRight()->AccessHeight())   ) , (   (n->getLeft()== nullptr) ? 0 :(n->getLeft()->AccessHeight())   ) ) + 1;
        rightCh->AccessHeight() = std::max( (  (rightCh->getRight()== nullptr) ? 0 : (rightCh->getRight()->AccessHeight())   ) , ( n->AccessHeight()) ) + 1;
        n = rightCh;
    }

}

template <typename T>
void AVLcontainer<T>:: DoubleLeftRight( Node<T> * & n )     //Rotates firstly the right child of its left child, then its new left child.
{
    if (n== nullptr)
        return;
    else {
        RotateRight ( n->getLeft() );
        RotateLeft (n);
    }

}

template <typename T>
void AVLcontainer<T>:: DoubleRightLeft( Node<T> * & n )     //Rotates firstly the left child of its right child, then its new right child.
{
    if (n== nullptr)
        return;
    else {
        RotateLeft ( n->getRight() );
        RotateRight (n);
    }

}

template <typename T>
void AVLcontainer<T>:: Balance (Node<T> * & t) {            //Balances the subtree pointed by t.
    if (t== nullptr) {
        return;
    }
    if ( ( t->getLeft() != nullptr) && ( t->getRight()!= nullptr) ){            //Has two children.
        if ( ( t->getLeft()->AccessHeight() ) - ( t->getRight()->AccessHeight() ) > 1 ) {
            int h1 = (t->getLeft()->getLeft() == nullptr) ? 0 : (t->getLeft()->getLeft()->AccessHeight());      //Height of left left child
            int h2 = (t->getLeft()->getRight() == nullptr) ? 0 : (t->getLeft()->getRight()->AccessHeight() );   //Height of left right child
            if( h1 >= h2 ) {
                RotateLeft(t);
            } else {
                DoubleLeftRight(t);
            }
        } else if ( ( t->getRight()->AccessHeight() ) - ( t->getLeft()->AccessHeight() ) > 1 ) {
            int h1 = (t->getRight()->getRight() == nullptr) ? 0 : (t->getRight()->getRight()->AccessHeight());  //Height of right right child
            int h2 = (t->getRight()->getLeft()  == nullptr) ? 0 : (t->getRight()->getLeft()->AccessHeight()  ); //Height of right left child
            if( h1  >=  h2 ) {
                RotateRight(t);
            } else {
                DoubleRightLeft(t);
            }
        }
        int h1 = (t->getLeft() == nullptr) ? 0 : (t->getLeft()->AccessHeight());    //Height of left child
        int h2 = (t->getRight()  == nullptr) ? 0 : (t->getRight()->AccessHeight()  );   //Height of right child

        t->AccessHeight() = std:: max( h1, h2) + 1;     //New height of t

    } else  if ( ( t->getLeft() == nullptr) && ( t->getRight()!= nullptr) ){        //Has only right child
        if (t->getRight()->AccessHeight() == 1){
            t->AccessHeight() = 2;
        } else if (t->getRight()->getLeft() != nullptr) {
            DoubleRightLeft(t);
            return;
        } else if (t->getRight()->getRight() != nullptr){
            RotateRight(t);
            return;
        }

    } else  if ( ( t->getLeft() != nullptr) && ( t->getRight()== nullptr) ){        //Has only left child
        if (t->getLeft()->AccessHeight() == 1){
            t->AccessHeight() = 2;
        } else if (t->getLeft()->getRight() != nullptr) {
            DoubleLeftRight(t);
            return;
        } else if (t->getLeft()->getLeft() != nullptr){
            RotateLeft(t);
            return;
        }

    } else return;          //Has no children

};

template <typename T>
void AVLcontainer<T>:: ProcessAfterChange (Node<T> * & t){      //Function that does nothing in case of BST and acts as Balance(t) in case of AVL.
    Balance(t);
};



#endif //MY_TREES_MY_TREES_H