#pragma once
#include "std_lib_facilities.h"
#include "Car.h"

class Person{
    public:
        Person(string name,string email,Car* car=nullptr):
            name{name},email{email},car{car}{}
        string get_name() const;
        string get_email() const;
        void set_email(string newEmail);
        bool hasAvailableSeats() const;
        friend ostream& operator<<(ostream& os, const Person& p);
    private:
        string name;
        string email;
        Car* car;
};
