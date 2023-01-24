#include "Person.h"
#include "Car.h"

string Person::get_name() const{
    return name;
}

string Person::get_email() const{
    return email;
}

void Person::set_email(string newEmail){
    email=newEmail;
}

bool Person::hasAvailableSeats() const{
    if(car){
        return car->hasFreeSeats();
    }
    return false;
}

ostream& operator<<(ostream& os, const Person& p){
    if(p.hasAvailableSeats()){
        os<<p.name<<"; "<<p.email<<"; Available";
        return os;
    }
    os<<p.name<<"; "<<p.email<<"; Non available";
    return os;
}