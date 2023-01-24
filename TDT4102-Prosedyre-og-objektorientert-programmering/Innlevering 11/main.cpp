//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include <iostream>
#include <string>
#include "iterator.h"
#include "Person.h"
#include "LinkedList.h"
#include "templatefunctions.h"
#include "TemplateLinkedList.h"
//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{
	iteratorTest();	
	std::cout<<"\n";
	listTest();
	std::cout<<"\n";
	testLinkedList();
	std::cout<<"\n";
	testFunctions();
	std::cout<<"\n";
	testTemplateLinkedList();
	std::cout<<"\n";

	std::cout<<"Type to exit: ";
	std::string end{""};
	std::cin>>end;


}

//------------------------------------------------------------------------------
