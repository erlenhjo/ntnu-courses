#include "Bysykler.h"


Location::Location(string str, Point pt)
    :name{str},p{pt}{}



void BikeStation::setBikes(unsigned int num){
    bikes=num;
}
unsigned int BikeStation::getBikes() const{
    return bikes;
}
string BikeStation::status(){
    return to_string(bikes)+" out of "+to_string(capacity);
}
BikeStation::BikeStation(Location where, unsigned int cap, unsigned int numBikes)
    : loc{where},capacity{cap},bikes{numBikes}{
        display.push_back(new Rectangle{loc.p,dispWidth,dispHeight});
        display[0].set_fill_color(Color::white);
        Text* txt = new Text{loc.p,loc.name};
        txt->set_color(Color::blue);
        txt->set_font_size(20);
        display.push_back(txt);
        Text* txt2 = new Text{Point{loc.p.x+2,loc.p.y+15},status()};
        txt2->set_color(Color::black);
        display.push_back(txt2);
    }

map<string,int> simulateOneDay(vector<BikeStation*> stations){
    srand(time(nullptr));
    map<string,int> denials;
    for(int rideNr{0};rideNr<ridesPerDay;++rideNr){
        BikeStation* start = stations[randInt(0,stations.size())];
        BikeStation* stop = stations[randInt(0,stations.size())]; //Allowing rides between same station :)

        if(start->getBikes()<1 || stop->getCapacity()-stop->getBikes()<1){
            denials[start->getName()]+=1;
        }
    }
    return denials;
}

int randInt(int a, int b){
    return a + rand()%(b-a);
}

void printStats(map<string,int> denials){
    cout<<"Unsuccsessful rides:\n";
    for(auto station:denials){
        cout<<station.second<<" bike trips refused at "<<station.first;
    }
    //map-et er allerede alfabetisk sorter siden key er av typen string
}