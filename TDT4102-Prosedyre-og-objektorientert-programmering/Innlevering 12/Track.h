#pragma once

#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_JPEG_Image.H>

#include <tuple>
#include <vector>

#include "utilities.h"

enum class Obstacle{
    Spill,Boost,Peel,None
};

class Track : public Fl_Widget{
    private:
        std::vector<std::pair<double,double>> goals;
        std::vector<std::tuple<double,double,Obstacle>> obstacles;
        Fl_JPEG_Image b{"boostSprite.jpeg"};
        Fl_JPEG_Image p{"peelSprite.jpeg"};
        Fl_JPEG_Image s{"spillSprite.jpeg"};

    public:
        Track():
            Fl_Widget{10,10,10,10},
            goals{std::pair<double,double>{3.0/16.0,7.0/16.0},
                std::pair<double,double>{(11.0/16.0),(14.0/16.0)},
                std::pair<double,double>{3.0/16.0,3.0/16.0},
                std::pair<double,double>{3.0/16.0,14.0/16.0},
                std::pair<double,double>{14.0/16.0,3.0/16.0},
                std::pair<double,double>{7.0/16.0,9.0/16.0}},
            obstacles{
                std::tuple<double,double,Obstacle>{5.0/16,5.0/16,Obstacle::Peel},
                std::tuple<double,double,Obstacle>{2.0/16,3.0/16,Obstacle::Boost},
                std::tuple<double,double,Obstacle>{11.0/16,7.0/16,Obstacle::Boost},
                std::tuple<double,double,Obstacle>{8.0/16,2.0/16,Obstacle::Peel},
                std::tuple<double,double,Obstacle>{4.0/16,9.0/16,Obstacle::Spill}}
            {}
        void draw() override;
        const std::vector<std::pair<double,double>>* getGoals() const;
        const std::vector<std::tuple<double,double,Obstacle>>* getObstacles() const;
};

