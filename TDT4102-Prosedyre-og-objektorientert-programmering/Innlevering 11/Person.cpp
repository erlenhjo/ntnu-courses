#include <iostream>
#include "Person.h"
#include <string>
#include <list>


using namespace std;

void listTest(){
    Person A{"Arne","Alvesen"};
    Person B{"Bob","Bjartson"};
    Person C{"Carl","Calinka"};

    list<Person> pList{};
    insertOrdered(pList,B);
    insertOrdered(pList,A);
    insertOrdered(pList,B);
    insertOrdered(pList,C);

    for(auto p: pList){
        cout<<p<<"\n";
    }
}

ostream& operator<<(ostream& os,Person p){
    os<<p.getFirstName()<<" "<<p.getLastName();
    return os;
}

void insertOrdered(list<Person>& l, const Person& p){
    for(auto it=l.begin();it!=l.end();++it){
        if(p.getLastName()< (*it).getLastName()){
            l.insert(it,p);
            return;
        }
    }
    l.insert(l.end(),p);
}