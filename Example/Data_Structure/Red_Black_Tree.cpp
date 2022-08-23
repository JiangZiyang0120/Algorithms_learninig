//
// Created by jiang-ziyang on 22-8-23.
//

#include <fstream>
#include "../../Data_Structure/Red_Black_Tree.h"
#include "../../Include/Supported_Tools.h"

void testInsertAndRemove() {
    RedBlackTree<int> BT;
    std::string order;
    int elem;
    std::cout<<R"(please input order, like "insert 13" or "remove 13" or "printTree")"<<std::endl;
    while (std::cin>>order){
        if(order == "insert"){
            std::cin >> elem;
            BT.insert(elem);
//        }else if(order == "remove"){
//            std::cin >> elem;
//            BT.remove(BT.search(elem));
        } else if(order == "printTree")
            printTree(BT);
        else
            std::cout<<"Not a order, please enter again"<<std::endl;
    }
}

int main(){
    testInsertAndRemove();
}