#pragma once

#include <tuple>
#include <cmath>

#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>

#include "utilities.h"
#include "Track.h"

class Vehicle: public Fl_Widget{
    protected:
        virtual std::pair<double,double> steer() const=0;
        virtual void drawBody() const=0;
        PhysicsState state;
        const Track* track;
        int currentGoal=0;
        Obstacle status=Obstacle::None;
        int peelAngle=0;
    public:
        Vehicle(double x, double y, double angle,Track* track):Fl_Widget{10,10,10,10},state{x,y,angle},track{track}{}
        void draw() final;
};

class PlayerVehicle : public Vehicle{
    public:
        PlayerVehicle(Track* track):Vehicle(0,0,0,track){}
        void drawBody() const;
        std::pair<double,double> steer() const;      
};

class WASDPlayerVehicle : public Vehicle{
    public:
        WASDPlayerVehicle(Track* track):Vehicle(0,0,0,track){}
        void drawBody() const;
        std::pair<double,double> steer() const;
};

bool circleCollision(double delX, double delY, double sumR);