#pragma once

// Include Graph_lib library files that holds declarations needed for Window,
// and Shape derivatives.
#include "Graph.h"
#include "GUI.h"



using namespace Graph_lib;

// An abstract class. Concrete classes derived from this base class
// has to implement the member function attach_to().
class Emoji{
	public:
		Emoji(const Emoji&) = delete;
		Emoji& operator=(const Emoji&) = delete;
		Emoji() {}
		virtual void attach_to(Graph_lib::Window&)=0;
		virtual ~Emoji() {}
};

class Face:public Emoji{
	public:
		virtual void attach_to(Graph_lib::Window&) override =0;
		Face(Point c,int r):circle{c,r}{
			circle.set_color(Color::black);
			circle.set_fill_color(Color::yellow);
		}
	private:
		Circle circle;
};

class EmptyFace:public Face{
	public:
		EmptyFace(Point c,int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Circle leftEye;
		Circle rightEye;
};

class SmilingFace:public EmptyFace{
	public:
		SmilingFace(Point c,int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Arc smile;
};

class SadFace:public EmptyFace{
	public:
		SadFace(Point c,int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Arc sadMouth;
};

class AngryFace:public EmptyFace{
	public:
		AngryFace(Point c,int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Line leftEyebrow;
		Line rightEyebrow;
		Arc angryMouth;
};

class WinkingFace:public Face{
	public:
		WinkingFace(Point c, int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Arc smile;
		Circle leftEye;
		Arc rightWink;
};

class SurprisedFace:public EmptyFace{
	public:
		SurprisedFace(Point c,int r);
		void attach_to(Graph_lib::Window&) override;
	private:
		Ellipse surprisedMouth;
};