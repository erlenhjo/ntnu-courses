#include "Card.h"

string suitToString(Suit suit){    
    return suitMap.at(suit);
}
string rankToString(Rank rank){
    return rankMap.at(rank);
}

Card::Card(Suit suit,Rank rank): s{suit} ,r{rank}
{}
Suit Card::getSuit(){
    return s;
}
Rank Card::getRank(){
    return r;
}
string Card::toString(){
    return rankToString(r)+" of "+suitToString(s);
}
string Card::toStringShort(){
    if(static_cast<int>(r)==14){
        return suitToString(s)[0]+static_cast<string>("A");
    } else{
        return suitToString(s)[0]+to_string(static_cast<int>(r));
    }
}

Suit operator++(Suit& s){
    s = (s==Suit::spades) ? Suit::clubs : Suit(static_cast<int>(s)+1);
    return s;
}

/*
Suit operator++(Suit& s){
    if (s==Suit::spades){
        s=Suit::clubs;
    } else{
        s=Suit(static_cast<int>(s)+1);
    }
    return s;
}

*/

Rank operator++(Rank& r){
    r=(r==Rank::ace)?Rank::two:Rank(static_cast<int>(r)+1);
    return r;
}