#include "utilities.h"
#include "std_lib_facilities.h"
#include "cstdlib"
#include "ctime"
#include "ctype.h"

int incrementByValueNumTimes(int startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
    return startValue;
}
int incrementByValueNumTimesRef(int& startValue, int increment, int numTimes) {
    for (int i = 0; i < numTimes; i++) {
        startValue += increment;
    }
    return startValue;
}
void swapNumbers(int& x, int& y){
    int temp=x;
    x=y;
    y=temp;
}
void printStudent(Student subject){
    cout<<"Student info:\n";
    cout<<"Navn: "<<subject.name<<"\n";
    cout<<"Studieprogram: "<<subject.studyProgram<<"\n";
    cout<<"Alder: "<<subject.age<<"\n";
}
bool isInProgram(Student subject,string program){
    if(subject.studyProgram==program){
        return true;
    }
    return false;
}
string randomizeString(int length, char lower, char upper){
    srand(static_cast<unsigned int>(time(nullptr)));
    string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i=0;
    string eligible="";
    while(alphabet[i] != lower){
        ++i;
    }
    while(alphabet[i] != upper){
        eligible+=alphabet[i];
        ++i;
    }
    eligible+=alphabet[i];
    string random="";
    for(int i=0;i<length;++i){
        random+=eligible[rand()%(eligible.size())];
    }
    return random;
}
string readInputToString(int n, char lower, char upper){
    string input="";
    cout<<"Skriv in "<<n<<" tegn: \n";
    bool eligible=false;
    while(!eligible){
        eligible=true;
        cin>>input;
        int length=input.size();
        if(length!=n){
            cout<<"Feil antall tegn.\n";
            eligible=false;
            continue;
        }
        for(int i=0;i<n;++i){
            if (lower<=input[i]&&input[i]<=upper){
                continue;
            }else if(!isalpha(input[i])){
                cout<<input[i]<<" ikke i intervall.\n";
                eligible=false;
                break;
            }else if(lower<=tolower(input[i])&&tolower(input[i])<=upper){
                continue;
            }else if(lower<=toupper(input[i])&&toupper(input[i])<=upper){
                continue;
            }else{
                cout<<input[i]<<" ikke i intervall.\n";
                eligible=false;
                break;
            }
        }
    }
    return input;
}
int countChar(string theString, char character){
    int count=0;
    int length=theString.size();
    for(int i=0; i<length;++i){
        if(theString[i]==character){
            ++count;
        }
    }
    return count;
}