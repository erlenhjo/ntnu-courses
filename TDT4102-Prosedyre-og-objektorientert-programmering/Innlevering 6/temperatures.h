#pragma once
#include "std_lib_facilities.h"

struct Temps{
    double max;
    double min;
    friend istream& operator>>(istream& is, Temps& t);
};
vector<Temps> readTemps(string file);
int findMinTempIndex(vector<Temps> temps);
int findMaxTempIndex(vector<Temps> temps);