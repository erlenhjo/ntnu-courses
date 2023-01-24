#include <string>
#include <iostream>
#include <list>


class Person{
    private:
        std::string fName;
        std::string lName;
    public:
        Person(std::string firstName,std::string lastName):fName{firstName},lName{lastName}{};
        std::string getFirstName() const{return fName;}
        std::string getLastName() const{return lName;}
        
};

void listTest();

std::ostream& operator<<(std::ostream& os,Person p);

void insertOrdered(std::list<Person>& l, const Person& p);