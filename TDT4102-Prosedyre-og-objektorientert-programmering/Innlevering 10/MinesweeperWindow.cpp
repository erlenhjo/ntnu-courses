#include "MinesweeperWindow.h"
#include "ctime"
#include "cstdlib"

MinesweeperWindow::MinesweeperWindow(Point xy, int width, int height, int mines, const string& title) :
	Graph_lib::Window{xy, width*cellSize, (height+1)*cellSize, title}, width{width}, height{height}, mines{mines},
	resultText{Point{(width-5)*cellSize,(height+1)*cellSize-10},""},
	mineText{Point{10,(height+1)*cellSize-10},"Mines remaining: "+to_string(mines)},remainingMines{mines},remainingTiles{width*height},
	endMenu{Point{(width-2)*cellSize,(height)*cellSize},cellSize,cellSize,Menu::horizontal,""}
	//Initialiser medlemsvariabler, bruker konstruktoren til Windowsklassen
{
	attach(resultText);
	attach(mineText);
	endMenu.attach(new Button{Point{0,0},0,0,"R",cb_restart});
	endMenu.attach(new Button{Point{0,0},0,0,"Q",cb_quit});
	attach(endMenu);
	endMenu.hide();
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.push_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize, cb_click });
			attach(tiles.back());
		}
	}
	srand(time(nullptr));
	//Legg til miner paa tilfeldige posisjoner
	for(int i=0;i<mines;++i){
		int cellNum=rand()%(width*height);
		if(tiles[cellNum].get_isMine()){
			--i;
		}
		else{
			tiles[cellNum].set_isMine(true);
		}
	}

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}


vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}

	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	if(hasLost || hasWon){
		return;
	}
	if(at(xy).getState()==Cell::closed){
		at(xy).open();
		--remainingTiles;
		if(!(at(xy).get_isMine())){
			int adjMines=countMines(adjacentPoints(xy));
			if(adjMines>0){
				at(xy).setAdjMines(adjMines);
			}
			else{
				for(Point p:adjacentPoints(xy)){
					if(at(p).getState()!=Cell::open){
						openTile(p);
					}
				}
			}
			if(remainingTiles==mines && !hasLost){
				hasWon=true;
				resultText.set_label("You won! :)");
				endMenu.show();
				redraw();
				for(auto t:tiles){
				if(t->get_isMine() && t->getState()!=Cell::flagged){
					t->flag();
					}
				}
			}
		}
		else if(!hasWon){
			hasLost=true;
			resultText.set_label("You lost :(");
			endMenu.show();
			redraw();
			for(auto t:tiles){
				if(t->get_isMine()){
					t->open();
				}
			}
		}
	}
}

void MinesweeperWindow::flagTile(Point xy) {
	if(at(xy).getState()==Cell::closed){
		--remainingMines;
		at(xy).flag();
	}else if(at(xy).getState()==Cell::flagged){
		++remainingMines;
		at(xy).flag();
	}
	mineText.set_label("Mines remaining: "+to_string(remainingMines));
	redraw();
}

//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk/trykke med to fingre paa mac
void MinesweeperWindow::click()
{
	Point xy{Fl::event_x(), Fl::event_y()};

	MouseButton mb = static_cast<MouseButton>(Fl::event_button());

	if (!inRange(xy)) {
		return;
	}

	switch (mb) {
	case MouseButton::left:
		openTile(xy);
		break;
	case MouseButton::right:
		flagTile(xy);
		break;
	}

	flush();
}

int MinesweeperWindow::countMines(vector<Point> points) const{
	int adjMines{0};
	for(Point p:points){
		if(at(p).get_isMine()){
			++adjMines;
		}
	}
	return adjMines;
}

void MinesweeperWindow::cb_quit(Address,Address pw){
    reference_to<MinesweeperWindow>(pw).hide();
}
void MinesweeperWindow::cb_restart(Address,Address pw){
	reference_to<MinesweeperWindow>(pw).restart();
}

void MinesweeperWindow::restart(){
	hasWon=false;
	hasLost=false;
	endMenu.hide();
	resultText.set_label("");
	remainingMines=mines;
	mineText.set_label("Mines remaining: "+to_string(remainingMines));
	remainingTiles=width*height;
	for(auto t:tiles){
		t->reset();
	}
	//Legg til miner paa tilfeldige posisjoner
	for(int i=0;i<mines;++i){
		int cellNum=rand()%(width*height);
		if(tiles[cellNum].get_isMine()){
			--i;
		}
		else{
			tiles[cellNum].set_isMine(true);
		}
	}
}