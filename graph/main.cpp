#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {

    vector <char> vertex = {'A','B','C','D'};
    vector <Edge> list;
    list.push_back(Edge{0,1,3});
    list.push_back(Edge{0,2,2});
    list.push_back(Edge{2,3,1});
    list.push_back(Edge{3,1,5});
    list.push_back(Edge{3,2,4});

    vector <Edge> list1={Edge{0,1}, Edge{0,3}, Edge{2,1}, Edge{2,3}};

    cout << "adj_mat: " << endl;
    Graph <char> G1 (store_type::adj_mat, vertex, list);
    G1.listVertexes();
    G1.listEdges();

    cout << "adj_list: " << endl;
    Graph <char> G2 (store_type::adj_list, vertex, list);
    G2.listVertexes();
    G2.listEdges();

    cout << "undirected graph: " << endl;
    Graph <char> G3 (store_type::adj_mat, vertex, list1, false);
    G3.listVertexes();
    G3.listEdges();

    return 0;
}