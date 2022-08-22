//
// Created by jiang-ziyang on 22-8-22.
//

#include <fstream>
#include "../../Data_Structure/Binary_Searching_Tree.h"
#include "../../Include/Supported_Tools.h"

void testInsertAndRemove() {
    BinarySearchingTree<int> BT;
    std::string order;
    int elem;
    std::cout<<R"(please input order, like "insert 13" or "remove 13" or "printTree")"<<std::endl;
    while (std::cin>>order){
        if(order == "insert"){
            std::cin >> elem;
            BT.insert(elem);
        }else if(order == "remove"){
            std::cin >> elem;
            BT.remove(BT.search(elem));
        } else if(order == "printTree")
            printTree(BT);
        else
            std::cout<<"Not a order, please enter again"<<std::endl;
    }
}

int main() {
//    //This Tree's construction satisfies the condition of binarySearchingTree
//    std::vector<int> vec({15,6,18,3,9,17,20,2,4,7,13});
//    BinarySearchingTree<int> BT(vec.begin(),vec.end());
//    BT.insert(27);
//    BT.insert(1);
//    BT.insert(3);
//    BT.insert(14);
//    BT.insert(12);
//    std::string fileName = "data.json";
//    std::ofstream openFile;
//    printTree(openFile,fileName,BT);
//    int searchingNum = 13;
//    std::cout<<searchingNum << "'s successor is " <<*BT.successor(BT.search(searchingNum))<<std::endl;
//    std::cout<<"and its predecessor is "<<*BT.predecessor(BT.search(searchingNum))<<std::endl;
    testInsertAndRemove();
    return 0;
}