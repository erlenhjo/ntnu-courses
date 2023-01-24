#include "Track.h"


void Track::draw(){
    fl_color(FL_BLACK);
    for(auto g:goals){
        fl_circle(g.first*screenWidth,g.second*screenHeight,goalRadius);
    }
    for(auto o:obstacles){
        if(std::get<2>(o)==Obstacle::Boost){
            double r=10;
            double x=std::get<0>(o)*screenWidth-r;
            double y=std::get<1>(o)*screenHeight-r;
            b.draw(x,y,2*r,2*r);
        }
        else if(std::get<2>(o)==Obstacle::Peel){
            double r=15;
            double x=std::get<0>(o)*screenWidth-r;
            double y=std::get<1>(o)*screenHeight-r;
            p.draw(x,y,2*r,2*r);
        }
        else if(std::get<2>(o)==Obstacle::Spill){
            double r=25;
            double x=std::get<0>(o)*screenWidth-r;
            double y=std::get<1>(o)*screenHeight-r;
            s.draw(x,y,2*r,2*r);
        }
    }
}

const std::vector<std::pair<double,double>>* Track::getGoals() const{
    return &goals;
}

const std::vector<std::tuple<double,double,Obstacle>>* Track::getObstacles() const{
    return &obstacles;
}