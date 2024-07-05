#include "graph.h"
#include <cstring>
#include "error.h"
#include <iostream>
#include <iomanip>
#include <deque>

using std::cin,std::nullopt,std::pair,std::deque;


void InputStruct::getFromCin(InputStruct& input){
    int a,b;char c;double d;
    cin>>a>>b>>c>>d;
    InputStruct ret(a,b,c,d);
    input=ret;
}

Graph::Graph() : size(0) {
    int sizecnt=0;
    while(cin){
        InputStruct::getFromCin(buffer[sizecnt]);
        sizecnt++;
    }

    for(int i=0;i<sizecnt;i++){
        if(buffer[i].a>size) size=buffer[i].a+1;
        if(buffer[i].b>size) size=buffer[i].b+1;
    }

    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            data[i][j]=std::nullopt;
        }
    }

    for(int i=0;i<sizecnt;i++){
        switch (buffer[i].name)
        {
            case 'R':
                data[buffer[i].a][buffer[i].b]=new R(buffer[i].data);
                data[buffer[i].b][buffer[i].a]=data[buffer[i].a][buffer[i].b];
                break;
            
            case 'L':
                data[buffer[i].a][buffer[i].b]=new L(buffer[i].data);
                data[buffer[i].b][buffer[i].a]=data[buffer[i].a][buffer[i].b];
                break;

            case 'C':
                data[buffer[i].a][buffer[i].b]=new C(buffer[i].data);
                data[buffer[i].b][buffer[i].a]=data[buffer[i].a][buffer[i].b];
                break;
            
            case 'M':
                throw IoError("UNIMPLEMENTED");
            
            default:
                throw IoError("unkown signal");
        }
        
    }
}

void Graph::CalcValue(double omega){
    if(size==0) throw IoError("empty input");
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(data[i][j]==std::nullopt) 
                value[i][j]=std::nullopt;
            else{
                value[i][j]=(*(data[i][j]))->calresistance(omega);
            }
        }
    }
}

void Graph::print(){

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(value[i][j]==std::nullopt)
                std::cout<<std::setw(10)<<"\\  ";
            else
                std::cout<<std::setw(10)<<value[i][j].value()<<" ";
        }
        std::cout<<std::endl;
    }
}

Edge Graph::findloop(){

    deque<Edge> edges;
    for(int i=0;i<size;i++){
        for(int j=i;j<size;j++){
            if(value[i][j]!=nullopt){
                edges.push_back(Edge(i,j));
            }
        }
    }
    
    while(!edges.empty()){
        int startnode=edges.front().first;
        deque<int> nownodes;
        nownodes.push_back(startnode);
        edges.pop_front();
        while(!nownodes.empty()){
            for(auto i : nownodes){
                std::cout<<" "<<i;
                if(i==startnode) goto END; 
            }
            END:break;
            std::cout<<std::endl;

            int current=nownodes.front();
            nownodes.pop_front();
            for(int i=0;i<size;i++)
                if(value[current][i]!=nullopt)
                    nownodes.push_back(i);

           
        }
    }
    throw IoError("1");
}