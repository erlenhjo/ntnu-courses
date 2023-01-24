#include "animals.h"
#include "std_lib_facilities.h"
#include "Graph.h"


// string Animal::toString() const{
//     ostringstream s;
//     s<<"Animal: "<<name<<", "<<age;
//     return s.str();
// }
string Cat::toString() const{
    ostringstream s;
    s<<"Cat: "<<name<<", "<<age;
    return s.str();
}
string Dog::toString() const{
    ostringstream s;
    s<<"Dog: "<<name<<", "<<age;
    return s.str();
}
void testAnimals(){
    using namespace Graph_lib;
    //Animal animal{"Anders",1};
    Cat cat{"Cody",2};
    Dog dog{"Dudleif",3};
    //cout<<animal.toString()<<"\n";
    cout<<cat.toString()<<"\n";
    cout<<dog.toString()<<"\n";
    
    cout<<"Via vector_ref:\n";
    Vector_ref<Animal> vref;
    //vref.push_back(animal);
    vref.push_back(cat);
    vref.push_back(dog);
    for(int i{0};i<vref.size();++i){
        cout<<vref[i].toString()<<"\n";
    }
    return;
}