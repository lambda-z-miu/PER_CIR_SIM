#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <windows.h>
#include "linear.h"
#include "graph.h"
#include "devices.h"


using namespace std;

int main(){
    Graph graph;

    auto time_0=clock();
    graph.CalcValue(2);
//  graph.print();
    auto p=graph.findloop();

/*
    for(auto i : p){
        for(auto j : i){
            std::cout<<j.first<<"->"<<j.second<<" ";
        }
        std::cout<<std::endl;
    }
*/    

    auto test=graph.getequation(p);
/*
    for(auto i : test){
        for(auto j : i){
            std::cout<<setw(12)<<j<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
*/

    Matrix indexs{test};
    auto answers=indexs.solve();

    auto time_1=clock();

    std::cout<<"After "<<(time_1-time_0)/1000.01<<" seconds :"<<std::endl;
    
    for(int i=0;i<answers.size();i++) {
        std::cout<<graph.edges[i].first<<"->"<<graph.edges[i].second<<": i="<<
        answers[i].real()<<(answers[i].imag()<0 ? "" : "+")<<answers[i].imag()<<"j";
        std::cout<<std::endl;
    }
}