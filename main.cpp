#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <windows.h>
#include "graph.h"
#include "devices.h"

#include <eigen-3.4.0/Eigen/Core>
#include <eigen-3.4.0/Eigen/Dense>


using namespace std;

int main(){
    Graph graph;

    auto time_0=clock();
    graph.CalcValue(2);
//  graph.print();
    auto p=graph.findloop();

    auto test=graph.getequation(p);


    Matrix indexs{test};


    int rows=test.size();
    Eigen::MatrixXcd L(rows,rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            L(i, j) = test[i][j];
        }
    }
    //std::cout<<L<<std::endl;


    Eigen::VectorXcd R(rows);
    for(int i=0;i<rows;i++){
        R(i)=test[i].back();
    }
    //std::cout<<R;

    Eigen::JacobiSVD<Eigen::MatrixXcd> svd(L, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::VectorXcd answer = svd.solve(R);

    auto time_1=clock();
    std::cout<<"After "<<(time_1-time_0)/1000.01<<" seconds :"<<std::endl;

    //std::cout<<std::endl<<"!!"<<std::endl<<answer<<std::endl;

    for(int i=0;i<answer.size();i++) {
        std::cout<<graph.edges[i].first<<"->"<<graph.edges[i].second<<": i="<<
        answer[i].real()<<(answer[i].imag()<0 ? "" : "+")<<answer[i].imag()<<"j";
        std::cout<<std::endl;
    }


    //auto answers=indexs.solve();

}