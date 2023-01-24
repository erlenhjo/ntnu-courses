#include "Vector2d.h"



double Vector2d::length() const{
    return sqrt(x*x+y*y);
}

Vector2d operator+(Vector2d lhs,Vector2d rhs){
    return Vector2d{lhs.x+rhs.x,lhs.y+rhs.y};
}

Vector2d Vector2d::operator*(int k) const{
    return Vector2d{x*k,y*k};
}

std::ostream& operator<<(std::ostream& out, const Vector2d& v){
    out<<"["<<v.x<<","<<v.y<<"]";
    return out;
}

Vector2d vectorSum(const std::vector<Vector2d>& vectors){
    double sumX=0;
    double sumY=0;
    for(Vector2d v: vectors){
        sumX+=v.x;
        sumY+=v.y;
    }
    return Vector2d{sumX,sumY};
}

void trackStats(const std::vector<Vector2d>& track){
    double length=0;
    int maxSpeed=0;
    for(Vector2d v:track){
        length+=v.length();
        if(v.length()/10*1000>maxSpeed){
            maxSpeed=round(v.length()/10*1000);
        }
    }
    std::cout<<"Length: "<<std::setprecision(2)<<std::fixed<<length<<" km, max-speed: "<<maxSpeed<<" m/min, ended at "<<vectorSum(track)<<"\n"; 
}

std::vector<Vector2d> cleanTrack(std::vector<Vector2d> track){
    clean c;
    std::vector<Vector2d> cleanTrack = track;
    std::transform(track.begin(),track.end(),cleanTrack.begin(),c);
    return cleanTrack;
}

Vector2d clean::operator()(Vector2d v){
    Vector2d newPos{position + v};
    if(newPos.x<0||newPos.x>10||newPos.y<0||newPos.y>10){
        return Vector2d{0,0};
    }
    position=newPos;
    return v;
}