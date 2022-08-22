//
// Created by jiang-ziyang on 22-8-18.
//

#ifndef MAIN_CPP_TREE_H
#define MAIN_CPP_TREE_H

#include "DS_Header.h"
#include "Stack.h"
#include "Queue.h"

template<typename T, size_t ChildNum>
class Node;

template<typename T, size_t ChildNum, class Leaves>
class Tree;

template<typename T, class Leaves = Node<T, 2>>
class BinaryTree;

template<typename T, size_t ChildNum>
class Node : public std::enable_shared_from_this<Node<T, ChildNum>> {
public:
    Node() : child(new std::shared_ptr<Node<T, ChildNum>>[ChildNum]) {}

    explicit Node(T x) : data(x), child(new std::shared_ptr<Node<T, ChildNum>>[ChildNum]) {}

    void setData(T x);

    T getData();

    Node<T, ChildNum> *getPointer();

    void setChild(std::shared_ptr<Node<T, ChildNum>> childPointer, size_t index);

    void setChild(T x, size_t index);

    void setLeftChild(std::shared_ptr<Node<T, ChildNum>> childPointer);

    void setLeftChild(T x);

    void setRightChild(std::shared_ptr<Node<T, ChildNum>> childPointer);

    void setRightChild(T x);

    void copyChild(std::shared_ptr<Node<T, ChildNum>> pointer);

    std::shared_ptr<Node<T, ChildNum>> getChild(size_t index);

    std::shared_ptr<Node<T, ChildNum>> getLeftChild();

    std::shared_ptr<Node<T, ChildNum>> getRightChild();

    std::shared_ptr<Node<T, ChildNum>> getParent();

    bool isNoneChild();

private:
    T data;
    std::unique_ptr<std::shared_ptr<Node<T, ChildNum>>[]> child;
    std::shared_ptr<Node<T, ChildNum>> parent;
};


