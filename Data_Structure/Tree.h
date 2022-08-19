//
// Created by jiang-ziyang on 22-8-18.
//

#ifndef MAIN_CPP_TREE_H
#define MAIN_CPP_TREE_H

#include "DS_Header.h"

template<typename T, size_t ChildNum>
class Tree;


template<typename T, size_t ChildNum>
class Node {
public:
    Node() : child(new Node<T, ChildNum>[ChildNum]), parent(NULL) {
        setChildNULL();
    }

    Node(T x) : data(x), child(new Node<T, ChildNum>[ChildNum]), parent(NULL) {
        setChildNULL();
    }

    void setNode(T x);

    T getData();

    Node<T, ChildNum> *getPointer();

    void setChild(Node<T, ChildNum> *childPointer, size_t index);
    
    void setChild(T x, size_t index);

    Node<T, ChildNum> *getChild(size_t index);

    Node<T, ChildNum> *getParent();

    bool isNoneChild();
private:
    T data;
    std::unique_ptr<Node<T, ChildNum>> child;
    std::unique_ptr<Node<T, ChildNum>> parent;

    void setChildNULL();
};


template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setNode(T x) {
    data = x;
    return;
}

template<typename T, size_t ChildNum>
T Node<T, ChildNum>::getData() {
    return data;
}

template<typename T, size_t ChildNum>
Node<T, ChildNum> *Node<T, ChildNum>::getPointer() {
    return this;
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setChild(Node<T, ChildNum> *childPointer, size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    child[index] = childPointer;
    childPointer->parent = this;
    return;
}

template <typename T,size_t ChildNum>
void Node<T, ChildNum>::setChild(T x, size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    std::unique_ptr<Node<T,ChildNum>> pointer(new Node<T,ChildNum>(x));
    setChild(pointer,index);
}

template<typename T, size_t ChildNum>
Node<T, ChildNum> *Node<T, ChildNum>::getChild(size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    return child[index];
}

template<typename T, size_t ChildNum>
Node<T, ChildNum> *Node<T, ChildNum>::getParent() {
    return parent;
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setChildNULL() {
    for (size_t i = 0; i != ChildNum; ++i) {
        child[i] = NULL;
    }
}

template <typename T,size_t ChildNum>
bool Node<T, ChildNum>::isNoneChild() {
    for(size_t i = 0; i != ChildNum; ++i)
        if(child[i])
            return false;
    return true;
}

template<typename T>
using BinaryTree = Tree<T, 2>;

template<typename T, size_t ChildNum>
class Tree {
    Tree() : root(NULL) {};

    Tree(T x) : root(x) {}

    BinaryTree<T> &&Tree2BinaryTree();

private:
    std::unique_ptr<Node<T, ChildNum>> root;

    void Tree2BinaryTree(Node<T,2> *BTPointer, Node<T, ChildNum> *pointer);
};

template<typename T, size_t ChildNum>
BinaryTree<T> &&Tree<T, ChildNum>::Tree2BinaryTree() {
    BinaryTree<T> BT(this->root->getData());
    auto BTPointer = BT.root;
    auto pointer = this->root;
    Tree2BinaryTree(BTPointer,pointer);
    return BT;
}

template <typename T,size_t ChildNum>
void Tree<T, ChildNum>::Tree2BinaryTree(Node<T,2> *BTPointer, Node<T, ChildNum> *pointer) {
    if(pointer->isNoneChild())
        return;
    bool isFirstChild = true;
    for(size_t i = 0; i != ChildNum; ++i){
        if(pointer->getChild(i)) {
            pointer = pointer->getChild(i);
            BTPointer->setChild(pointer->getData(),(isFirstChild)?0:1);
            BTPointer = BTPointer->getChild((isFirstChild)?0:1);
            isFirstChild = false;
            Tree2BinaryTree(BTPointer,pointer);
        }
    }
}

#endif //MAIN_CPP_TREE_H
