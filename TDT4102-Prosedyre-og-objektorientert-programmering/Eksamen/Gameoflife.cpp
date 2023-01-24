#include <algorithm>
#include <exception>
#include <iostream>
#include <vector>
#include <cassert>

#include "GUI.h"
#include "Gameoflife.h"
#include "Graph.h"
#include "Window.h"

#include "FL/fl_ask.H"

using namespace Graph_lib;


Cell::Cell(Point pos, int size)
	: state(State::Dead), rect{std::make_shared<Rectangle>(pos, size, size)}
{
	// Do not show the border of the cell
	rect->set_color(border_hide);

	// Update the graphical state based on the current state
	update();
}

// TASK
int Cell::get_value() const
{
	// BEGIN: C1
	return static_cast<int>(state);
	// END: C1
}

// TASK
void Cell::update()
{
	// BEGIN: C2
	rect->set_fill_color(colors[get_value()]);
	// END: C2
}

// TASK
void Cell::kill()
{
	// BEGIN: C3
	state=State::Dead;
	update();
	// END: C3
}

// TASK
void Cell::resurrect()
{
	// BEGIN: C4
	state=State::Live;
	update();
	// END: C4
}

// TASK
void Cell::set_state(char c)
{
	// BEGIN: C5
	state=char_to_state.at(c);
	update();
	// END: C5
}

// TASK
std::istream& operator>>(std::istream& is, Cell& cell)
{
	// BEGIN: C6
	char c;
	is>>c;
	cell.set_state(c);
	return is;
	// END: C6
}

// TASK
bool Cell::is_alive() const
{
	// BEGIN: C7
	if(state==State::Live) return true;
	else return false;
	// END: C7
}

// TASK
char Cell::as_char() const
{
	// BEGIN: C8
	return chars.at(get_value());
	// END: C8
}

// TASK
Gameoflife::Gameoflife(int x_cells,
                       int y_cells,
                       const std::string& window_title)
	: Window{x_cells * cell_size + 4 * button_width + 2 * margin,
             y_cells * cell_size + 2 * margin,
             window_title},
	  x_cells{x_cells},
	  y_cells{y_cells}
{
	// Provided (asserts and attach() calls)
	// Asserts are here to make sure any unintended changes to
	// compile-time constants makes the exercise less hard to debug.
	assert(x_cells > 0);
	assert(y_cells > 0);
	assert(button_width > 0);
	assert(margin > 0);

	attach(step_btn);
	attach(steps_input);

	attach(load_btn);
	attach(save_btn);
	attach(filename_input);

	attach(toggle_gridlines_btn);
	attach(play_pause_btn);

	// Provided
	// We do not want the window or its children widgets (button, inputs,
	// etc.) to be resizable. This only leads to possible confusion and
	// frustration. If you struggle with a window that is too large/too
	// small, modify the `cell_size` variable at the top of Gameoflife.h so
	// that it suits your screen resolution and size.
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());

	// BEGIN: G1
	for(int y{0};y<y_cells;++y){
		get_current_grid().push_back({});
		for(int x{0};x<x_cells;++x){
			get_current_grid().back().push_back(Cell{Point{margin+x*cell_size,margin+y*cell_size},cell_size});
			get_current_grid().back().back().attach_to(*this);
		}
	}
	get_scratch_grid()=get_current_grid();
	// END: G1
	load("glider.cgol");
}

// TASK
std::istream& operator>>(std::istream& is, Gameoflife& gameoflife)
{
	// BEGIN: G2
	char newline;
	for(int y{0};y<gameoflife.y_cells;++y){
		for(int x{0};x<gameoflife.x_cells;++x){
			is>>gameoflife.get_current_grid()[y][x];
		}
	}

	gameoflife.get_scratch_grid()=gameoflife.get_current_grid();

	return is;
	// END: G2
}

// TASK
void Gameoflife::load(const std::string& filename)
{
	// BEGIN: G3
	ifstream file{filename};
	if(!file){
		throw runtime_error("Could not load a Game of life state from "+filename);
	}
	
	file>>*this;

	
	
	if(!file){
		throw runtime_error("Could not load a Game of life state from "+filename);
	} //to check if the reading worked.
	redraw();
	
	
	// END: G3
}

// TASK
void Gameoflife::step()
{
	// BEGIN: G4
	for(int y{0};y<y_cells;++y){
		for(int x{0};x<x_cells;++x){
			int neighbors{0};
			
			for(int j{-1};j<2;++j){
				for(int i{-1};i<2;++i){
					if (i==0&&j==0) continue;
					neighbors+=get_current_grid()[(y+i+y_cells)%y_cells][(x+j+x_cells)%x_cells].get_value();
				}
			}
			

			if(get_current_grid()[y][x].get_value()==1){
				if(neighbors==2||neighbors==3) get_scratch_grid()[y][x].resurrect();
				else get_scratch_grid()[y][x].kill();
			}
			else{
				if(neighbors==3) get_scratch_grid()[y][x].resurrect();
				else get_scratch_grid()[y][x].kill();
			}
			
		}
	}
	current_grid=scratch_grid;
	scratch_grid=static_cast<int>(!current_grid);
	// END: G4
}