template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setData(T x) {
    data = x;
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
    if(childPointer)
        childPointer->parent = this->shared_from_this();
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setChild(T x, size_t index) {
    if (index >= ChildNum)
        throw std::overflow_error("The index is over the child's number");
    std::shared_ptr<Node<T, ChildNum>> pointer(std::make_shared<Node<T, ChildNum>>(x));
    setChild(pointer, index);
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setLeftChild(std::shared_ptr<Node<T, ChildNum>> childPointer) {
    setChild(childPointer, 0);
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setLeftChild(T x) {
    setChild(x, 0);
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setRightChild(std::shared_ptr<Node<T, ChildNum>> childPointer) {
    setChild(childPointer, ChildNum - 1);
}

template<typename T, size_t ChildNum>
void Node<T, ChildNum>::setRightChild(T x) {
    setChild(x, ChildNum - 1);
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
std::shared_ptr<Node<T, ChildNum>> Node<T, ChildNum>::getLeftChild() {
    return child[0];
}

template<typename T, size_t ChildNum>
std::shared_ptr<Node<T, ChildNum>> Node<T, ChildNum>::getRightChild() {
    return child[ChildNum - 1];
}

template<typename T, size_t ChildNum>
std::shared_ptr<Node<T, ChildNum>> Node<T, ChildNum>::getParent() {
    return std::shared_ptr<Node<T, ChildNum>>(parent);
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
    return os << node.getData();
}

template<typename T, size_t ChildNum>
std::ostream &operator<<(std::ostream &os, Node<T, ChildNum> &&node) {
    return os << node.getData();
}

template<typename T, size_t ChildNum, class Leaves = Node<T, ChildNum>>
class Tree {
    template<typename thisT, size_t thisChildNum, class thisLeaves>
    friend std::ofstream &operator<<(std::ofstream &output, Tree<thisT, thisChildNum, thisLeaves> &Tr);

    template<typename thisT, size_t thisChildNum, class thisLeaves>
    friend std::ostream &operator<<(std::ostream &os, Tree<thisT, thisChildNum, thisLeaves> &Tr);

public:
    Tree() = default;

    explicit Tree(T x) : root(std::make_shared<Leaves>(x)) {}

    template<typename Iterator>
    Tree(Iterator begin, Iterator end): Tree() {
        Queue<std::weak_ptr<Leaves>> thisQueue((end - begin) / ChildNum * (ChildNum - 1) + 2);
        root = std::make_shared<Leaves>(*(begin++));
        thisQueue.enroll(root);
        std::shared_ptr<Leaves> pointer;
        for (; begin != end;) {
            pointer = thisQueue.eject().lock();
            for (size_t i = 0; i != ChildNum && begin != end; ++i, ++begin) {
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
    void setData(std::shared_ptr<Leaves> node, size_t depth, size_t index);

    void setData(T x, size_t depth, size_t index);

    void setRoot(std::shared_ptr<Leaves> node) {
        setData(node, 1, 0);
    }

    void setRoot(T x) {
        setData(x, 1, 0);
    }

    size_t getDepth();

    BinaryTree<T> Tree2BinaryTree();

    std::shared_ptr<Leaves> getRoot();


private:
    void Tree2BinaryTree(std::shared_ptr<Node<T, 2>> BTPointer, std::shared_ptr<Leaves> pointer);

    void getDepth(std::shared_ptr<Leaves> pointer, size_t depth, size_t *maxDepth);

    std::shared_ptr<Leaves> root;
};


template<typename T, size_t ChildNum, class Leaves>
std::pair<std::pair<size_t, size_t>, size_t> Tree<T, ChildNum, Leaves>::getParent(size_t depth, size_t index) {
    size_t parentIndex = index / ChildNum;
    size_t childIndex = index % ChildNum;
    return std::pair<std::pair<size_t, size_t>, size_t>(std::pair<size_t, size_t>(depth - 1, parentIndex), childIndex);
}

template<typename T, size_t ChildNum, class Leaves>
void Tree<T, ChildNum, Leaves>::setData(std::shared_ptr<Leaves> node, size_t depth, size_t index) {
    std::shared_ptr<Leaves> pointer = root;
    if (depth == 1) {
        if (index != 0)
            throw std::overflow_error("The index is over the child's number");
        if (pointer && !pointer->isNoneChild())
            node->copyChild(pointer);
        root = node;
        return;
    } else if (depth == 2) {
        if (!root)
            throw std::runtime_error("No valid trace to the node");
        if (root->getChild(index) && !root->getChild(index)->isNoneChild())
            node->copyChild(root->getChild(index));
        root->setChild(node, index);
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
}


template<typename T, size_t ChildNum, class Leaves>
void Tree<T, ChildNum, Leaves>::setData(T x, size_t depth, size_t index) {
    std::shared_ptr<Leaves> node(std::make_shared<Leaves>(x));
    setData(node, depth, index);
}

template<typename T, size_t ChildNum, class Leaves>
void Tree<T, ChildNum, Leaves>::getDepth(std::shared_ptr<Leaves> pointer, size_t depth, size_t *maxDepth) {
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

template<typename T, size_t ChildNum, class Leaves>
size_t Tree<T, ChildNum, Leaves>::getDepth() {
    auto *maxDepth = new size_t(0);
    getDepth(root, 1, maxDepth);
    size_t depth = *maxDepth;
    delete maxDepth;
    return depth;
}

template<typename T, size_t ChildNum, class Leaves>
BinaryTree<T> Tree<T, ChildNum, Leaves>::Tree2BinaryTree() {
    BinaryTree<T> BT(this->root->getData());
    auto BTPointer = BT.getRoot();
    auto pointer = this->root;
    Tree2BinaryTree(BTPointer, pointer);
    return BT;
}

template<typename T, size_t ChildNum, class Leaves>
void
Tree<T, ChildNum, Leaves>::Tree2BinaryTree(std::shared_ptr<Node<T, 2>> BTPointer, std::shared_ptr<Leaves> pointer) {
    if (pointer->isNoneChild())
        return;
    size_t i = 0;
    for (; i != ChildNum; ++i) {
        if (pointer->getChild(i)) {
            BTPointer->setChild(pointer->getChild(i)->getData(), 0);
            Tree2BinaryTree(BTPointer->getChild(0), pointer->getChild(i));
            BTPointer = BTPointer->getChild(0);
            ++i;
            break;
        }
    }
    for (; i != ChildNum; ++i) {
        if (pointer->getChild(i)) {
            BTPointer->setChild(pointer->getChild(i)->getData(), 1);
            Tree2BinaryTree(BTPointer->getChild(1), pointer->getChild(i));
            BTPointer = BTPointer->getChild(1);
        }
    }
}

template<typename T, size_t ChildNum, class Leaves>
std::shared_ptr<Leaves> Tree<T, ChildNum, Leaves>::getRoot() {
    return root;
}

inline std::string repeatString(size_t tier, std::string &&str) {
    std::string returnStr;
    for (size_t i = 0; i != tier; ++i)
        returnStr.insert(returnStr.end(), str.begin(), str.end());
    return std::move(returnStr);
}

template<typename T, size_t ChildNum>
std::string node2json(std::shared_ptr<Node<T, ChildNum>> nodePointer, size_t tier) {
    std::ostringstream oss;
    oss << repeatString(tier - 1, "\t") << "{\n";
    if (nodePointer->isNoneChild())
        oss << repeatString(tier, "\t") << "\"children\": [],\n";
    else {
        oss << repeatString(tier, "\t") << "\"children\": [\n";
        bool isFirstChild = true;
        for (size_t i = 0; i != ChildNum; ++i)
            if (nodePointer->getChild(i)) {
                oss << (isFirstChild ? "" : ",\n");
                oss << node2json(nodePointer->getChild(i), tier + 2);
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
    oss << repeatString(tier, "\t") << R"("name": ")" << nodePointer->getData() << "\"\n";
    oss << repeatString(tier - 1, "\t") << "}";
    return oss.str();
}

template<typename T, size_t ChildNum, class Leaves>
std::ofstream &operator<<(std::ofstream &output, Tree<T, ChildNum, Leaves> &Tr) {
    output << node2json(Tr.root, 1);
    return output;
}


template<typename T, size_t ChildNum, class Leaves>
std::ostream &operator<<(std::ostream &os, Tree<T, ChildNum, Leaves> &Tr) {
    return os << node2json(Tr.root, 1);
}

template<typename T, class Leaves>
class BinaryTree : public Tree<T, 2, Leaves> {
public:
    BinaryTree() : Tree<T, 2, Leaves>() {};

    explicit BinaryTree(T x) : Tree<T, 2, Leaves>(x) {}

    template<typename Iterator>
    BinaryTree(Iterator begin, Iterator end): Tree<T, 2, Leaves>(begin, end) {}

    std::string preorderTreeWalk();

    std::string inorderTreeWalk();

    std::string postorderTreeWalk();

private:
    std::string preorderTreeWalk(std::shared_ptr<Leaves> pointer);

    std::string inorderTreeWalk(std::shared_ptr<Leaves> pointer);

    std::string postorderTreeWalk(std::shared_ptr<Leaves> pointer);
};

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::preorderTreeWalk(std::shared_ptr<Leaves> pointer) {
    std::ostringstream oss;
    oss << *pointer << ",";
    if (pointer->getLeftChild())
        oss << preorderTreeWalk(pointer->getLeftChild());
    if (pointer->getRightChild())
        oss << preorderTreeWalk(pointer->getRightChild());
    return oss.str();
}

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::preorderTreeWalk() {
    std::string str = std::move(this->preorderTreeWalk(this->getRoot()));
    str.substr(0, str.size() - 1);
    return str;
}

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::inorderTreeWalk(std::shared_ptr<Leaves> pointer) {
    std::ostringstream oss;
    if (pointer->getLeftChild())
        oss << inorderTreeWalk(pointer->getLeftChild());
    oss << *pointer << ",";
    if (pointer->getRightChild())
        oss << inorderTreeWalk(pointer->getRightChild());
    return oss.str();
}

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::inorderTreeWalk() {
    std::string str = std::move(this->inorderTreeWalk(this->getRoot()));
    str.substr(0, str.size() - 2);
    return str;
}

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::postorderTreeWalk(std::shared_ptr<Leaves> pointer) {
    std::ostringstream oss;
    if (pointer->getLeftChild())
        oss << postorderTreeWalk(pointer->getLeftChild());
    if (pointer->getRightChild())
        oss << postorderTreeWalk(pointer->getRightChild());
    oss << *pointer << ",";
    return oss.str();
}

template<typename T, class Leaves>
std::string BinaryTree<T, Leaves>::postorderTreeWalk() {
    std::string str = std::move(this->postorderTreeWalk(this->getRoot()));
    str.substr(0, str.size() - 2);
    return str;
}

#endif //MAIN_CPP_TREE_H