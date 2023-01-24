#include "observations.h"

using namespace std;



void obsMain(){
    try{
        ifstream file{"input.txt"};

        if(!file){
            throw string{"Could not open file \"input.txt\""};
        }
        int a,b;
        vector<Obs> vec;
        while(file>>a>>b){
            vec.push_back(Obs{a,b});
            cout<<a<<" "<<b<<"\n";
        }

        //test
        report(vec,1);
    }

    catch(string e){
        cerr<<"Error:"<<e;
    }
}

bool operator<(const Obs& lhs, const Obs& rhs){
    if(lhs.x<rhs.x){
        return true;
    }
    else if(lhs.x==rhs.x){
        if(lhs.y<rhs.y){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

void report(vector<Obs> vec, int threshold){
    map<Obs,int> obsNum;
    for(Obs o:vec){
        obsNum[o]+=1;
    }
    for(auto oPair:obsNum){
        if(oPair.second>threshold){
            cout<<oPair.first.x<<" ";
            cout<<oPair.first.y<<" ";
            cout<<oPair.second<<"\n";
        }
    }

}