#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <windows.h>
#include "graph.h"
#include "devices.h"
#include "io.h"
#include "solver.h"

#include <eigen-3.4.0/Eigen/Dense>
#include <eigen-3.4.0/Eigen/Core>


using namespace std;

int main(){

    Graph graph;
    Solver solver;
    solver.solve(graph,2,SIN);

}