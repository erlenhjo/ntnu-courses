#pragma once
#include "std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include "temperatures.h"

using namespace Graph_lib;

constexpr int yMax{600};
constexpr int xMax{1200};
const int xOffset{100};
constexpr int yOffset{60};
constexpr int xAxisLength{xMax-2*xOffset};
constexpr int yAxisLength{yMax-2*yOffset};
const Point origo{xOffset,yMax/2};

const Point windowStart{100,100};
const string winLabel="Temperature graph";

void plotTemperatures(string file);
void addMonthLabels(Simple_window& win);

class Scale{
    private:
        int cBase;
        int vBase;
        double scale;
    public:
        Scale(int c,int v, double s);
        int calculatePoint(double val);
};