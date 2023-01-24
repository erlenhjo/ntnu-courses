#include "MiniDAK.h"




bool is_inside_rectangle(int x, int y, int r_x, int r_y, int r_width, int r_height){
    return (x>r_x && x<(r_x+r_width) && y>r_y && y<(r_y+r_height));
}

bool is_inside_circle(int x, int y, int c_x, int c_y, int c_rad){
    return((x-c_x)*(x-c_x)+(y-c_y)*(y-c_y)<c_rad*c_rad);
}

Color string_to_color(string col){
    if(colors.find(col)!=colors.end()){
        return colors.at(col);
    }
    else{
        throw color_error(col);
    }
}

string color_to_string(Color color){
    for(auto c:colors){
        if(c.second==color){
            return c.first;
        }
    }
    return "unknown color";
}

string DAKRectangle::to_string() const{
    stringstream s;

    s<<"rect ";
    s<<color_to_string(get_color())<<" ";
    s<<rect.point(0).x<<" ";
    s<<rect.point(0).y<<" ";
    s<<rect.width()<<" ";
    s<<rect.height()<<" ";
    
    return s.str();
}


bool DAKRectangle::is_inside(Point p) const{
    return is_inside_rectangle(p.x,p.y,rect.point(0).x,rect.point(0).y,rect.width(),rect.height());
}

void MiniDAK::on_enter_pressed(){
    string command;
    try{
        command=cmd_box.get_string();
        do_command(command);
        cmd_box.clear_value();
    }
    catch(...){
        cerr<<"Command: "<<command<<"resulted in error.\n";
    }
}

void MiniDAK::on_mouse_click(int x,int y){
    mouse=Point{x,y};
    selected_shape=-1;
    unsigned int i{0};
    for(auto s:shapes){
        if(s->is_inside(Point{x,y})){
            selected_shape=i;
        }
        ++i;
    }
}

void MiniDAK::on_mouse_drag(int x, int y){
    if(selected_shape!=-1){
        shapes[selected_shape].move(x-mouse.x,y-mouse.y);
        mouse=Point{x,y};
    }
}

void MiniDAK::save(string filename){
    ofstream ofs{filename};
    for(auto s: shapes){
        ofs<<s->to_string();
    }
}

void MiniDAK::load(string filename){
    ifstream ifs{filename};
    if(!ifs){
        throw "Could not open file: "+filename+"\n";
    }
    if(ifs.eof()){
        return;
    }
    int i{1};
    do{
        try{
            char* s;
            ifs.getline(s,256);
            do_command(s);
        }
        catch(...){
            throw "Error in competing command on line "+to_string(i)+" i "+filename+".\n";
        }
        i++;
    } while(!ifs.eof());
}

void MiniDAK::do_command(string cmd){
    try{
        stringstream s{cmd};
        string type;
        s>>type;
        if(type=="rect"){
            string color;
            Color col=Color::blue;
            int x;
            int y;
            int w;
            int h;
            s>>color;
            col=string_to_color(color);
            s>>x>>y>>w>>h;
            add_shape(new DAKRectangle{Point{x,y},w,h});
        }
        else if(type=="save"){
            string filename;
            s>>filename;
            save(filename);
        }
        else{
            throw;
        }
    }
    catch(...){
        throw "Error: Bad command.\n";
    }
}