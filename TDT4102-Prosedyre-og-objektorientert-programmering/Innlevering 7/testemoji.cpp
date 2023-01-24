#include "Simple_window.h"
#include "Emoji.h"
#include "testemoji.h"

void testEmoji()
{
	using namespace Graph_lib;

	const Point tl{100, 100};
	const string win_label{"Emoji factory"};
	Simple_window win{tl, xmax, ymax, win_label};

	EmptyFace empty{Point{100,100},emojiRadius};
	empty.attach_to(win);
	SmilingFace smiley{Point{200,100},emojiRadius};
	smiley.attach_to(win);
	SadFace sad{Point{300,100},emojiRadius};
	sad.attach_to(win);
	AngryFace angry{Point{400,100},emojiRadius};
	angry.attach_to(win);
	WinkingFace wink{Point{500,100},emojiRadius};
	wink.attach_to(win);
	SurprisedFace wow{Point{600,100},emojiRadius};
	wow.attach_to(win);

	win.wait_for_button();
}
