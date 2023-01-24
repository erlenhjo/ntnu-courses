#pragma once


#include <string>
#include <map>
#include <stdexcept>

#include "std_lib_facilities.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"

using namespace std;
using namespace Graph_lib;


bool is_inside_rectangle(int x, int y, int r_x, int r_y, int r_width, int r_height);
bool is_inside_circle(int x, int y, int c_x, int c_y, int c_rad);



const map<string,Color> colors = {
    {"red",Color::red},{"blue",Color::blue}};

Color string_to_color(string col);

class color_error{
    string color;
    public:
    color_error(string col):color(col){}
    string what(){return "Could not find: "+color+"\n";}
};

string color_to_string(Color color);

class DAKShape {
    protected:
        Shape &shape; // The underlying Shape to draw
        DAKShape(Shape &s) : shape{ s } { }
    public:
        virtual bool is_inside(const Point xy) const = 0;
        virtual string to_string() const = 0;
        virtual ~DAKShape() { }
        void attach_to(Graph_lib::Window & win) { win.attach(shape); }
        void move(int dx, int dy) { shape.move(dx, dy); }
        void set_color(Color c) { shape.set_fill_color(c); }
        Color get_color() const { return shape.fill_color(); }
};

class DAKRectangle : public DAKShape{
    private:
        Rectangle rect;

    public: 
        DAKRectangle(Point xy, int ww, int hh) : rect{xy,ww,hh},DAKShape{rect}{}
        string to_string() const override;
        bool is_inside(Point p) const override;
};

class DAKCircle : public DAKShape{
    private:
        Circle circ;

    public: 
        DAKCircle(Point xy,int r) : circ{xy,r},DAKShape{circ}{}
        string to_string();
        bool is_inside(Point p);
};



class MiniDAK : public Graph_lib::Window {
private:
In_box cmd_box; // input box for commands
Vector_ref<DAKShape> shapes; // vector of shapes in the drawing                
int selected_shape; // index into shapes or ‐1 if none are selected
Point mouse; // mouse position
public:
MiniDAK(int w, int h);
void add_shape(DAKShape *shape);//adds a shape to the window (stored in shapes)
int handle(int event); // handle events (See text)                             
void on_enter_pressed();  
void on_mouse_click(int x, int y);
void on_mouse_drag(int x, int y);
void save(string filename);
void load(string filename);
void do_command(string command);
};

