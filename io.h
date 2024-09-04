#include <string>
#include <eigen-3.4.0/Eigen/Core>

using std::string;
#ifndef IO_H
#define IO_H

struct Snum{
    Snum(){}
    Snum(double datain) : level('1'),val(datain){}
    char level;
    double val;
    double getval();
};

struct InputStruct{
    int a;
    int b;
    char name;
    Snum data;

    InputStruct(int ain,int bin,char namein,Snum datain) : a(ain),b(bin),name(namein),data(datain) {};
    InputStruct(){}
    static void getFromCin(InputStruct& a);
};

class Graph;

std::istream& operator>>(std::istream& input,Snum& target);
void output(Graph circuit,Eigen::VectorXcd answer);


#endif