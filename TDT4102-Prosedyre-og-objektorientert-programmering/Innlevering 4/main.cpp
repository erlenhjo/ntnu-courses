//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "tests.h"
#include "utilities.h"
#include "mastermind.h"
//------------------------------------------------------------------------------'
/*
Kodeforståelse
	1a) 
		v0: 5  pga pass-by-value
		increment: 2
		iterations: 0
		result: 5+10*2=25
	
constexpr defineres under kopilering. 
Hensiktsmessig om det f.eks. er et tall "7".
const skjer der det er definert i coden.
Nødvendig om man skall definere konstanten
som resultatet av en funksjon f.eks.

*/
// C++ programs start by executing the function main
int main(){	
	bool quit = false;
	int caseNum;
	while(!quit){
		cout<<"0)Avslutt 1)Increment 2)IncrementRef 3)SwapNumbers 4)StudentInfo 5)Studieprogram\n";
		cout<<"6)String 7)Gyldig input 8)Mastermind\n";
		cin>>caseNum;
		switch(caseNum){
			case 0:{
				quit=true;
				break;
			}
			case 1:{
				testCallByValue();
				break;
			}
			case 2:{
				testCallByReference();
				break;
			}
			case 3:{
				int a=1;
				int b=2;
				swapNumbers(a,b);
				cout<<a<<b<<"\n";
				break;
			}
			case 4:{
				Student subject={"Bob","Afrikastudier",42};
				printStudent(subject);
				break;
			}
			case 5:{
				Student subject={"Bob","Afrikastudier",42};
				cout<<"Afrikastudier: "<<isInProgram(subject,"Afrikastudier")<<"\n";
				cout<<"Ikke afrikastudier: "<<isInProgram(subject,"Datateknologi")<<"\n";
				break;
			}
			case 6:{
				testString();
				break;
			}
			case 7:{
				string test=readInputToString(4,'a','h');
				cout<<"Skrev in gyldig string "<<test<<"\n";
				test=readInputToString(4,'A','b');
				cout<<"Skrev in gyldig string "<<test<<"\n";
				break;
			}
			case 8:{
				playMastermind();
				break;
			}
			
		}
	}
}

//------------------------------------------------------------------------------
