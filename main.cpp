#include <iostream>
#include <algorithm>
#include <vector>
#include <windows.h>
#include "linear.h"
#include "graph.h"


using namespace std;

int main(){
    //std::complex<double> a(0,1);
    //std::cout<<_i(2);

    Graph graph;
    graph.CalcValue(2);
    graph.print();
    auto p=graph.findloop();
    for(auto i : p){
        for(auto j : i){
            std::cout<<j.first<<"->"<<j.second<<" ";
        }
        std::cout<<std::endl;
    }

    /*
    std::cout<<clock()<<endl;
    srand(static_cast<unsigned int>(time(0)));

    Complex2D tar;
    for(int i=0;i<14;i++){
        ComplexVector temp;
        for(int j=0;j<15;j++){
            complex<double> randnum=rand()/1000;
            std::cout<<randnum;
            temp.push_back(randnum);
        }
        tar.push_back(temp);
    }
    Matrix d{tar};
    //cout<<d.deter();
    std::cout<<endl<<clock()<<endl;
    auto e=d.solve();
    std::cout<<clock()<<endl;
    for(auto i :e) cout<<i;
    */
}