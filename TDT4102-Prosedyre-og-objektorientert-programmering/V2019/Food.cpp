#include "Food.h"



bool operator<(Food& lhs,Food& rhs){
    if(lhs.price<rhs.price){
        return true;
    }
    return false;
}

void addPrice(map<string,set<Food>>& db, Food fp){
    if(db.find(fp.name)!=db.end()){
        db.at(fp.name).insert(fp);
    }
    else{
        db[fp.name]=set<Food>{fp};
    }
}

void printAllPrices(const map<string,set<Food>>& db){
    for(auto f:db){
        cout<<f.first<<":\n";
        for(Food fp:f.second){
            cout<<fp.price<<" "<<fp.where<<"\n";
        }
    }
}

void bestPrice(const map<string, set<Food>>& db, string name){
    if(db.find(name)!=db.end()){
        cout<<"Best price for"<<name<<"is "<<db.at(name).begin()->price<<" at "<<db.at(name).begin()->where<<"\n";
    }
    else{
        cout<<"No price for "<<name<<"\n";
    }
}