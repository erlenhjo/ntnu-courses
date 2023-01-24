#include "std_lib_facilities.h"
#include "temperatures.h"

istream& operator>>(istream& is, Temps& t){
    is>>t.max;
    is>>t.min;
    return is;
}

vector<Temps> readTemps(string file){
    ifstream is{file};
    vector<Temps> temps;
    do{
        Temps newTemps;
        is>>newTemps;
        temps.push_back(newTemps);
    } while(!is.eof());
    return temps;
}
int findMaxTempIndex(vector<Temps> temps){
    int index{0};
    for(unsigned int i{0};i<temps.size();++i){
        if(temps[i].max>temps[index].max){
            index=i;
        }
    }
    return index;
}
int findMinTempIndex(vector<Temps> temps){
    int index{0};
    for(unsigned int i{0};i<temps.size();++i){
        if(temps[i].min<temps[index].min){
            index=i;
        }
    }
    return index;
}