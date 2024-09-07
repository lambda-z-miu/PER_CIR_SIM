#include <iostream>
#include <iomanip>
#include <windows.h>
#include <memory>
#include "graph.h"
#include "io.h"

#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/Eigen/Core>

#ifndef SOLVER_H
#define SOLVER_H

using std::shared_ptr,std::make_shared;

enum Wave{
    SIN,
    TRI,
    PWM,
    REC,
    SAW,
};


struct Solver{
    Solver(){looplist={};}
    Edge2D looplist;
    void iniedge(Graph& circuit,double omega);
    Eigen::VectorXcd decode(Graph circuit,enum Wave,double omega);
    Eigen::VectorXcd solve(Graph circuit,double omega);
};

#endif