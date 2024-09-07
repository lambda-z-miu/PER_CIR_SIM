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

    //solver.decode(graph,SIN,2);
    solver.decode(graph,REC,2);
    //solver.solve(graph,2);

}