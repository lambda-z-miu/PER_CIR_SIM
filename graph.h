#include <optional>
#include <iostream>
#include <deque>
#include <deque>
#include "devices.h"
#include "linear.h"
#ifndef GRAPH_H
#define GRAPH_H
using std::deque,std::deque;

typedef std::pair<int,int> Edge;
typedef deque<Edge> Edgedeque;
typedef deque<deque<Edge>> Edge2D;

struct InputStruct{
    int a;
    int b;
    char name;
    double data;

    InputStruct(int ain,int bin,char namein,double datain) : a(ain),b(bin),name(namein),data(datain) {};
    InputStruct(){}
    static void getFromCin(InputStruct& a);
};

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
};
#endif