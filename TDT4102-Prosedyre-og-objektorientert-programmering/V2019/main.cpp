//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "Vector2d.h"

#include <vector>
#include <iostream>

//------------------------------------------------------------------------------'

// C++ programs start by executing the function main
int main()
{
	std::vector<Vector2d> track ={{1.0, 0.5}, {2.0, 0.0}, {1.0, 1.0}, {-1.0, 2.0}, {-1.0, 0.0}, {-1.0, -1.0}};
    trackStats(track);
	track ={{1.0, 0.5}, {2.0, 7.0}, {5.0, 1.0}, {-1.0, 2.0}, {-1.0, 0.0}, {-1.0, -1.0}};
    track=cleanTrack(track);
	for(auto v:track){
		std::cout<<v<<"\n";
	}
	int b = 10 / a‐‐;

}

//------------------------------------------------------------------------------
