#include "std_lib_facilities.h"
#include "CardDeck.h"
#include "Card.h"
#include "cstdlib"

CardDeck::CardDeck(){
    Suit s=Suit::clubs;
    Rank r=Rank::two;
    for(int i=0; i<4; ++i){
        for(int j=0;j<13;++j){
            Card c{s,r};
            cards.push_back(c);
            ++r;
        }
        ++s;
    }
}

void CardDeck::print(){
    for(int i=0;i<static_cast<int>(cards.size());++i){
        cout<<cards[i].toString()<<"\n";
    }
}
void CardDeck::printShort(){
    for(int i=0;i<static_cast<int>(cards.size());++i){
        cout<<cards[i].toStringShort()<<"\t";
        if(i%13==12){cout<<"\n";}
    }
}
void CardDeck::swap(int a, int b){
    Card Temp=cards[a];
    cards[a]=cards[b];
    cards[b]=Temp;
}
void CardDeck::shuffle(){
    int s=cards.size();
    for(int i=0;i<1000;++i){
        int a=rand()%s;
        int b=rand()%s;
        swap(a,b);
    }
}
Card CardDeck::drawCard(){
    Card card=cards.back();
    cards.pop_back();
    return card;
}
