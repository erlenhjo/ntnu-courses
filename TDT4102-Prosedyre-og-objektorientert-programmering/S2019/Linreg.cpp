#include "Linreg.h"



double sum(vector<double>& x){
    double sum=0;
    for(double e: x){
        sum+=e;
    }
    return sum;
}

double mean(vector<double>& x){
    return sum(x)/x.size();
}

void read_csv(string filename, vector<double>& x, vector<double>& y){
    ifstream file{filename};
    double xVal=0;
    double yVal=0;
    
    if(!file){
        throw "Couldn't read file "+filename;
    }
    while(!file.eof()){
        file>>xVal>>yVal;
        x.push_back(xVal);
        y.push_back(yVal);
    }
    file.close();
}

void linregMain(){
    vector<double> x;
    vector<double> y;
    read_csv("data.csv",x,y);
    pair<double,double> ab = linreg(x,y);
    double a=ab.first;
    double b=ab.second;
    vector<double> y_pred=linpred(x,a,b);
    double R2=r2(y,y_pred);
    cout<<"a: "<<a<<"   b: "<<b<<"   R^2: "<<R2<<endl;
}

pair<double,double> linreg(vector<double>& x, vector<double>& y){
    int n = x.size();
    double xBar=mean(x);
    double yBar=mean(y);
    double var=0;
    double cov=0;
    for(int i{0};i<n;++i){
        var+=(x[i]-xBar)*(x[i]-xBar);
        cov+=(x[i]-xBar)*(y[i]-yBar);
    }
    var=var/n;
    cov=cov/n;

    double a=cov/var;
    double b=yBar-a*xBar;

    return pair<double,double>{a,b};
}

vector<double> linpred(vector<double>& x, double a, double b){
    vector<double> y;
    for(double xi:x){
        y.push_back(a*xi+b);
    }
    return y;
}

double r2(vector<double>& y, vector<double>& y_pred){
    double numerator=0;
    double denominator=0;

    int n = y.size(); //I assume y-values are for same x in both vectors. 
    double yBar=mean(y);

    for(int i{0};i<n;++i){
        numerator+=(y[i]-y_pred[i])*(y[i]-y_pred[i]);
        denominator+=(y[i]-yBar)*(y[i]-yBar);
    }

    return 1-numerator/denominator;
}