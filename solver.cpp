#include "solver.h"

void Solver::solve(Graph circuit,int omega,enum Wave){

    circuit.CalcValue(omega);
    auto p=circuit.findloop();

    auto test=circuit.getequation(p);
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

    output(circuit,answer);
    
}
