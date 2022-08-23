//
// Created by jiang-ziyang on 22-8-23.
//

#ifndef MAIN_CPP_RED_BLACK_TREE_H
#define MAIN_CPP_RED_BLACK_TREE_H

#include "DS_Header.h"
#include "Tree.h"
#include "Binary_Searching_Tree.h"

enum colorSet {
    RED, BLACK
};

static const char *colorChar[] = {
        "RED", "BLACK"
};

template<typename T>
class RedBlackNode : public Node<T, 2> {
public:
    RedBlackNode() : Node<T, 2>(), color(RED) {}

    explicit RedBlackNode(T x) : Node<T, 2>(x), color(RED) {}

    std::shared_ptr<Node<int, 2UL>> getPointer();

    virtual void setChild(std::shared_ptr<RedBlackNode<T>> childPointer, size_t index);

    virtual void setChild(T x, size_t index);

    virtual void setLeftChild(std::shared_ptr<RedBlackNode<T>> childPointer);

    virtual void setLeftChild(T x);

    virtual void setRightChild(std::shared_ptr<RedBlackNode<T>> childPointer);

    virtual void setRightChild(T x);

    std::shared_ptr<RedBlackNode<T>> getChild(size_t index);

    std::shared_ptr<RedBlackNode<T>> getLeftChild();

    std::shared_ptr<RedBlackNode<T>> getRightChild();

    std::shared_ptr<RedBlackNode<T>> getParent();

    std::string printColor();

    colorSet getColor();

    void setColor(colorSet c);

    std::string node2json(size_t tier);

private:
    colorSet color;
};

template<typename T>
std::shared_ptr<Node<int, 2UL>> RedBlackNode<T>::getPointer() {
    return std::dynamic_pointer_cast<RedBlackNode<T>>(this->shared_from_this());
}

template<typename T>
void RedBlackNode<T>::setChild(std::shared_ptr<RedBlackNode<T>> childPointer, size_t index) {
    if (index >= 2)
        throw std::overflow_error("The index is over the child's number");
    this->child[index] = childPointer;
    if (childPointer)
        childPointer->parent = this->shared_from_this();
}

template<typename T>
void RedBlackNode<T>::setChild(T x, size_t index) {
    if (index >= 2)
        throw std::overflow_error("The index is over the child's number");
    std::shared_ptr<RedBlackNode<T>> childPointer = std::make_shared<RedBlackNode<T>>(x);
    setChild(childPointer, index);
}

template<typename T>
void RedBlackNode<T>::setLeftChild(std::shared_ptr<RedBlackNode<T>> childPointer) {
    setChild(childPointer, 0);
}

template<typename T>
void RedBlackNode<T>::setLeftChild(T x) {
    std::shared_ptr<RedBlackNode<T>> pointer = std::make_shared<RedBlackNode<T>>(x);
    setLeftChild(pointer);
}

template<typename T>
void RedBlackNode<T>::setRightChild(std::shared_ptr<RedBlackNode<T>> childPointer) {
    setChild(childPointer, 1);
}

template<typename T>
void RedBlackNode<T>::setRightChild(T x) {
    std::shared_ptr<RedBlackNode<T>> pointer = std::make_shared<RedBlackNode<T>>(x);
    setRightChild(pointer);
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackNode<T>::getChild(size_t index) {
    if (index >= 2)
        throw std::overflow_error("The index is over the child's number");
    return std::dynamic_pointer_cast<RedBlackNode<T>>(this->child[index]);
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackNode<T>::getLeftChild() {
    return std::dynamic_pointer_cast<RedBlackNode<T>>(this->child[0]);
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackNode<T>::getRightChild() {
    return std::dynamic_pointer_cast<RedBlackNode<T>>(this->child[1]);
}

template<typename T>
std::shared_ptr<RedBlackNode<T>> RedBlackNode<T>::getParent() {
    return std::dynamic_pointer_cast<RedBlackNode<T>>(this->parent);
}

template<typename T>
std::string RedBlackNode<T>::printColor() {
    return colorChar[color];
}

template<typename T>
colorSet RedBlackNode<T>::getColor() {
    return color;
}

template<typename T>
void RedBlackNode<T>::setColor(colorSet c) {
    color = c;
}

template<typename T>
std::string RedBlackNode<T>::node2json(size_t tier) {
    std::ostringstream oss;
    oss << repeatString(tier - 1, "\t") << "{\n";
    if (this->isNoneChild())
        oss << repeatString(tier, "\t") << "\"children\": [],\n";
    else {
        oss << repeatString(tier, "\t") << "\"children\": [\n";
        bool isFirstChild = true;
        for (size_t i = 0; i != 2; ++i)
            if (this->getChild(i)) {
                oss << (isFirstChild ? "" : ",\n");
                oss << this->getChild(i)->node2json(tier + 2);
                isFirstChild = false;
            } else {
                oss << (isFirstChild ? "" : ",\n");
                oss << repeatString(tier + 1, "\t") << "{\n";
                oss << repeatString(tier + 2, "\t") << "\"children\": [],\n";
                oss << repeatString(tier + 2, "\t") << R"("name": ")" << "None" << "\"\n";
                oss << repeatString(tier + 1, "\t") << "}";
                isFirstChild = false;
            }
        oss << "\n" << repeatString(tier, "\t") << "],\n";
    }
    oss << repeatString(tier, "\t") << R"("name": ")" << this->getData() << "\",\n";
    oss << repeatString(tier, "\t") << R"("color": ")" << this->printColor() << "\"\n";
    oss << repeatString(tier - 1, "\t") << "}";
    return oss.str();
}

