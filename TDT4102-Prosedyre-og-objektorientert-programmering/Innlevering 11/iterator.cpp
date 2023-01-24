#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include "iterator.h"

void iteratorTest(){
    std::vector<std::string> lorem{"Lorem","Ipsum","Dolor","Sit","Amet","Consectetur"};

    for(auto it=lorem.begin();it!=lorem.end();++it){
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";

    for(auto rit=lorem.rbegin();rit!=lorem.rend();++rit){
        std::cout<<*rit<<" ";
    }
    std::cout<<"\n";

    std::vector<std::string> lorem2{"Lorem","Ipsum","Dolor","Lorem"};
    replace(lorem2,"Lorem","Latin");

    for(auto it=lorem2.begin();it!=lorem2.end();++it){
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";

    std::set<std::string> lorem3{"Lorem","Ipsum","Dolor","Sit","Amet","Consectetur"};

    for(auto it=lorem3.begin();it!=lorem3.end();++it){
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";

    for(auto rit=lorem3.rbegin();rit!=lorem3.rend();++rit){
        std::cout<<*rit<<" ";
    }
    std::cout<<"\n";
    
    replace(lorem3,"Lorem","Another");

    for(auto it=lorem3.begin();it!=lorem3.end();++it){
        std::cout<<*it<<" ";
    }
    std::cout<<"\n";

}


void replace(std::vector<std::string>& v,std::string old, std::string replacement){
    for(auto it=v.begin();it!=v.end();++it){
        if(*it==old){
            it=v.erase(it);
            it=v.insert(it,replacement);
        }
    }
}

void replace(std::set<std::string>& v,std::string old, std::string replacement){
    auto it=find(v.begin(),v.end(),old);
    if(it!=v.end()){
        it=v.erase(it);
        it=v.insert(it,replacement);
    }
}