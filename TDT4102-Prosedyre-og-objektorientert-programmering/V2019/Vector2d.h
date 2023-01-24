#pragma once



#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

class Vector2d{
    public:
        double x;
        double y;
    
        Vector2d(double x, double y):x{x},y{y}{}
        double length() const;
        Vector2d operator*(int  k) const;

};

Vector2d operator+(Vector2d lhs,Vector2d rhs);

std::ostream & operator<<(std::ostream& out, const Vector2d& v);

Vector2d vectorSum(const std::vector<Vector2d>& vectors);

void trackStats(const std::vector<Vector2d>& track);

std::vector<Vector2d> cleanTrack(std::vector<Vector2d> track);

struct clean{
    Vector2d position=Vector2d{0.0,0.0};
    Vector2d operator()(Vector2d v);
};