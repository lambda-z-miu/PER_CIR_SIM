#include "solver.h"
#include "error.h"
#include <deque>


#define pi 3.1415926


Eigen::VectorXcd Solver::decode(Graph circuit,enum Wave wave,double omega){

    double amplitudes[20];
    double SinAmplitudes[20]={0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    double TriAmplitudes[20]={0,1,0,(double)-1/9,0,(double)1/25,0,-(double)1/49,0,(double)1/81,
                              0,(double)-1/121,0,(double)1/169,0,(double)-1/225,0,(double)1/289,0,(double)-1/361};
    for(auto i : TriAmplitudes)
        i*=(8/(pi*pi));

    double RecAmplitudes[20]={0,1,0,(double)1/3,0,(double)1/5,0,(double)1/7,0,(double)1/9,0,
                              (double)1/11,0,(double)1/13,0,(double)1/15,0,(double)1/17,0,(double)1/19};
    for(auto i : RecAmplitudes)
        i*=(4/pi);
    

    switch(wave) {  
        case SIN:
            memcpy(amplitudes,SinAmplitudes,sizeof(amplitudes));
            break;

        case TRI:
            memcpy(amplitudes,TriAmplitudes,sizeof(amplitudes));
            break;

        case REC:
            memcpy(amplitudes,RecAmplitudes,sizeof(amplitudes));
            break;

        case SAW:
            throw SolveError("Unimplemented");
            break;

        case PWM:
            throw SolveError("Unimplemented");
            break;
    }

    auto ans=this->solve(circuit,omega);
    ans*=amplitudes[1];

    for(int i=2;i<20;i++){
        if(amplitudes[i]==0) continue;
        double tempomega = i * omega;
        auto tempans = amplitudes[i] * this->solve(circuit,tempomega);
        //std::cout<<"answer"<<i<<"="<<tempans;
        ans+=tempans;
        circuit.edges.clear();
    }



    this->iniedge(circuit,omega);
    output(circuit,ans);
    return ans;
}



Eigen::VectorXcd Solver::solve(Graph circuit,double omega){

    circuit.CalcValue(omega);
    //circuit.print();
    if (looplist.empty())
        looplist=circuit.findloop();

    auto test=circuit.getequation(looplist);
    int rows=test.size();

    Eigen::MatrixXcd L(rows,rows);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            //std::cout<<test[i][j]<<" ";
            L(i, j) = test[i][j];
        }
    //    std::cout<<std::endl;
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
