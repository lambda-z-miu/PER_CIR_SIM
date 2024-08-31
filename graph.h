#include <optional>
#include <deque>
#include "devices.h"
#include "io.h"

#ifndef GRAPH_H
#define GRAPH_H
using std::deque,std::deque,std::complex;;
typedef deque<deque<complex<double>>> Complex2D;
typedef deque<complex<double>> Complexdeque;

typedef std::pair<int,int> Edge;
typedef deque<Edge> Edgedeque;
typedef deque<deque<Edge>> Edge2D;



class Graph
{
    int size;
    optional<RLCME*> data[16][16];
    optional<complex<double>> value[16][16];
    

public:
    Edgedeque edges;

    Graph();
    void print();
    void CalcValue(double omega);

    Edge2D findloop();
    Edgedeque DFS(int currentnode,int startnode,Edgedeque& egdes);

    Complex2D getequation(Edge2D loopsin);

    friend int main();
    ~Graph();
};
#endif