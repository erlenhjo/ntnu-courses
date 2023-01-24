#include "mastermind.h"
#include "std_lib_facilities.h"
#include "utilities.h"
#include "ctype.h"
#include "masterVisual.h"


void playMastermind(){
    MastermindWindow mwin{Point{900,20},winW,winH,"Mastermind"};
    constexpr int size=4;
    constexpr int letters=6;
    string code=randomizeString(size,'A','A'+letters-1);;
    string guess;
    
    addGuess(mwin,code,size,'A',0);
    hideCode(mwin,size);
    mwin.redraw();
    cout<<code<<"\n";
    int lives=6;
    while(lives>0){
        //cout<<"Gjett.\n";
        guess=mwin.getInput(size,'A','A'+letters-1);
        addGuess(mwin,guess,size,'A',7-lives);
        //cout<<checkCharacters(guess,code)<<" er i koden.\n";
        //cout<<checkCharactersAndPosition(guess,code)<<" er på riktig plass.\n";
        addFeedback(mwin,checkCharactersAndPosition(guess,code),checkCharacters(guess,code),size,7-lives);
        mwin.redraw();
        if(checkCharactersAndPosition(guess,code)<size){
            --lives;  
        }else{
            break;
        }
    }
    if(lives>0){
        cout<<"Gratulerer, du klarte det.\n";
    }else{
        cout<<"Du tapte. Bedre lykke neste gang.\n";
    }
    keep_window_open();
}
int checkCharactersAndPosition(string a, string b){
    int count=0;
    int size=a.size();
    if(b.size()<size){
        size=b.size();
    }
    for(int i=0;i<size;++i){
        if(toupper(a[i])==toupper(b[i])){
            ++count;
        }
    }
    return count;
}
int checkCharacters(string a, string b){
    int count=0;
    for(int i=0;i<a.size();++i){
        for(int j=0;j<b.size();++j){
            if(toupper(a[i])==toupper(b[j])){
                count++;
                b.erase(j,1);
                break;
            }
        }
    }
    return count;
}
