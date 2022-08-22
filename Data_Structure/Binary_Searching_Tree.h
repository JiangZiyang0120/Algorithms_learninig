//
// Created by jiang-ziyang on 22-8-21.
//

#ifndef MAIN_CPP_BINARY_SEARCHING_TREE_H
#define MAIN_CPP_BINARY_SEARCHING_TREE_H

#include "DS_Header.h"
#include "Tree.h"

template<typename T, class Leaves = Node<T, 2>>
class BinarySearchingTree : public BinaryTree<T, Leaves> {
public:
    BinarySearchingTree() : BinaryTree<T, Leaves>() {};

    explicit BinarySearchingTree(T x) : BinaryTree<T, Leaves>(x) {}

    template<typename Iterator>
    BinarySearchingTree(Iterator begin, Iterator end): BinaryTree<T, Leaves>(begin, end) {}

    std::shared_ptr<Leaves> search(T x);

    std::shared_ptr<Leaves> minimum();

    std::shared_ptr<Leaves> minimum(std::shared_ptr<Leaves> Node);

    std::shared_ptr<Leaves> maximum();

    std::shared_ptr<Leaves> maximum(std::shared_ptr<Leaves> Node);

    std::shared_ptr<Leaves> successor(std::shared_ptr<Leaves> Node);

    std::shared_ptr<Leaves> predecessor(std::shared_ptr<Leaves> Node);

    void insert(T x);

    void remove(std::shared_ptr<Leaves> Node);

private:
    void transPlant(std::shared_ptr<Leaves> originNode, std::shared_ptr<Leaves> plantNode);
};

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::search(T x) {
    auto pointer = this->getRoot();
    while (pointer && pointer->getData() != x) {
        if (x < pointer->getData())
            pointer = pointer->getLeftChild();
        else
            pointer = pointer->getRightChild();
    }
    return pointer;
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::minimum(std::shared_ptr<Leaves> Node) {
    if (!Node)
        throw std::runtime_error("This tree has no Node");
    while (Node->getLeftChild())
        Node = Node->getLeftChild();
    return Node;
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::minimum() {
    return minimum(this->getRoot());
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::maximum(std::shared_ptr<Leaves> Node) {
    if (!Node)
        throw std::runtime_error("This tree has no Node");
    while (Node->getRightChild())
        Node = Node->getRightChild();
    return Node;
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::maximum() {
    return maximum(this->getRoot());
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::successor(std::shared_ptr<Leaves> Node) {
    if (Node->getRightChild())
        return minimum(Node->getRightChild());
    auto branch = Node->getParent();
    while (branch && Node == branch->getRightChild()) {
        Node = branch;
        branch = Node->getParent();
    }
    return branch;
}

template<typename T, class Leaves>
std::shared_ptr<Leaves> BinarySearchingTree<T, Leaves>::predecessor(std::shared_ptr<Leaves> Node) {
    if (Node->getLeftChild())
        return minimum(Node->getLeftChild());
    auto branch = Node->getParent();
    while (branch && Node == branch->getLeftChild()) {
        Node = branch;
        branch = Node->getParent();
    }
    return branch;
}

template<typename T, class Leaves>
void BinarySearchingTree<T, Leaves>::insert(T x) {
    if (!this->getRoot())
        this->setRoot(x);
    auto preNode = this->getRoot();
    std::shared_ptr<Leaves> nextNode = preNode;
    while (nextNode && x != preNode->getData()) {
        preNode = nextNode;
        nextNode = (x > preNode->getData()) ? preNode->getRightChild() : preNode->getLeftChild();
    }
    if (x > preNode->getData())
        preNode->setRightChild(x);
    else if (x == preNode->getData());
    else
        preNode->setLeftChild(x);
}

template<typename T, class Leaves>
void BinarySearchingTree<T, Leaves>::remove(std::shared_ptr<Leaves> Node) {
    if(!Node)
        return;
    if (!Node->getLeftChild()) {
        transPlant(Node, Node->getRightChild());
    } else {
        if (!Node->getRightChild()) {
            transPlant(Node, Node->getLeftChild());
        } else {
            auto suc = successor(Node);
            if (Node->getRightChild() == suc) {
                transPlant(Node,Node->getRightChild());
            } else {
                transPlant(suc,suc->getRightChild());
                suc->setRightChild(Node->getRightChild());
                suc->setLeftChild(Node->getLeftChild());
                transPlant(Node,suc);
            }
        }
    }
}

template<typename T, class Leaves>
void BinarySearchingTree<T, Leaves>::transPlant(std::shared_ptr<Leaves> originNode, std::shared_ptr<Leaves> plantNode) {
    if(!originNode)
        throw std::runtime_error("Node originNode is NULL");
    if (!originNode->getParent())
        this->setRoot(plantNode);
    else if (originNode->getParent()->getLeftChild() == originNode)
        originNode->getParent()->setLeftChild(plantNode);
    else
        originNode->getParent()->setRightChild(plantNode);
}

#endif //MAIN_CPP_BINARY_SEARCHING_TREE_H
