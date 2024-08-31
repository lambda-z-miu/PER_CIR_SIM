#include <deque>

#include <complex>

#ifndef MATH_H
#define MATH_H

using std::deque,std::complex;
typedef deque<deque<complex<double>>> Complex2D;
typedef deque<complex<double>> Complexdeque;
class Matrix
{
    int size;
    deque<deque<complex<double>>> data;

public:
    int getsize();
    Matrix(Complex2D datain) : size(datain.size()),data(datain) {}
    Matrix(){}
    complex<double> deter();
    Complexdeque solve();
    void print();
};

#endif