//
// Created by jiang-ziyang on 22-8-26.
//

#ifndef MAIN_CPP_GRAPH_H
#define MAIN_CPP_GRAPH_H

#include "DS_Header.h"
#include "List.h"
#include <Eigen/Core>

class Vertex {
    friend std::ostream &operator<<(std::ostream &os, Vertex &V);

    friend std::ostream &operator<<(std::ostream &os, Vertex &&V);

public:
    Vertex(std::string &str) : name(str) {};

    Vertex(std::string &&str) {
        name = std::move(str);
    }

private:
    std::string name;
};

std::ostream &operator<<(std::ostream &os, Vertex &V) {
    return os << V.name;
}

std::ostream &operator<<(std::ostream &os, Vertex &&V) {
    return os << V.name;
}

template<class Vertex = ::Vertex>
class Edge {
public:
    Edge() = default;

    explicit Edge(std::shared_ptr<Vertex> n, double w) : node(n), weight(w) {};

    std::shared_ptr<Vertex> getNode();

    double getWeight();

private:
    std::shared_ptr<Vertex> node;
    double weight;
};


template<class Vertex>
std::shared_ptr<Vertex> Edge<Vertex>::getNode() {
    return node;
}

template<class Vertex>
std::ostream &operator<<(std::ostream &os, Edge<Vertex> &E) {
    return os << "(" << "node : " << *E.getNode() << " , weight : " << E.getWeight() << ")";
}

template<class Vertex>
double Edge<Vertex>::getWeight() {
    return weight;
}

template<class Vertex = ::Vertex, class Edge = ::Edge<Vertex>>
class AdjacentList;

template<class Vertex = ::Vertex, class Edge = ::Edge<Vertex>>
class AdjacentArray;

template<class Vertex, class Edge>
class AdjacentList {
    friend AdjacentArray<Vertex, Edge>;

    template<class thisVertex, class thisEdge>
    friend std::ostream &operator<<(std::ostream &os, AdjacentList<thisVertex, thisEdge> &AJ);

    template<class thisVertex, class thisEdge>
    friend std::ostream &operator<<(std::ostream &os, AdjacentList<thisVertex, thisEdge> &&AJ);

public:
    AdjacentList() = default;

    void insert(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, double);

    void remove(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>);

protected:
    std::map<std::shared_ptr<Vertex>, List<Edge>> graph;
};

template<class Vertex, class Edge>
std::ostream &operator<<(std::ostream &os, AdjacentList<Vertex, Edge> &AJ) {
    for (auto iter = AJ.graph.begin(); iter != AJ.graph.end(); ++iter) {
        os << *iter->first << " : " << iter->second << "\n";
    }
    return os;
}

template<class Vertex, class Edge>
std::ostream &operator<<(std::ostream &os, AdjacentList<Vertex, Edge> &&AJ) {
    for (auto iter = AJ.graph.begin(); iter != AJ.graph.end(); ++iter) {
        os << *iter->first << " : " << iter->second << "\n";
    }
    return os;
}

template<class Vertex, class Edge>
void AdjacentList<Vertex, Edge>::insert(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> next, double w) {
    if (!graph[origin])
        graph[origin];
    auto x = Edge(next, w);
    graph[origin].insert(x);
}

template<class Vertex, class Edge>
void AdjacentList<Vertex, Edge>::remove(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> nextNode) {
    if (graph[origin]) {
        //where iter is an iterator points to a shared_ptr Node
        //we need to dereference iter to get shared_ptr
        for (auto iter = graph[origin].begin(); iter != graph[origin].end(); ++iter) {
            if ((*iter).getNode() == nextNode) {
                graph[origin].remove(iter.get());
                if (!graph[origin])
                    graph.erase(origin);
                break;
            }
        }
    }
}

template<class Vertex, class Edge>
class AdjacentArray {
    friend AdjacentList<Vertex, Edge>;

    template<class thisVertex, class thisEdge>
    friend std::ostream &operator<<(std::ostream &os, AdjacentArray<thisVertex, thisEdge> &AD);

    template<class thisVertex, class thisEdge>
    friend std::ostream &operator<<(std::ostream &os, AdjacentArray<thisVertex, thisEdge> &&AD);

public:
    explicit AdjacentArray(Eigen::MatrixXd &M) {
        route = M;
    }

    explicit AdjacentArray(Eigen::MatrixXd &&M) {
        route = std::move(M);
    }

    explicit AdjacentArray(AdjacentList<Vertex, Edge> &AL) {
        List2Array(AL);
    }

    void insert(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, double);

    void insert(size_t, size_t, double);

    void remove(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>);

    void remove(size_t, size_t);

    double &operator()(size_t, size_t);

protected:
    std::map<std::shared_ptr<Vertex>, size_t> Vertex2Index;
    std::vector<std::shared_ptr<Vertex>> VertexLink;
    std::set<std::shared_ptr<Vertex>> VertexSet;
    Eigen::MatrixXd route;

private:
    void List2Array(AdjacentList<Vertex, Edge> &AL);
};

