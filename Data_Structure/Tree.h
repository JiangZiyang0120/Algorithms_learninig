//
// Created by jiang-ziyang on 22-8-18.
//

#ifndef MAIN_CPP_TREE_H
#define MAIN_CPP_TREE_H

#include "DS_Header.h"
#include "Stack.h"
#include "Queue.h"

template<typename T, size_t ChildNum>
class Tree;


template<typename T, size_t ChildNum>
class Node : public std::enable_shared_from_this<Node<T,ChildNum>> {
    template<typename thisT, size_t thisChildNum>
    friend std::ostream &operator<<(std::ostream &os, Node<thisT, thisChildNum> &node);

    template<typename thisT, size_t thisChildNum>
    friend std::ostream &operator<<(std::ostream &os, Node<thisT, thisChildNum> &&node);

public:
    Node() : child(new std::shared_ptr<Node<T, ChildNum>>[ChildNum]) {}

    Node(T x) : data(x), child(new std::shared_ptr<Node<T, ChildNum>>[ChildNum]) {}

    void setData(T x);

    T getData();

    Node<T, ChildNum> *getPointer();

    void setChild(std::shared_ptr<Node<T, ChildNum>> childPointer, size_t index);

    void setChild(const T x, size_t index);

    void copyChild(std::shared_ptr<Node<T, ChildNum>> pointer);

    std::shared_ptr<Node<T, ChildNum>> getChild(size_t index);

    std::shared_ptr<Node<T, ChildNum>> getParent();

    bool isNoneChild();

private:
    T data;
    std::unique_ptr<std::shared_ptr<Node<T, ChildNum>>[]> child;
    std::weak_ptr<Node<T, ChildNum>> parent;
};


