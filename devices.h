#include <complex>
#include <optional>
#include "error.h"

#ifndef DEVICES_H
#define DEVICES_H

#define _i [](int x){std::complex<double> a(0,1); std::complex<double> b(x,0);return a*b;}

using std::complex,std::optional;

class RLCM{
public:
    optional<complex<double>> current;
    optional<complex<double>> resistance;
    optional<complex<double>> voltage;
public:
    RLCM() : current(NULL),voltage(NULL),resistance(NULL){};
    virtual optional<complex<double>> calresistance(double omega)=0;
};

class R:public RLCM{
public:
    R(double datain) :RLCM() {
        resistance=datain;
    }
    optional<complex<double>> calresistance(double omega) override;
};

class L:public RLCM{
public:
    L(double datain) :RLCM(){
        resistance=datain*_i(1);
    }
    optional<complex<double>> calresistance(double omega) override;
};

class C:public RLCM{
public:
    C(double datain) : RLCM(){
        resistance=-datain*_i(1);
    }
    optional<complex<double>> calresistance(double omega) override;
};

class General : RLCM{
    General(RLCM* a,RLCM* b) : RLCM(){
        if(a->resistance.has_value() && b->resistance.has_value())
            resistance=a->resistance.value()+b->resistance.value();
        else throw IoError("INvalid Input");
    }
};



#endif