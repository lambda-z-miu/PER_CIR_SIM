#include <iostream>
#include <iomanip>
#include <windows.h>
#include "graph.h"
#include "io.h"

#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/Eigen/Core>

#ifndef SOLVER_H
#define SOLVER_H

enum Wave{
    SIN,
    TRIANGLE,
};

struct Solver{
    void solve(Graph circuit,int omega,enum Wave);
};

#endif