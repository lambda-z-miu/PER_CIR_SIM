#include <complex>
#include <optional>
#include "error.h"
#include <memory>


#ifndef DEVICES_H
#define DEVICES_H

#define _i [](int x){std::complex<double> a(0,1); std::complex<double> b(x,0);return a*b;}

using std::complex,std::optional;
using std::shared_ptr;

class RLCME{
public:
    optional<complex<double>> current;
    optional<complex<double>> resistance;
    optional<complex<double>> voltage;
    optional<complex<double>> epsilon;

public:
    RLCME() : current(NULL),voltage(NULL),resistance(NULL),epsilon(NULL){};
    virtual optional<complex<double>> calresistance(double omega)=0;
};

class R:public RLCME{
public:
    R(double datain) :RLCME() {
        resistance=datain;
    }
    optional<complex<double>> calresistance(double omega) override;
};

class L:public RLCME{
public:
    L(double datain) :RLCME(){
        resistance=datain*_i(1);
    }
    optional<complex<double>> calresistance(double omega) override;
};

class C:public RLCME{
public:
    C(double datain) : RLCME(){
        resistance=-datain*_i(1);
    }
    optional<complex<double>> calresistance(double omega) override;
};

class E :public RLCME{
public:
    E(double datain) :RLCME(){
        resistance=0;
        epsilon=datain;
    }
    optional<complex<double>> calresistance(double omega) override;
};

class General : RLCME{
    General(shared_ptr<RLCME> a,shared_ptr<RLCME> b) : RLCME(){
        if(a->resistance.has_value() && b->resistance.has_value())
            resistance=a->resistance.value()+b->resistance.value();
        else throw IoError("INvalid Input");
    }
};

bool isE(RLCME* a);

#endif