template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setData(T x) {
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
void Node<T, ChildNum>::setChild(std::shared_ptr<Node<T, ChildNum>> childPointer, size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    child[index] = childPointer;
    childPointer->parent = this->shared_from_this();
    return;
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setChild(const T x, size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    std::shared_ptr<Node<T, ChildNum>> pointer(std::make_shared<Node<T, ChildNum>>(x));
    setChild(pointer, index);
}


template<typename T, size_t ChildNum>
void Node<T, ChildNum>::copyChild(std::shared_ptr<Node<T, ChildNum>> pointer) {
    for (size_t i = 0; i != ChildNum; ++i)
        if (child[i])
            pointer->setChild(child[i], i);
}

template<typename T, size_t ChildNum>
std::shared_ptr<Node<T, ChildNum>> Node<T, ChildNum>::getChild(size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    return child[index];
}

template<typename T, size_t ChildNum>
std::shared_ptr<Node<T, ChildNum>> Node<T, ChildNum>::getParent() {
    return std::shared_ptr<Node<T,ChildNum>>(parent);
}

template<typename T, size_t ChildNum>
bool Node<T, ChildNum>::isNoneChild() {
    for (size_t i = 0; i != ChildNum; ++i)
        if (child[i])
            return false;
    return true;
}

template<typename T, size_t ChildNum>
std::ostream &operator<<(std::ostream &os, Node<T, ChildNum> &node) {
    return os << node.data;
}

template<typename T, size_t ChildNum>
std::ostream &operator<<(std::ostream &os, Node<T, ChildNum> &&node) {
    return os << node.data;
}

template<typename T>
using BinaryTree = Tree<T, 2>;

template<typename T, size_t ChildNum>
class Tree {
public:
    Tree() {}

    Tree(T x) : root(std::make_shared<Node<T, ChildNum>>(x)) {}

    template<typename Iterator>
    Tree<T, ChildNum>(Iterator begin, Iterator end): Tree<T, ChildNum>(){
        Queue<Node<T, ChildNum> *> thisQueue((end - begin) / ChildNum + 1);
        root = std::make_unique<Node<T, ChildNum>>(*(begin++));
        thisQueue.enroll(root);
        Node<T, ChildNum> *pointer;
        for (;;) {
            pointer = thisQueue.eject();
            for (size_t i = 0; i != 3 && begin != end; ++i, ++begin) {
                pointer->setChild(*begin, i);
                thisQueue.enroll(pointer->getChild(i));
            }
        }
    }

    /* The return value's first element contents this node's parent's depth and index.
     * The return value's second element is the node's childIndex.
     */
    std::pair<std::pair<size_t, size_t>, size_t> getParent(size_t depth, size_t index);

    //This index is a complete tree's index of the $(depth) layer
    void setData(std::shared_ptr<Node<T, ChildNum>> node, size_t depth, size_t index);

    void setData(T x, size_t depth, size_t index);

    void setRoot(std::shared_ptr<Node<T, ChildNum>> node){
        setData(node,1,0);
    }

    void setRoot(T x){
        setData(x,1,0);
    }

    size_t getDepth();

    BinaryTree<T> &&Tree2BinaryTree();

private:
    std::shared_ptr<Node<T, ChildNum>> root;

    void Tree2BinaryTree(Node<T, 2> *BTPointer, Node<T, ChildNum> *pointer);

    void getDepth(std::shared_ptr<Node<T, ChildNum>> pointer, size_t depth, size_t *maxDepth);
};


template<typename T, size_t ChildNum>
std::pair<std::pair<size_t, size_t>, size_t> Tree<T, ChildNum>::getParent(size_t depth, size_t index) {
    size_t parentIndex = index / ChildNum;
    size_t childIndex = index % ChildNum;
    return std::pair<std::pair<size_t, size_t>, size_t>(std::pair<size_t, size_t>(depth - 1, parentIndex), childIndex);
}

template<typename T, size_t ChildNum>
void Tree<T, ChildNum>::setData(std::shared_ptr<Node<T, ChildNum>> node, size_t depth, size_t index) {
    std::shared_ptr<Node<T, ChildNum>> pointer = root;
    if (depth == 1) {
        if (index != 0)
            throw std::overflow_error("The index is over the child's number");
        if (pointer && !pointer->isNoneChild())
            node->copyChild(pointer);
        root = node;
        return;
    } else if(depth == 2){
        if(!root)
            throw std::runtime_error("No valid trace to the node");
        if(root->getChild(index) && !root->getChild(index)->isNoneChild())
            node->copyChild(root->getChild(index));
        root->setChild(node,index);
        return;
    }
    Stack<size_t> childStack;
    for (; depth != 1; --depth) {
        childStack.push(index % ChildNum);
        index /= ChildNum;
    }
    while (childStack.elemNum() != 1) {
        pointer = pointer->getChild(childStack.pop());
        if (!pointer)
            throw std::runtime_error("No valid trace to the node");
    }
    auto childIndex = childStack.pop();
    if (pointer->getChild(childIndex) && !pointer->getChild(childIndex)->isNoneChild())
        node->copyChild(pointer->getChild(childIndex));
    pointer->setChild(node, childIndex);
    return;
}


template<typename T, size_t ChildNum>
void Tree<T, ChildNum>::setData(T x, size_t depth, size_t index) {
    std::shared_ptr<Node<T, ChildNum>> node(std::make_shared<Node<T, ChildNum>>(x));
    setData(node, depth, index);
}

template<typename T, size_t ChildNum>
void Tree<T, ChildNum>::getDepth(std::shared_ptr<Node<T, ChildNum>> pointer, size_t depth, size_t *maxDepth) {
    if (depth > *maxDepth)
        *maxDepth = depth;
    if (pointer->isNoneChild())
        return;
    else {
        for (size_t i = 0; i != ChildNum; ++i) {
            if (pointer->getChild(i)) {
                pointer = pointer->getChild(i);
                getDepth(pointer, depth + 1, maxDepth);
            }
        }
    }
}

template<typename T, size_t ChildNum>
size_t Tree<T, ChildNum>::getDepth() {
    size_t *maxDepth = new size_t(0);
    getDepth(root, 1, maxDepth);
    size_t depth = *maxDepth;
    delete maxDepth;
    return depth;
}

template<typename T, size_t ChildNum>
BinaryTree<T> &&Tree<T, ChildNum>::Tree2BinaryTree() {
    BinaryTree<T> BT(this->root->getData());
    auto BTPointer = BT.root;
    auto pointer = this->root;
    Tree2BinaryTree(BTPointer, pointer);
    return BT;
}

template<typename T, size_t ChildNum>
void Tree<T, ChildNum>::Tree2BinaryTree(Node<T, 2> *BTPointer, Node<T, ChildNum> *pointer) {
    if (pointer->isNoneChild())
        return;
    bool isFirstChild = true;
    for (size_t i = 0; i != ChildNum; ++i) {
        if (pointer->getChild(i)) {
            pointer = pointer->getChild(i);
            BTPointer->setChild(pointer->getData(), (isFirstChild) ? 0 : 1);
            BTPointer = BTPointer->getChild((isFirstChild) ? 0 : 1);
            isFirstChild = false;
            Tree2BinaryTree(BTPointer, pointer);
        }
    }
}

#endif //MAIN_CPP_TREE_H