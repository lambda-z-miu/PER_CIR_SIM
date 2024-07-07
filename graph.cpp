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


deque<int> visitednodes;
EdgeVector loop;
bool endsgn;

Edge2D Graph::findloop(){

    Edge2D allloops;
    EdgeVector edges;

    for(int i=0;i<size;i++){
        for(int j=i;j<size;j++){
            if(value[i][j]!=nullopt){
                edges.push_back(Edge(i,j));
            }
        }
    }

    while(!edges.empty()){
        int startnode=edges.front().first;
        int currentnode=edges.front().second;
        bool endsgn=0;

        visitednodes.clear();
        loop.clear();

        visitednodes.push_back(startnode);
        visitednodes.push_back(currentnode);
        loop.push_back(Edge(startnode,currentnode));
        edges.pop_front();

        auto temp=DFS(currentnode,startnode,edges);
        allloops.push_back(temp);
    }
    return allloops;
}



EdgeVector Graph::DFS(int currentnode,int startnode,EdgeVector& edges){

    if(value[currentnode][startnode]!=nullopt && loop.size()!=1){
        loop.push_back(pair<int,int>(currentnode,startnode));
        for(auto i : loop){
            for(auto j=edges.begin();j!=edges.end();j++){
                if((i.first==(*j).first && i.second==(*j).second) || (i.second==(*j).first && i.first==(*j).second))
                    edges.erase(j);
            }
        }
        endsgn=1;
        return loop;
    }

    for(int i=0;i<5;i++){
        for(int j=0;j<visitednodes.size();j++){
            if(visitednodes[j]==i)
                goto NEXT;
        }
        

        if(value[currentnode][i]!=nullopt){
            visitednodes.push_back(i);
            loop.push_back(pair<int,int>(currentnode,i));
            DFS(i,startnode,edges);
            if(endsgn==1) return loop;
            loop.pop_back();
            visitednodes.pop_back();
        }
        NEXT: continue;//logic
    }
}