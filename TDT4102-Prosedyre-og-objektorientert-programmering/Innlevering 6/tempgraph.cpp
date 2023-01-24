#include "std_lib_facilities.h"
#include "Simple_window.h"
#include "Graph.h"
#include "temperatures.h"
#include "tempgraph.h"


void plotTemperatures(string file){
    Simple_window win{windowStart,xMax,yMax,winLabel};
    
    Axis xAxis{Axis::x,origo,xAxisLength,12,""};
    Axis yAxis{Axis::y,Point{xOffset ,yMax-yOffset},yAxisLength,6,"degrees [\260C]"};
    xAxis.set_color(Color::black);
    yAxis.set_color(Color::black);
    win.attach(xAxis);
    win.attach(yAxis);

    Text February{Point{xOffset+xAxisLength*1/48,yMax/2+20},"Feb"};
    February.set_color(Color::black);
    win.attach(February);
    Text March{Point{xOffset+xAxisLength*5/48,yMax/2+20},"Mar"};
    March.set_color(Color::black);
    win.attach(March);
    Text April{Point{xOffset+xAxisLength*9/48,yMax/2+20},"Apr"};
    April.set_color(Color::black);
    win.attach(April);
    Text May{Point{xOffset+xAxisLength*13/48,yMax/2+20},"May"};
    May.set_color(Color::black);
    win.attach(May);
    Text June{Point{xOffset+xAxisLength*17/48,yMax/2+20},"Jun"};
    June.set_color(Color::black);
    win.attach(June);
    Text July{Point{xOffset+xAxisLength*21/48,yMax/2+20},"Jul"};
    July.set_color(Color::black);
    win.attach(July);
    Text August{Point{xOffset+xAxisLength*25/48,yMax/2+20},"Aug"};
    August.set_color(Color::black);
    win.attach(August);
    Text September{Point{xOffset+xAxisLength*29/48,yMax/2+20},"Sep"};
    September.set_color(Color::black);
    win.attach(September);
    Text October{Point{xOffset+xAxisLength*33/48,yMax/2+20},"Oct"};
    October.set_color(Color::black);
    win.attach(October);
    Text November{Point{xOffset+xAxisLength*37/48,yMax/2+20},"Nov"};
    November.set_color(Color::black);
    win.attach(November);
    Text December{Point{xOffset+xAxisLength*41/48,yMax/2+20},"Dec"};
    December.set_color(Color::black);
    win.attach(December);
    Text January{Point{xOffset+xAxisLength*45/48,yMax/2+20},"Jan"};
    January.set_color(Color::black);
    win.attach(January);

    Text p20deg{Point{xOffset-30,yOffset+yAxisLength*1/6+7}," 20"};
    p20deg.set_color(Color::black);
    win.attach(p20deg);
    Text p10deg{Point{xOffset-30,yOffset+yAxisLength*2/6+7}," 10"};
    p10deg.set_color(Color::black);
    win.attach(p10deg);
    Text p0deg{Point{xOffset-30,yOffset+yAxisLength*3/6+7},"  0"};
    p0deg.set_color(Color::black);
    win.attach(p0deg);
    Text m10deg{Point{xOffset-30,yOffset+yAxisLength*4/6+7},"-10"};
    m10deg.set_color(Color::black);
    win.attach(m10deg);
    Text m20deg{Point{xOffset-30,yOffset+yAxisLength*5/6+7},"-20"};
    m20deg.set_color(Color::black);
    win.attach(m20deg);
    double xScale=1.0/365*xAxisLength;
    Scale x{xOffset,0,xScale};
    double yScale=-1.0/60*yAxisLength;
    Scale y{yMax/2,0,yScale};

    Open_polyline maxGraph;
    Open_polyline minGraph;

    vector<Temps> temps=readTemps(file);
    for(unsigned int i{0};i<temps.size();++i){
        maxGraph.add(Point{x.calculatePoint(i),y.calculatePoint(temps[i].max)});
        minGraph.add(Point{x.calculatePoint(i),y.calculatePoint(temps[i].min)});
    }
    maxGraph.set_color(Color::red);
    minGraph.set_color(Color::blue);
    win.attach(maxGraph);
    win.attach(minGraph);

    Text max{Point{x.calculatePoint(0)-70,y.calculatePoint(temps[0].max)},"Max"};
    Text min{Point{x.calculatePoint(0)-70,y.calculatePoint(temps[0].min)},"Min"};
    max.set_color(Color::red);
    min.set_color(Color::blue);
    win.attach(max);
    win.attach(min);


    win.wait_for_button();
}

Scale::Scale(int c,int v, double s):cBase{c},vBase{v},scale{s}{}
int Scale::calculatePoint(double val){
    return static_cast<int>(cBase + (val-vBase)*scale);
}