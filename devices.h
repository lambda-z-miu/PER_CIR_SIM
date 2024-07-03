#include <complex>

#ifndef DEVICES_H
#define DEVICES_H

#define _i [](int x){std::complex<double> a(0,1); std::complex<double> b(x,0);return a*b;}

using std::complex;

class RLCM{
protected:
    double data;
    complex<double> current;
    complex<double> resistance;
    complex<double> voltage;

};

class R:public RLCM{
public:
    //R(double datain) : data(data){}
};



#endif