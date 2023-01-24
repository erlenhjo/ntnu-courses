//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Person.h"
#include "Meeting.h"
#include "MeetingWindow.h"
//------------------------------------------------------------------------------'
using namespace Graph_lib;
//Person operator<<(ostream& os, const Person& p)
//Skal ikke endre person, så ryddig med const
//For opperatorer som endrer f.eks operator++
//kan man ikke ha const. Dersom man ikke skal kunne
//endre er det bedre med const så man får feil om
//man prøver.

// C++ programs start by executing the function main
int main()
{
	Person Abe{"Abe","abe@mail.com",new Car{2}};
	Person Bob{"Bob","bob@mail.com"};
	Person Cal{"Cal","cal@mail.com",new Car{3}};
	Person Dan{"Dan","dan@mail.com",new Car{1}};
	Person Eli{"Eli","eli@mail.com"};
	Eli.set_email("eli@notmail.com");
	cout<<Abe<<"\n";
	cout<<Bob<<"\n";
	cout<<Cal<<"\n";
	cout<<Dan<<"\n";
	cout<<Eli<<"\n";
	
	Meeting meetA{1,13,14,Campus::Trondheim,"Altruisme",&Abe};
	meetA.addParticipant(&Bob);
	meetA.addParticipant(&Cal);
	cout<<meetA;
	for(auto p:meetA.findPotentialCoDriving()){
		cout<<*p<<"\n";
	}
	
	Point topLeft{100,100};
	int width{xMax};
	int height{yMax};
	const string title{"Meeting"};
	MeetingWindow meetWin{topLeft,width,height,title};
	gui_main();
	meetWin.printPersons();
	
	keep_window_open();

}

//------------------------------------------------------------------------------
