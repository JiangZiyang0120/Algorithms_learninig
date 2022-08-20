//
// Created by jiang-ziyang on 22-8-20.
//


#include "../../Data_Structure/Tree.h"
#include "../../Include/Supported_Tools.h"

void testNode() {
    std::shared_ptr<Node<double, 3>> node(std::make_unique<Node<double, 3>>());
    node->setData(3.469);
    std::cout << *node << std::endl;
    std::cout << "node " << (node->isNoneChild() ? "has " : "doesn't has ") << "children" << std::endl;
    node->setChild(4.69,0);
    std::cout<<*node->getChild(0)<<std::endl;
    std::shared_ptr<Node<double, 3>> nodeChild(std::make_unique<Node<double, 3>>(9.27));
    node->setChild(nodeChild,2);
    std::cout<<*node->getChild(2)<<std::endl;
    std::cout<<*node->getChild(2)->getParent()<<std::endl;
    return;
}


void testTree(){
    Tree<double,3> T;
    T.setRoot(3.976);
    std::cout<<T.getDepth()<<std::endl;
    T.setData(2.768,2,0);
    std::cout<<T.getDepth()<<std::endl;
    T.setData(-3.142,3,2);
    T.setData(2.514,4,6);
    std::cout<<T.getDepth()<<std::endl;
}

int main() {
    std::cout<<"Test of Node\n-----------------------------------\n"<<std::endl;
    testNode();
    std::cout<<"Test of Tree\n-----------------------------------\n"<<std::endl;
    testTree();
    return 0;
}