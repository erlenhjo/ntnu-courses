#pragma once

#include <string>
#include <iostream>
#include <strstream>
#include <ctime>
#include <cstdlib>
#include <map>


#include "Graph.h"


using namespace std;
using namespace Graph_lib;

constexpr int dispWidth=100;
constexpr int dispHeight=50;
constexpr int ridesPerDay=50;


struct Location {
   string name;
   Point p;
   Location(string str, Point pt);
};

class BikeStation{
    private:
        Location loc;
        unsigned int capacity;
        unsigned int bikes;
        Vector_ref<Shape> display;

    public:
        void setBikes(unsigned int num);
        unsigned int getBikes() const;
        string getName() const {return loc.name;}
        string status();
        BikeStation(Location where, unsigned int cap, unsigned int numBikes);
        unsigned int getCapacity() const {return capacity;}
};

map<string,int> simulateOneDay(vector<BikeStation*> stations);
int randInt(int a, int b);
void printStats(map<string,int> denials);