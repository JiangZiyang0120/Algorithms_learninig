//
// Created by jiang-ziyang on 22-8-29.
//

#include "../../../Include/Supported_Tools.h"
#include "../../../Data_Structure/Graph.h"

void testLink2Array() {
    auto a = std::make_shared<Vertex>("a"),
            b = std::make_shared<Vertex>("b"),
            c = std::make_shared<Vertex>("c"),
            d = std::make_shared<Vertex>("d");
    AdjacentList<> AJ;
    AJ.insert(a, b, 3);
    AJ.insert(a, c, 2);
    AJ.insert(b, c, 1.7);
    AJ.insert(a, d, 9);
    AJ.insert(d, b, 7);
    AJ.insert(b, d, 6);
    std::cout << AJ << std::endl;
    AdjacentArray<> AD(AJ);
    std::cout << AD << std::endl;
    AD(3, 2) = 10.6;
    std::cout << AD << std::endl;
}

void testUndirected() {
    std::shared_ptr<Vertex> a(std::make_shared<Vertex>("a")), b(
            std::make_shared<Vertex>("b")), c = std::make_shared<Vertex>("c"), d(std::make_shared<Vertex>("d")), e(
            std::make_shared<Vertex>("e")), f(std::make_shared<Vertex>("f"));
    UndirectedAdjacentList<> UAD;
    UAD.insert(a,e,3);
    std::cout<<UAD<<std::endl;
}

int main() {
//    testLink2Array();
    testUndirected();
    return 0;
}