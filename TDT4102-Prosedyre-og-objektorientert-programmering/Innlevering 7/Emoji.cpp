#include "Emoji.h"

using namespace Graph_lib;

void Face::attach_to(Graph_lib::Window& win){
		win.attach(circle);
	};

EmptyFace::EmptyFace(Point c,int r):
    Face{c,r}, 
    leftEye{Point{c.x-r/4,c.y-r/4},r/5},
    rightEye{Point{c.x+r/4,c.y-r/4},r/5}
    {
        leftEye.set_fill_color(Color::green);
        leftEye.set_color(Color::black);
        rightEye.set_fill_color(Color::green);
        rightEye.set_color(Color::black);
}

void EmptyFace::attach_to(Graph_lib::Window& win){
    Face::attach_to(win);
    win.attach(leftEye);
    win.attach(rightEye);
    return;
}

SmilingFace::SmilingFace(Point c, int r):
    EmptyFace{c,r},
    smile{Point{c.x,c.y+r/4},r*6/5,r*2/3,180,360}
    {
        smile.set_color(Color::black);
}

void SmilingFace::attach_to(Graph_lib::Window& win){
    EmptyFace::attach_to(win);
    win.attach(smile);
    return;
}

SadFace::SadFace(Point c, int r):
    EmptyFace{c,r},
    sadMouth{Point{c.x,c.y+r*2/3},r*6/5,r*2/3,0,180}
    {
        sadMouth.set_color(Color::black);
}

void SadFace::attach_to(Graph_lib::Window& win){
    EmptyFace::attach_to(win);
    win.attach(sadMouth);
    return;
}

AngryFace::AngryFace(Point c, int r):
    EmptyFace{c,r},
    leftEyebrow{
        Point{c.x-r/9,c.y-r*4/9},
        Point{c.x-r/2,c.y-r*2/3}},
    rightEyebrow{
        Point{c.x+r/9,c.y-r*4/9},
        Point{c.x+r/2,c.y-r*2/3}},
    angryMouth{Point{c.x,c.y+r*2/3},r*6/5,r*2/3,30,150}
    {
        angryMouth.set_color(Color::black);
        leftEyebrow.set_color(Color::black);
        rightEyebrow.set_color(Color::black);
}
void AngryFace::attach_to(Graph_lib::Window& win){
    EmptyFace::attach_to(win);
    win.attach(leftEyebrow);
    win.attach(rightEyebrow);
    win.attach(angryMouth);
    return;
}

WinkingFace::WinkingFace(Point c, int r):
    Face{c,r},
    smile{Point{c.x,c.y+r/4},r*6/5,r*2/3,180,360},
    leftEye{Point{c.x-r/4,c.y-r/4},r/5},
    rightWink{Point{c.x+r/4,c.y-r/7},r*4/9,r*2/5,0,170}
    {
        smile.set_color(Color::black);
        leftEye.set_color(Color::black);
        leftEye.set_fill_color(Color::green);
        rightWink.set_color(Color::black);
        rightWink.set_style(Line_style(Line_style::solid ,2));
}

void WinkingFace::attach_to(Graph_lib::Window& win){
    Face::attach_to(win);
    win.attach(smile);
    win.attach(leftEye);
    win.attach(rightWink);
    return;
}

SurprisedFace::SurprisedFace(Point c,int r):
    EmptyFace{c,r},
    surprisedMouth{Point{c.x,c.y+r*2/5},r/2,r*1/3}
    {
        surprisedMouth.set_color(Color::black);
        surprisedMouth.set_fill_color(Color::dark_blue);
}

void SurprisedFace::attach_to(Graph_lib::Window& win){
    EmptyFace::attach_to(win);
    win.attach(surprisedMouth);
}