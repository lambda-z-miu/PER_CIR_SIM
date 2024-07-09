#include "devices.h"
#include "error.h"
optional<complex<double>> R::calresistance(double omega){
    if(this->resistance.has_value())
        return this->resistance.value();
    else return std::nullopt;
}

optional<complex<double>> L::calresistance(double omega){
    if(this->resistance.has_value())
        return this->resistance.value()*omega;
    else return std::nullopt;
}

optional<complex<double>> C::calresistance(double omega){
    if(this->resistance.has_value())
        return this->resistance.value()/omega;
    else return std::nullopt;
}

optional<complex<double>> E::calresistance(double omega){
    return this->resistance;
}


bool isE(RLCME* a){
    if(typeid(*a)==typeid(E)) return 1;
    return 0;
}