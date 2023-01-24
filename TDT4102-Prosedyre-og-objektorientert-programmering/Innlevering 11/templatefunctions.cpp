#include "templatefunctions.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

void testFunctions(){
    int a = 1;
    int b = 2;
    int c = maximum(a, b);
    // c er nå 2.
    double d = 2.4;
    double e = 3.2;
    double f = maximum(d,e);
    std::cout<<c<<"\n"<<f<<"\n";

    std::vector<int> g{1, 2, 3, 4, 5, 6, 7};
    shuffle(g); // Resultat, rekkefølgen i a er endret.
    std::vector<double> h{1.2, 2.2, 3.2, 4.2};
    shuffle(h); // Resultat, rekkefølgen i b er endret.
    std::vector<std::string> i{"one", "two", "three", "four"};
    shuffle(i); // Resultat, rekkefølgen i c er endret.
    
    for(auto e: g){
        std::cout<<e<<" ";
    }
    std::cout<<"\n";
    for(auto e: h){
        std::cout<<e<<" ";
    }
    std::cout<<"\n";
    for(auto e: i){
        std::cout<<e<<" ";
    }
    std::cout<<"\n";

}

template<typename T>
T maximum(T lhs,T rhs){
    if(lhs>rhs){
        return lhs;
    }
    return rhs;
}

template<typename T>
void shuffle(std::vector<T>& v){
    srand(time(nullptr));
    std::vector<T> temp{};
    while(v.size()){
        int index = rand()%v.size();
        temp.push_back(v[index]);
        v.erase(v.begin()+index);
    }    
    v=temp;
}