#pragma once
#include "algorithm"

class Dummy {
    public:
        int *num;
        Dummy() {
            num = new int{0};
        }
        ~Dummy() {
            delete num;
        }
        Dummy(const Dummy& d){
            num=new int{*d.num};
        }
        Dummy& operator=(Dummy d){
            std::swap(num,d.num);
            return *this;
        }
};

void dummyTest();