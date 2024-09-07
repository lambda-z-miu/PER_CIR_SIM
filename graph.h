#include <optional>
#include <deque>
#include "devices.h"
#include <eigen-3.4.0/Eigen/Core>


#include <iostream>

#ifndef GRAPH_H
#define GRAPH_H

#define MAXBUFFER 32


using std::deque,std::deque,std::complex;
typedef deque<deque<complex<double>>> Complex2D;
typedef deque<complex<double>> Complexdeque;

typedef std::pair<int,int> Edge;
typedef deque<Edge> Edgedeque;
typedef deque<deque<Edge>> Edge2D;

class Solver;

class Graph
{
    int size;
    optional<RLCME*> data[MAXBUFFER][MAXBUFFER];
    optional<complex<double>> value[MAXBUFFER][MAXBUFFER];
    

public:
    Edgedeque edges;

    Graph();
    void print();
    void CalcValue(double omega);

    Edge2D findloop();
    Edgedeque DFS(int currentnode,int startnode,Edgedeque& egdes);

    Complex2D getequation(Edge2D loopsin);

    friend Solver;
    friend void output(const Graph& circuit,Eigen::VectorXcd answer);

    ~Graph(){
        std::cout<<"Graph destoyed";
    }
};
#endif