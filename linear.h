#include <vector>
#include <complex>

#ifndef MATH_H
#define MATH_H

using std::vector,std::complex;
typedef vector<vector<complex<double>>> Complex2D;
typedef vector<complex<double>> ComplexVector;
class Matrix
{
    int size;
    vector<vector<complex<double>>> data;

public:
    int getsize();
    Matrix(Complex2D datain) : size(datain.size()),data(datain) {}
    Matrix(){}
    complex<double> deter();
    ComplexVector solve();
    void print();
};

#endif