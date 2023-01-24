//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "animals.h"
#include "Emoji.h"
#include "testemoji.h"
//------------------------------------------------------------------------------'

//Teori
/*
Private: Tilgjengelig for medlemmer av klassen.
Protected: Tilgjengelig for medlemmer av klassen og deriverte klasser.
Public: Tilgjengelig for alt.
*/
// C++ programs start by executing the function main
int main()
{
	try{
		constexpr int quit=0;
		int caseNum=-1;
		
		while(caseNum!=quit){
			cout<<"1)Animals 2)Emoji 0)Quit\n";
			
			while(!(cin>>caseNum)){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout<<"Not valid input.\n";
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');

			switch(caseNum){
				case 0:{
					break;
				}
				case 1:{
					testAnimals();
					break;
				}
				case 2:{
					testEmoji();
					break;
				}
				default:{
					cout<<"Not valid case.\n";
					break;
				}
			}
		}
	}
	catch(exception& e){
		cout<<1;
		cerr<<"Error: "<<e.what()<<"\n";
		keep_window_open();
		return 1;
	}
	catch(...){
		cout<<2;
		cerr<<"Error: Uknown error.\n";
		keep_window_open();
		return 2;
	}
}

//------------------------------------------------------------------------------
