#include "utilities.h"
#include "tests.h"
#include "std_lib_facilities.h"


void testCallByValue() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    int result = incrementByValueNumTimes(v0, increment, iterations);
    cout << "v0: " << v0
    << " increment: " << increment
    << " iterations: " << iterations
    << " result: " << result << endl;
}
void testCallByReference() {
    int v0 = 5;
    int increment = 2;
    int iterations = 10;
    int result = incrementByValueNumTimesRef(v0, increment, iterations);
    cout << "v0: " << v0
    << " increment: " << increment
    << " iterations: " << iterations
    << " result: " << result << endl;
}
void testString(){
    string grades=randomizeString(8,'A','F');
    cout<<grades<<"\n";
    vector<int> gradeCount (6);
    string abcdef="ABCDEF";
    for(int i=0;i<6;++i){
        gradeCount[i]=countChar(grades,abcdef[i]);
    }
    int sum=0;
    for(int i=0;i<6;++i){
        sum+=gradeCount[i]*(5-i);
    }
    cout<<"Snittet blir "<<sum/8.0<<"\n";
}
