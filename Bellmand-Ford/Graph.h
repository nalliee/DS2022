#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <cassert>
#include <cmath>

using namespace std;

typedef int WeightType;
const int Inf = INT_MAX;
enum store_type{adj_mat, adj_list};

struct Edge
{
    int u;
    int v;
    WeightType w = 1;
};

template <typename G>
class Graph
{
  private:
    bool Direction;
    store_type store_mode;
    vector <G> Vertex;
    vector <vector<WeightType>> adj_mat;
    vector <list<Edge>> adj_list;
    vector <list<Edge>> adj_list_inv;

    void choose_store_mode (int Nv, int Ne)
    {
        if(Ne < Nv*log(Nv))
            store_mode == store_type::adj_list;
        else
            store_mode == store_type::adj_mat;
    }
    
  public:
    int GetNumOfVertex()
    {
        return Vertex.size();
    }
    void addEdge(Edge edge)
    {
        if(store_mode == store_type::adj_mat)
        {
            if(Direction == true)
            {
                adj_mat[edge.u][edge.v] = edge.w;
            }
            else
            {
                adj_mat[edge.u][edge.v] = edge.w;
                adj_mat[edge.v][edge.u] = edge.w;
            }
        }
        else if (store_mode == store_type::adj_list)
        {
            if(Direction == true)
            {
                adj_list[edge.u].push_back(edge);
                adj_list_inv[edge.v].push_back(edge);
            }
            else
            {
                adj_list[edge.u].push_back(edge);
                swap(edge.u, edge.v);
                adj_list[edge.u].push_back(edge);
            }
        }
    }

    void Init()
    {
        if (store_mode == store_type::adj_mat)
        {
            vector <WeightType> v;
            for(int i = 0; i < Vertex.size(); ++i)
            {
                if(Direction == true)
                    v.push_back(Inf);
                else
                    v.push_back(0);
            }

            for(int i = 0; i < Vertex.size(); ++i)
            {
                adj_mat.push_back(v);
            }
        }
        else if(store_mode == store_type::adj_list)
        {
            for(int i = 0; i < Vertex.size(); ++i)
            {
                adj_list.push_back(list<Edge>());
                adj_list_inv.push_back(list<Edge>());
            }
        }
    }

    Graph(store_type mode, vector <G> vertex, vector <Edge> list = {}, bool type = true) : store_mode{mode}, Vertex{vertex}, Direction{type}
    {
        Init();
        for(auto edge : list)
            this -> addEdge(edge);
    }

    Graph(vector <G> vertex, vector <Edge> list = {}, bool type = true) : Vertex{vertex}, Direction{type}
    {
        this -> choose_store_mode(vertex.size(), list.size());
        Init();
        for(auto edge : list)
            this -> addEdge(edge);
    }

    void listVertexes () {
        for(auto v : Vertex)
            cout << v << " ";
        cout << endl;
    }

    void listEdges ()
    {
        if(store_mode == store_type:: adj_mat)
        {
            for(size_t i = 0; i < Vertex.size(); ++i)
            {
                if(Direction == true)
                {
                    for(size_t j = 0; j < Vertex.size(); ++j)
                    {
                        if(adj_mat[i][j] != Inf)
                            cout << "(" << Vertex[i] << "," << Vertex[j] << "," << adj_mat[i][j] << ")" << endl;
                    }
                }
                else
                {
                    for(size_t j = i + 1; j < Vertex.size(); ++j)
                    {
                        if(adj_mat[i][j] != 0)
                            cout << "(" << Vertex[i] << "," << Vertex[j] << "," << adj_mat[i][j] << ")" << endl;
                    }
                }
            }
        }
        else if (store_mode == store_type::adj_list)
        {
            for(int i = 0; i < Vertex.size(); ++i)
            {
                for(auto it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
                    cout << "(" << Vertex[it -> u] << "," << Vertex[it -> v] << "," << it -> w << ")" << endl;
            }
        }
    }

    bool BELLMAN_FORD(int s, bool output = false)
    {
        int N = this -> GetNumOfVertex();
        vector<int> d{};
        for(int i = 0; i < N; ++i) {
            d.push_back(Inf);
        }
        d[s] = 0;
        for(int i = 0; i < N-1; ++i) {
            for(int j = 0; j < N; ++j) 
            {
                for(auto e : adj_list[j]) {
                    if(d[e.v] > d[e.u] + e.w)
                    {
                        d[e.v] = d[e.u] + e.w;
                    }
                }
            }
        }
    
        for(int j = 0; j < N; ++j)
        {
            for(auto e : adj_list[j]) {
                if(d[e.v] > d[e.u] + e.w)
                {
                    if(output)
                    {
                        cout << "Negative cycle occurs." << endl;
                    }
                    return false;
                }
            }
        }
        if(output)
        {
            for(int i = 0; i < N; ++i)
            {
                cout << "delta(" << Vertex[s] << "," << Vertex[i] << ")" << d[i] << endl;
            }
        }
    }
};

#endif