#include "linear.h"
#include "error.h"
#include <algorithm>
#include <iostream>
using std::cout;
int Matrix::getsize(){
    return size;
}

void Matrix::print(){
    for(auto i : data){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<std::endl;
    }
}

complex<double> Matrix::deter(){
    if(data.size()!=data[0].size()) {
        cout<<data.size()<<data[0].size();
        throw MatrixError("invalid determinant");
    }

    auto getsgn=[](vector<int> order){
        int ret=0;
        for(int i=0;i<order.size();i++){
            for(int j=i;j<order.size();j++){
                if(order[i]>order[j]) ret++;
            }
        }
        return 1-2*(ret%2);
    };

    vector<int> order;
    complex<double> ret=0;
    for(int i=1;i<=size;i++) order.push_back(i);
    do{
        complex<double> temp=1;
        for(int i=0;i<size;i++){
            temp*=data[i][order[i]-1];
        }
        temp*=getsgn(order);
        ret+=temp;
    }
    while(next_permutation(order.begin(),order.end()));
    return ret;
}

vector<complex<double>> Matrix::solve(){
    if(data.size()!=data[0].size()-1) throw MatrixError("Cannot solve");

    Complex2D crammerdelta;
    for(auto i : data) {
        i.pop_back();
        crammerdelta.push_back(i);
    }
    Matrix delta{crammerdelta};
    complex<double> denominator=delta.deter();

    ComplexVector ret={};
    for(int i=0;i<data.size();i++){
        Complex2D temp;
        for(auto j : data) {
            j.erase(j.begin()+i);
            j.insert(j.begin()+i,j.back());
            j.erase(j.end());
            temp.push_back(j);
        }
        Matrix numerator{temp};
        complex<double> xn=numerator.deter()/denominator;
        ret.push_back(xn);
    }
    return ret;
}