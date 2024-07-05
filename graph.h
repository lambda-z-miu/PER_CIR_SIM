#include <optional>
#include <iostream>
#include <vector>
#include "devices.h"
#ifndef GRAPH_H
#define GRAPH_H
using std::vector;

typedef std::pair<int,int> Edge;


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
    InputStruct buffer[16];
    int size;
    optional<RLCM*> data[16][16];
    optional<complex<double>> value[16][16];
public:
    Graph();
    void print();
    void CalcValue(double omega);
    Edge findloop();
};
#endif