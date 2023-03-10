#pragma once
#include "std_lib_facilities.h"
enum class Suit {clubs,diamonds,hearts,spades};
enum class Rank {two=2,three,four,five,six,
            seven,eight,nine,ten,jack,
            queen,king,ace};

const map<Rank,string> rankMap{{Rank::two,"Two"},
{Rank::three,"Three"},{Rank::four,"Four"},
{Rank::five,"Five"},{Rank::six,"Six"},
{Rank::seven,"Seven"},{Rank::eight,"Eight"},{Rank::nine,"Nine"},
{Rank::ten,"Ten"},{Rank::jack,"Jack"},
{Rank::queen,"Queen"},{Rank::king,"King"},{Rank::ace,"Ace"}};

const map<Suit,string> suitMap{{Suit::clubs,"Clubs"},
    {Suit::diamonds,"Diamonds"},{Suit::hearts,"Hearts"},
    {Suit::spades,"Spades"}};

string suitToString(Suit suit);
string rankToString(Rank rank);

class Card {
private:
    Suit s;
    Rank r;
public:
    Card(Suit suit, Rank rank);
    Suit getSuit();
    Rank getRank();
    string toString();
    string toStringShort();
};

Suit operator++(Suit& s);

Rank operator++(Rank& r);