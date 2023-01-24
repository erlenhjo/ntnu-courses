#pragma once
#include "std_lib_facilities.h"

class Animal{
    protected:
        string name;
        int age;
    public:
        Animal(string n, int a):name{n},age{a}{};
        virtual string toString() const=0;
};

class Cat:public Animal{
    public:
        Cat(string n,int a):Animal(n,a){};
        string toString() const;
};

class Dog:public Animal{
    public:
        Dog(string n, int a):Animal(n,a){};
        string toString() const;
};

void testAnimals();