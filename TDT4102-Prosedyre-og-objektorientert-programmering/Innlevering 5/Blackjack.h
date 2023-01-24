#pragma once
#include "Card.h"
#include "CardDeck.h"
#include "std_lib_facilities.h"

class Blackjack{
    private:
        CardDeck deck;
        vector<Card> playerCards;
        vector<Card> dealerCards;
        bool playerBlackjack;
        bool dealerBlackjack;
        
    public:
        Blackjack();
        bool queryPlayerDraw();
        bool decideDealerDraw();
        int getDealerScore();
        int getPlayerScore();
        bool checkPlayerBlackjack();
        bool checkDealerBlackjack();
        bool checkPlayerVictory();
        void showBoardState();
        void showAll();
        void play();
};