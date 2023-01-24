#include "Vehicle.h"



void Vehicle::draw(){
    std::pair<double,double> s = steer();
    
    if(status==Obstacle::Peel){
        if(state.speed<0.3){
            status=Obstacle::None;
            state.update(s.first,s.second);
        }
        else{
            state.slide(peelAngle);
        }
    }
    else{
        state.update(s.first,s.second);
    }

    if(state.x<vehicleRadius){state.x=vehicleRadius;}
    if(state.x>screenWidth-vehicleRadius){state.x=screenWidth-vehicleRadius;}
    if(state.y<vehicleRadius){state.y=vehicleRadius;}
    if(state.y>screenHeight-vehicleRadius){state.y=screenHeight-vehicleRadius;}

    double delX=state.x-track->getGoals()->at(currentGoal).first*screenWidth;
    double delY=state.y-track->getGoals()->at(currentGoal).second*screenHeight;
    double sumR=vehicleRadius+goalRadius;

    if(circleCollision(delX,delY,sumR)){
        if(currentGoal<static_cast<int>(track->getGoals()->size())-1){
            currentGoal+=1;
        }
    }

    for(auto o:*track->getObstacles()){
        delX=state.x-std::get<0>(o)*screenWidth;
        delY=state.y-std::get<1>(o)*screenHeight;
        
        switch(std::get<2>(o)){
            case Obstacle::Boost:{
                if(circleCollision(delX,delY,vehicleRadius+boostRadius)){
                    state.grip=2;
                }
                break;
            }
            case Obstacle::Peel:{
                if(circleCollision(delX,delY,vehicleRadius+peelRadius)){
                    if(state.speed>2){
                        status=Obstacle::Peel;
                        peelAngle=state.angle;
                    }
                }
                break;
            }
            case Obstacle::Spill:{
                if(circleCollision(delX,delY,vehicleRadius+spillRadius)){
                    state.grip=0.5;
                }
                break;
            }
        }
            
    }

    drawBody();
}


void PlayerVehicle::drawBody() const{
    fl_color(FL_BLUE);
    fl_circle(state.x,state.y,vehicleRadius);
    fl_circle(state.x+vehicleRadius*cos(state.angle),state.y+vehicleRadius*sin(state.angle),vehicleRadius/5);
    fl_color(FL_YELLOW);
    fl_circle(track->getGoals()->at(currentGoal).first*screenWidth,track->getGoals()->at(currentGoal).second*screenHeight,goalRadius);
}

std::pair<double,double> PlayerVehicle::steer() const{
    double traAcc{0},angAcc{0};
    if(Fl::event_key(FL_Right)){
        angAcc+=1;
    }
    if(Fl::event_key(FL_Left)){
        angAcc-=1;
    }
    if(Fl::event_key(FL_Up)){
        traAcc+=1;
    }
    if(Fl::event_key(FL_Down)){
        traAcc-=1;
    }
    return std::pair<double,double>{traAcc,angAcc};
}

void WASDPlayerVehicle::drawBody() const{
    fl_color(FL_RED);
    fl_circle(state.x,state.y,vehicleRadius);
    fl_circle(state.x+vehicleRadius*cos(state.angle),state.y+vehicleRadius*sin(state.angle),vehicleRadius/5);
}

std::pair<double,double> WASDPlayerVehicle::steer() const{
    double traAcc{0},angAcc{0};
    if(Fl::event_key('A')){
        angAcc+=1;
    }
    if(Fl::event_key('D')){
        angAcc-=1;
    }
    if(Fl::event_key('W')){
        traAcc+=1;
    }
    if(Fl::event_key('S')){
        traAcc-=1;
    }
    return std::pair<double,double>{traAcc,angAcc};
}


bool circleCollision(double delX, double delY, double sumR){
    if(sumR*sumR>(delX*delX+delY*delY)){
        return true;
    }
    return false;
}