//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "filemanipulation.h"
#include "coursecatalog.h"
#include "temperatures.h"
#include "tempgraph.h"
//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{	
	try{
		constexpr int quit=0;
		int caseNum=-1;
		while(caseNum!=quit){
			cout<<"1)1a 2)1b 3)2a 4)3c 5)4c 6)4d 7)Graph 0)Quit  \n";
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
					writeWordsToFile("1a.txt");
					break;
				}
				case 2:{
					numerateFileLines("1bin.txt","1bout.txt");
					break;
				}
				case 3:{
					countCharactersInFile("grunnlov.txt");
					break;
				}
				case 4:{
					testCourseCatalog();
					break;
				}
				case 5:{
					vector<Temps> temps=readTemps("temperatures.txt");
					for(int i{0};i<6;++i){
						cout<<temps[i].max<<"\t"<<temps[i].min<<"\n";
					}
					break;
				}
				case 6:{
					vector<Temps> temps=readTemps("temperatures.txt");
					int maxIndex{findMaxTempIndex(temps)};
					int minIndex{findMinTempIndex(temps)};
					cout<<"Maks temp: "<<temps[maxIndex].max<<"\t";
					cout<<"Dag: "<<maxIndex<<"\n";
					cout<<"Min temp: "<<temps[minIndex].min<<"\t";
					cout<<"Dag: "<<minIndex<<"\n";
					break;
				}
				case 7:{
					plotTemperatures("temperatures.txt");
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
		cerr << e.what() << '\n';
		keep_window_open();
		return 1;
	}
	catch(...){
		cerr<<"Error: Ukjent error.\n";
		keep_window_open();
		return 2;
	}
}

//------------------------------------------------------------------------------