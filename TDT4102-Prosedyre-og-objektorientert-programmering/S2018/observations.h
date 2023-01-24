#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>




struct Obs {
    int x;
    int y;
};

void obsMain();

bool operator<(const Obs& lhs, const Obs& rhs);

void report(std::vector<Obs> vec, int threshold);