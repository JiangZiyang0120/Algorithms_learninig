//
// Created by jiang-ziyang on 22-8-20.
//


#include <fstream>
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
    T.setData(2.768,2,0);
    T.setData(12.365,2,1);
    T.setData(-3.142,3,2);
    T.setData(3.124,3,3);
    T.setData(4.132,3,5);
    T.setData(2.514,4,6);
    T.setData(3.245,4,16);
    std::ofstream openFile;
    std::string fileName = "data.json";
    openFile.open(fileName);
    openFile<<T<<std::endl;
    std::cout<<fileName<<" is written successfully"<<std::endl;
    system("pytm-cli -i data.json -t 3");
    system("firefox ./TreeMap.html");
}

int main() {
    std::cout<<"Test of Node\n-----------------------------------\n"<<std::endl;
    testNode();
    std::cout<<"Test of Tree\n-----------------------------------\n"<<std::endl;
    testTree();
    return 0;
}