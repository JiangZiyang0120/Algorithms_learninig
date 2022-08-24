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
//    Tree<std::string ,3> T;
//    T.setRoot("A");
//    T.setData("B",2,0);
//    T.setData("C",2,1);
//    T.setData("D",3,2);
//    T.setData("E",3,3);
//    T.setData("F",3,5);
//    T.setData("G",4,6);
//    T.setData("H",4,16);
    std::ofstream openFile;
    std::string fileName = "data.json";
    std::vector<char> vec({'A','B','C','D','E','F','G','H','I','J','K','L','M','N'});
    Tree<char,3> T(vec.begin(),vec.end());
    printTree(T);
    auto T2 = T.Tree2BinaryTree();
    printTree(T2);
}

void testWalk(){
    std::vector<char> vec({'A','B','C','D','E','F','G','H','I','J','K','L','M','N'});
    BinaryTree<char> T(vec.begin(),vec.end());
    std::ofstream openFile;
    std::string fileName = "data.json";
    openFile.open(fileName);
    openFile<<T<<std::endl;
    openFile.close();
    std::cout<<fileName<<" is written successfully"<<std::endl;
    system("pytm-cli -i data.json -t 1");
    system("firefox ./TreeMap.html");
    std::cout<<"preorderTreeWalk:\n"<<T.preorderTreeWalk()<<"\n"<<std::endl;
    std::cout<<"inorderTreeWalk:\n"<<T.inorderTreeWalk()<<"\n"<<std::endl;
    std::cout<<"postorderTreeWalk:\n"<<T.postorderTreeWalk()<<"\n"<<std::endl;
}

int main() {
    std::cout<<"Test of Node\n-----------------------------------\n"<<std::endl;
    testNode();
    std::cout<<"Test of Tree\n-----------------------------------\n"<<std::endl;
    testTree();
    std::cout<<"Test of Walk\n-----------------------------------\n"<<std::endl;
    testWalk();
    return 0;
}