// TASK
void Gameoflife::step(int steps)
{
	// BEGIN: G5
	for(int s{0};s<steps;++s){
		step();
	}
	redraw();
	// END: G5
}

// TASK
Cell* Gameoflife::cell_at_pos(Point pos)
{
	// BEGIN: E1
	int x=(pos.x-margin)/cell_size;
	int y=(pos.y-margin)/cell_size;
	if(x<x_cells && y<y_cells) return &get_current_grid()[y][x];
	else return nullptr;
	// END: E1
}

// TASK
void Cell::toggle()
{
	// BEGIN: E2
	if(state==State::Live) state=State::Dead;
	else state=State::Live;
	update();
	// END: E2
}

// TASK
bool Gameoflife::toggle_cell(Point pos)
{
	// BEGIN: E3
	if(cell_at_pos(pos)!=nullptr){
		cell_at_pos(pos)->toggle();
		redraw();
		return true;
	}
	else return false;
	// END: E3
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
// The following code is provided as part of the exam handout
// and should _not_ be modified.

// Provided
void Cell::toggle_border()
{
	// Either visible or invisible border lines,
	// based on current visibility state
	Color new_grid_color = show_border ? border_hide : border_show;
	rect->set_color(new_grid_color);
	show_border = !show_border;
}

// Provided - same as ex7
void Cell::attach_to(Window& win) { win.attach(*rect); }

// Provided
std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
	return os << cell.as_char();
}

// Provided
void Gameoflife::save(const std::string& filename)
{
	// We do not want anyone to overwrite their
	// source code files. Make sure the last characters
	// are ".cgol".
	constexpr std::string_view ext = ".cgol";
	if (filename.size() < ext.size() ||
	    filename.substr(filename.size() - 5, 5) != ext) {
		throw std::runtime_error{"'" + filename +
		                         "' does not have the correct file extension: "
		                         "'.cgol' or is too short."};
	}

	std::ofstream ofs{filename};
	if (!ofs) {
		throw std::runtime_error{"Could not save the CGoL state to '" +
		                         filename + "'."};
	}

	ofs << *this;
}

// Provided
std::ostream& operator<<(std::ostream& os, const Gameoflife& gameoflife)
{
	for (auto& row : gameoflife.get_current_grid()) {
		for (auto&& cell : row) {
			os << cell;
		}
		os << '\n';
	}

	return os;
}

// Provided
void Gameoflife::step_pressed()
{
	int steps = std::clamp(steps_input.get_int(), min_steps, max_steps);
	step(steps);
}

// Provided
void Gameoflife::load_state()
{
	std::string filename = filename_input.get_string();
	try {
		load(filename);
	} catch (const std::runtime_error& e) {
		alert(e.what());
	}
}

// Provided
void Gameoflife::save_state()
{
	std::string filename = filename_input.get_string();
	try {
		save(filename);
	} catch (const std::runtime_error& e) {
		alert(e.what());
	}
}

// Provided
Gameoflife::Grid& Gameoflife::get_current_grid() { return grid[current_grid]; }
Gameoflife::Grid& Gameoflife::get_scratch_grid() { return grid[scratch_grid]; }
const Gameoflife::Grid& Gameoflife::get_current_grid() const
{
	return grid[current_grid];
}
const Gameoflife::Grid& Gameoflife::get_scratch_grid() const
{
	return grid[scratch_grid];
}

// Provided
// Show a pop-up alert box with `message`
void Gameoflife::alert(const std::string& message)
{
	fl_alert("%s", message.c_str());
}

// Provided
// Show or hide the grid lines
void Gameoflife::toggle_gridlines()
{
	for (auto& row : get_current_grid()) {
		for (auto& cell : row) {
			cell.toggle_border();
		}
	}

	redraw();
}

// Provided
// Handle events.
// If it's a mouse button click event outside Widgets,
// try to handle the event with grid_click()
int Gameoflife::handle(int event)
{
	if (int handled = Fl_Group::handle(event) > 0) {
		// Event has been passed on to a child widget
		return handled;
	} else if (event == FL_PUSH) {
		// Handle mouse button clicks outside the widgets
		return click_handler(Point{Fl::event_x(), Fl::event_y()});
	} else {
		return Fl_Widget::handle(event);
	}
}

// Provided
// The Gameoflife instance's mouse-click handler.
int Gameoflife::click_handler(Point pos) { return toggle_cell(pos); }

// Provided
void Gameoflife::play_pause()
{
	if (playing.load()) {
		playing.store(false);
		worker.join();
	} else {
		playing.store(true);
		worker = thread(&Gameoflife::animate, ref(*this));
	}
}

// Provided
void Gameoflife::animate()
{
	while (playing.load()) {
		Fl::lock();
		step(1);
		Fl::unlock();
		Fl::awake();

		this_thread::sleep_for(animation_interval);
	}
}

// Provided
Gameoflife::~Gameoflife()
{
	// Clean up animation thread if it is playing to avoid
	// ABI abort trap messages.
	playing.store(false);
	if (worker.joinable())
		worker.join();
}
