#include "Car.h"

void Car::reserveFreeSeat(){
    --freeSeats;
}

bool Car::hasFreeSeats() const{
    if(freeSeats>0){
        return true;
    }
    return false;
}