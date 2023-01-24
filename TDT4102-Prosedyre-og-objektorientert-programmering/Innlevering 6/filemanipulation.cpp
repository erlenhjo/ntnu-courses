#include "filemanipulation.h"
#include "std_lib_facilities.h"


void writeWordsToFile(string file){
    ofstream ost{file};
    cout<<"Write words (\"quit\" to exit)\n";
    for(string word; cin>>word;){
        if(word=="quit"){
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return;
        }
        ost<<word<<"\n";
    }
}

void numerateFileLines(string inputFile, string outputFile){
    ifstream ist{inputFile};
    if(!ist){
        error("Error: Can't open input file: ",inputFile);
        return;
    }
    ofstream ost{outputFile};
    if(!ost){
        error("Error: Can't open output file: ",outputFile);
        return;
    }
    int lineNum{1};
    for(string line; getline(ist, line);){
        ost<<lineNum<<line;
        ++lineNum;
        if(ist.eof()){
            return;
        }else{
            ost<<"\n";
        }
    }
}

void countCharactersInFile(string file){
    ifstream ist{file};
    if(!ist){
        error("Error: Can't open input file: ",file);
        return;
    }
    vector<int> characterCount(26);
    for(char c; ist>>c;){
        if(tolower(c)>='a'&& tolower(c)<='z'){
            characterCount[tolower(c)-'a']+=1;
            if(ist.eof()){
                break;
            }
        }
    }
    for(int i{0};i<26;++i){
        cout<<static_cast<char>('a'+i)<<": "<<left<<setw(6)<<characterCount[i];
        if(i%3==2||i==25){cout<<"\n";}
    }

}