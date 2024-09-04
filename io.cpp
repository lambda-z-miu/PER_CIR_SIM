#include <iostream>
#include <math.h>
#include "io.h"
#include "error.h"
#include "graph.h"

using std::cin,std::cout;


void InputStruct::getFromCin(InputStruct& input){
    int a,b;char c;Snum d;
    cin>>a>>b>>c>>d;
    InputStruct ret(a,b,c,d);
    input=ret;
}

std::istream& operator>>(std::istream& input,Snum& target){    
    string a;
    input>>a;


    if(a.back()-'0'<=9) {
        target.level='1';
        try{
        target.val=std::stod(a);
        }
        catch(...){;}
    }

    else{
        target.level=a.back();
        a.pop_back();
        //std::cout<<a;
        target.val=std::stod(a);
    }

    return input;
}

double Snum::getval(){

    switch (level)
    {
    case 'M':
        return val*pow(10,6);
    case 'k':
        return val*pow(10,3);
    case 'm':
        std::cout<<"called";
        return val*pow(10,-3);
    case 'u':
        return val*pow(10,-6);
    case 'n':
        return val*pow(10,-9);
    case 'p':
        return val*pow(10,-12);
    case '1':
        return val;
    default:
        throw IoError("invalid prefix");
    }
}

void output(Graph circuit,Eigen::VectorXcd answer){
    for(int i=0;i<answer.size();i++) {
        std::cout<<circuit.edges[i].first<<"->"<<circuit.edges[i].second<<": i="<<
        answer[i].real()<<(answer[i].imag()<0 ? "" : "+")<<answer[i].imag()<<"j";

        auto tempvoltage=circuit.value[circuit.edges[i].first][circuit.edges[i].second].value()*answer[i]+(*(circuit.data[circuit.edges[i].first][circuit.edges[i].second]).value()->epsilon);
        std::cout<<"\n      u="<<tempvoltage.real()<<(tempvoltage.imag()<0 ? "" : "+")<<tempvoltage.imag()<<"j";
        std::cout<<std::endl;
    }
}

