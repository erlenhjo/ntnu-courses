//
// This is example code from Chapter 2.2 "The classic first program" of
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
// 
// keep_window_open() added for TDT4102, excercise 0

// This program outputs the message "Hello, World!" to the monitor

#include "std_lib_facilities.h"
#include "Card.h"
#include "CardDeck.h"
#include "cstdlib"
#include "ctime"
#include "Blackjack.h"

//------------------------------------------------------------------------------'

// Mye lettere å kode med?
// ???

// C++ programs start by executing the function main
int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Rank r = Rank::king;
	Suit s = Suit::hearts;
	string rank = rankToString(r);
	string suit = suitToString(s);
	cout << "Rank: " << rank << " Suit: " << suit << '\n';
	
	Card c{Suit::spades,Rank::ace};
	cout << c.toString() << '\n';
	cout << c.toStringShort() << '\n';

	CardDeck deck;
	deck.print();
	deck.printShort();
	cout<<"\n\n\n";
	deck.shuffle();
	deck.printShort();
	Card card=deck.drawCard();
	cout<<card.toString()<<"\n";
	
	cout<<"\n\n\n\n\n\n\n\n";
	while(true){
		string answer;
		cout<<"Do you want to play Blackjack? (y/n): ";
		cin>>answer;
		if(answer=="y"){
			Blackjack game;
			game.play();
		}else{
			break;
		}
	}
}

//------------------------------------------------------------------------------