template<class Vertex, class Edge>
void AdjacentArray<Vertex, Edge>::insert(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> next, double w) {
    if (VertexSet.find(origin) || VertexSet.find(next))
        throw std::runtime_error("this graph doesn't contain at least one of those node");
    route(Vertex2Index[origin], Vertex2Index[next]) = w;
}

template<class Vertex, class Edge>
void AdjacentArray<Vertex, Edge>::insert(size_t row, size_t col, double w) {
    route(row, col) = w;
}

template<class Vertex, class Edge>
void AdjacentArray<Vertex, Edge>::remove(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> next) {
    insert(origin, next, 0);
}

template<class Vertex, class Edge>
void AdjacentArray<Vertex, Edge>::remove(size_t row, size_t col) {
    route(row, col) = 0;
}

template<class Vertex, class Edge>
double &AdjacentArray<Vertex, Edge>::operator()(size_t row, size_t col) {
    return route(row, col);
}

template<class Vertex, class Edge>
void AdjacentArray<Vertex, Edge>::List2Array(AdjacentList<Vertex, Edge> &AL) {
    size_t index = 0;
    for (auto iter = AL.graph.begin(); iter != AL.graph.end(); ++iter) {
        VertexSet.insert(iter->first);
        for (auto subiter = iter->second.begin(); subiter != iter->second.end(); ++subiter) {
            VertexSet.insert(subiter->getNode());
        }
    }
    const size_t arraySize = VertexSet.size();
    route = Eigen::MatrixXd(arraySize, arraySize);
    for (auto iter = VertexSet.begin(); iter != VertexSet.end(); ++iter) {
        Vertex2Index[*iter] = index++;
        VertexLink.push_back(*iter);
    }
    for (auto iter = AL.graph.begin(); iter != AL.graph.end(); ++iter) {
        auto colIndex = Vertex2Index[iter->first];
        for (auto subIter = iter->second.begin(); subIter != iter->second.end(); ++subIter) {
            route(colIndex, Vertex2Index[subIter->getNode()]) = subIter->getWeight();
        }
    }
}

template<class Vertex, class Edge>
std::ostream &operator<<(std::ostream &os, AdjacentArray<Vertex, Edge> &AD) {
    size_t arraySize = AD.VertexLink.size();
    os.fill(' ');
    os.width(10);
    os << "";
    for (auto iter = AD.VertexLink.begin(); iter != AD.VertexLink.end(); ++iter) {
        os.width(10);
        os << **iter;
    }
    os << "\n";
    for (size_t i = 0; i != arraySize; ++i) {
        os.width(10);
        os << *(AD.VertexLink[i]);
        for (size_t j = 0; j != arraySize; ++j) {
            os.width(10);
            os << AD.route(i, j);
        }
        os << "\n";
    }
    return os;
}

template<class Vertex = ::Vertex, class Edge = ::Edge<Vertex>>
class UndirectedAdjacentList : public AdjacentList<Vertex, Edge> {
public:
    void insert(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, double = 1);

    void remove(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>);
};

template<class Vertex, class Edge>
void
UndirectedAdjacentList<Vertex, Edge>::insert(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> node, double w) {
    AdjacentList<Vertex, Edge> *pointer = this;
    pointer->insert(origin, node, w);
    pointer->insert(node, origin, w);
}

template<class Vertex, class Edge>
void UndirectedAdjacentList<Vertex, Edge>::remove(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> node) {
    AdjacentList<Vertex, Edge> *pointer = this;
    pointer->remove(origin, node);
    pointer->remove(node, origin);
}

template<class Vertex = ::Vertex, class Edge = ::Edge<Vertex>>
class UndirectedAdjacentArray : public AdjacentArray<Vertex, Edge> {
public:
    void insert(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>, double);

    void insert(size_t, size_t, double);

    void remove(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>);

    void remove(size_t, size_t);
};

template<class Vertex, class Edge>
void
UndirectedAdjacentArray<Vertex, Edge>::insert(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> next, double w) {
    AdjacentArray<Vertex, Edge> *pointer = this;
    pointer->insert(origin, next, w);
    pointer->insert(next, origin, w);
}

template<class Vertex, class Edge>
void UndirectedAdjacentArray<Vertex, Edge>::insert(size_t row, size_t col, double w) {
    AdjacentArray<Vertex, Edge> *pointer = this;
    pointer->insert(row, col, w);
    pointer->insert(col, row, w);
}

template<class Vertex, class Edge>
void UndirectedAdjacentArray<Vertex, Edge>::remove(std::shared_ptr<Vertex> origin, std::shared_ptr<Vertex> next) {
    AdjacentArray<Vertex, Edge> *pointer = this;
    pointer->remove(origin, next);
    pointer->remove(next, origin);
}

template<class Vertex, class Edge>
void UndirectedAdjacentArray<Vertex, Edge>::remove(size_t row, size_t col) {
    AdjacentArray<Vertex, Edge> *pointer = this;
    pointer->remove(row, col);
    pointer->remove(col, row);
}

#endif //MAIN_CPP_GRAPH_H