template<typename T, class Leaves = RedBlackNode<T>>
class RedBlackTree : public BinarySearchingTree<T, Leaves> {
public:
    RedBlackTree() : BinarySearchingTree<T, Leaves>() {};

    std::shared_ptr<Leaves> insert(T x);

private:
    void insertFixup(std::shared_ptr<Leaves> pointer);

    void leftRotate(std::shared_ptr<Leaves> pointer);

    void rightRotate(std::shared_ptr<Leaves> pointer);
};

template<typename T, class Leaves>
std::shared_ptr<Leaves> RedBlackTree<T, Leaves>::insert(T x) {
    BinarySearchingTree<T, Leaves> *BSTP = this;
    auto pointer = BSTP->insert(x);
    insertFixup(pointer);
    return pointer;
}

template<typename T, class Leaves>
void RedBlackTree<T, Leaves>::insertFixup(std::shared_ptr<Leaves> pointer) {
    std::shared_ptr<Leaves> nextPointer;
    while (pointer->getParent() && pointer->getParent()->getColor() == RED) {
        auto grandParent = pointer->getParent()->getParent();
        //Cause the root's color is BLACK, if pointer's parent exists, it's grandparent must exist.
        if (grandParent->getLeftChild() == pointer->getParent()) {
            nextPointer = grandParent->getRightChild();
            if (nextPointer && nextPointer->getColor() == RED) {
                pointer->getParent()->setColor(BLACK);
                nextPointer->setColor(BLACK);
                grandParent->setColor(RED);
                pointer = grandParent;
            } else {
                if (pointer == pointer->getParent()->getRightChild()) {
                    pointer = pointer->getParent();
                    leftRotate(pointer);
                }
                pointer->getParent()->setColor(BLACK);
                grandParent->setColor(RED);
                rightRotate(grandParent);
            }
        } else {
            nextPointer = grandParent->getLeftChild();
            if (nextPointer && nextPointer->getColor() == RED) {
                pointer->getParent()->setColor(BLACK);
                nextPointer->setColor(BLACK);
                grandParent->setColor(RED);
                pointer = grandParent;
            } else {
                if (pointer == pointer->getParent()->getLeftChild()) {
                    pointer = pointer->getParent();
                    rightRotate(pointer);
                }
                pointer->getParent()->setColor(BLACK);
                grandParent->setColor(RED);
                leftRotate(grandParent);
            }
        }
    }
    this->getRoot()->setColor(BLACK);
}

template<typename T, class Leaves>
void RedBlackTree<T, Leaves>::leftRotate(std::shared_ptr<Leaves> pointer) {
    auto RC = pointer->getRightChild();
    pointer->setRightChild(RC->getLeftChild());
    if (!pointer->getParent())
        this->setRoot(RC);
    else if (pointer->getParent()->getLeftChild() == pointer)
        pointer->getParent()->setLeftChild(RC);
    else
        pointer->getParent()->setRightChild(RC);
    RC->setLeftChild(pointer);
}

template<typename T, class Leaves>
void RedBlackTree<T, Leaves>::rightRotate(std::shared_ptr<Leaves> pointer) {
    auto LC = pointer->getLeftChild();
    pointer->setLeftChild(LC->getRightChild());
    if (!pointer->getParent())
        this->setRoot(LC);
    else if (pointer->getParent()->getLeftChild() == pointer)
        pointer->getParent()->setLeftChild(LC);
    else
        pointer->getParent()->setRightChild(LC);
    LC->setRightChild(pointer);
}

#endif //MAIN_CPP_RED_BLACK_TREE_H