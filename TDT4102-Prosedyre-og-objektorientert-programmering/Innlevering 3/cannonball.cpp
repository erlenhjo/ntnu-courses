#include "cannonball.h"
#include "std_lib_facilities.h"
double acclY(){
    return -9.81;
} 
double acclX(){
    return 0;
}
double velX(double initVelocityX,double time){
    return initVelocityX+acclX()*time;
}
double velY(double initVelocityY,double time){
    return initVelocityY+acclY()*time;
}
double posX(double initPositionX, double initVelocityX,double time){
    return initPositionX+initVelocityX*time;
}
double posY(double initPositionY, double initVelocityY, double time){
    return initPositionY+initVelocityY*time+acclY()*pow(time,2)/2;
}
void printTime(double time){
    int hours=static_cast<int>(time)/3600;
    time=time-3600*hours;
    int minutes=static_cast<int>(time)/60;
    double seconds=time-60*minutes;
    cout<<hours<<" timer, "<<minutes<<" minutter og "<<seconds<<" sekunder.\n";
}
double flightTime(double initVelocityY){
    return -2*initVelocityY/acclY();
}
double getUserInputTheta(){
 double theta;
 cout<<"Angi skuddvinkel i grader: ";
 cin>>theta;
 return theta;
}
double getUserInputAbsVelocity(){
    double absVel;
    cout<<"Angi skuddhastighet: ";
    cin>>absVel;
    return absVel;
}
double degToRad(double deg){
    return deg*3.14/180;
}
double getVelocityX(double theta, double absVelocity){
    return absVelocity*cos(degToRad(theta));
}
double getVelocityY(double theta, double absVelocity){
    return absVelocity*sin(degToRad(theta));
}
vector<double> getVelocityVector(double theta, double absVelocity){
    vector<double> temp(2);
    temp[0]=getVelocityX(theta,absVelocity);
    temp[1]=getVelocityY(theta,absVelocity);
    return temp;
}
double getDistanceTraveled(double velocityX, double velocityY){
    return velocityX*flightTime(velocityY);
}
double targetPractice(double distanceToTarget,double velocityX,double velocityY){
    return getDistanceTraveled(velocityX,velocityY)-distanceToTarget;
}