#include "solver.h"
#include "error.h"
#include <deque>


#define pi 3.1415926


Eigen::VectorXcd Solver::decode(Graph circuit,enum Wave wave,double omega){

    deque<double> amplitude;

    auto lambda= [&](Graph circuit,deque<double> amplitude,double omega) -> Eigen::VectorXcd
    {

        auto ans=this->solve(circuit,omega);
        ans*=amplitude[1];

        for(int i=2;i<20;i++){
            if(amplitude[i]==0) continue;
            double tempomega = i * omega;
            auto tempans = this->solve(circuit,tempomega);
            ans+=amplitude[i]*tempans;
            circuit.edges.clear();
        }


        return ans;
    };

    switch(wave) {  

        case SIN:
            amplitude={0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
            break;

        case TRI:
            amplitude={0,1,0,-1/9,0,1/25,0,-1/49,0,1/81,0,-1/121,0,1/169,0,-1/225,0,1/289,0,-1/361};
            for(auto i : amplitude)
                i*=(8/(pi*pi));
            break;

        case REC:
            amplitude={0,1,0,1/3,0,1/5,0,1/7,0,1/9,0,1/11,0,1/13,0,1/15,0,1/17,0,1/19};
            for(auto i : amplitude)
                i*=(4/pi);
            break;

        case SAW:
            throw SolveError("Unimplemented");
            break;

        case PWM:
            throw SolveError("Unimplemented");
            break;
    }

    auto answer = lambda(circuit,amplitude,omega);

    this->iniedge(circuit,omega);
    output(circuit,answer);
    return answer;
}



Eigen::VectorXcd Solver::solve(Graph circuit,double omega){

    circuit.CalcValue(omega);
    if (looplist.empty())
        looplist=circuit.findloop();

    auto test=circuit.getequation(looplist);
    int rows=test.size();

    Eigen::MatrixXcd L(rows,rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            L(i, j) = test[i][j];
        }
    }


    Eigen::VectorXcd R(rows);
    for(int i=0;i<rows;i++){
        R(i)=test[i].back();
    }

    Eigen::JacobiSVD<Eigen::MatrixXcd> svd(L, Eigen::ComputeThinU | Eigen::ComputeThinV);
    Eigen::VectorXcd answer = svd.solve(R);

    return answer;

}


void Solver::iniedge(Graph& circuit,double omega){
    circuit.CalcValue(omega);
    circuit.getequation(looplist);
}
