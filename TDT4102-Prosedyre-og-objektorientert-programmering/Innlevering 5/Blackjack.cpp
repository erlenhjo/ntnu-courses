#include "Card.h"
#include "CardDeck.h"
#include "Blackjack.h"
#include "std_lib_facilities.h"

Blackjack::Blackjack(){
    
    CardDeck deck;
    deck.shuffle();
    playerCards.push_back(deck.drawCard());
    dealerCards.push_back(deck.drawCard());
    playerCards.push_back(deck.drawCard());
    dealerCards.push_back(deck.drawCard());
    playerBlackjack=checkPlayerBlackjack();
    dealerBlackjack=checkDealerBlackjack();
}
bool Blackjack::queryPlayerDraw(){
    string answer="";
    cout<<"Continue drawing (y/n): ";
    cin>>answer;
    while(answer!="y"&&answer!="n"){
        cout<<"Enter y or n: ";
        cin>>answer;
    }
    if(answer=="y"){
        return true;
    }
    return false;    
}
bool Blackjack::decideDealerDraw(){
    if(getDealerScore()<17){
        return true;
    }
    return false;
}
int Blackjack::getDealerScore(){
    int score=0;
    int handSize=dealerCards.size();
    bool firstAce=false;
    for(int i=0;i<handSize;++i){
        if(static_cast<int>(dealerCards[i].getRank())==14){
            score+=1;
            firstAce=true;
        }
        else if(static_cast<int>(dealerCards[i].getRank())<10){
            score+=static_cast<int>(dealerCards[i].getRank());
        } 
        else{
            score+=10;
        }
    }
    if(firstAce&&(score+10<=21)){
        score+=10;
    }
    return score;
}
int Blackjack::getPlayerScore(){
    int score=0;
    int handSize=playerCards.size();
    bool firstAce=false;
    for(int i=0;i<handSize;++i){
        if(static_cast<int>(playerCards[i].getRank())==14){
            score+=1;
            firstAce=true;
        }
        else if(static_cast<int>(playerCards[i].getRank())<10){
            score+=static_cast<int>(playerCards[i].getRank());
        } 
        else{
            score+=10;
        }
    }
    if(firstAce&&(score+10<=21)){
        score+=10;
    }
    return score;
}
bool Blackjack::checkPlayerBlackjack(){
    if(getPlayerScore()==21&& playerCards.size()==2){
        return true;
    }
    return false;
}
bool Blackjack::checkDealerBlackjack(){
    if(getDealerScore()==21&& dealerCards.size()==2){
        return true;
    }
    return false;
}
bool Blackjack::checkPlayerVictory(){
    if(getPlayerScore()<=21&&getPlayerScore()>getDealerScore()){
        return true;
    } else if(getDealerScore()>21&&getPlayerScore()<=21){
        return true;
    }
    return false;
}
void Blackjack::showBoardState(){
    cout<<"\n\nBoard state:\n";
    cout<<"Dealer cards: "<<dealerCards[0].toStringShort()<<" ";
    for(int i=0;i<static_cast<int>(dealerCards.size())-1;++i){
        cout<<"XX ";
    } 
    cout<<"\n";
    cout<<"Player cards: ";
    for(int i=0; i<static_cast<int>(playerCards.size());++i){
        cout<<playerCards[i].toStringShort()<<" ";
    }
    cout<<"\n\n";
}
void Blackjack::showAll(){
    cout<<"\nBoard state:\n";
    cout<<"Dealer cards: ";
    for(int i=0;i<static_cast<int>(dealerCards.size());++i){
        cout<<dealerCards[i].toStringShort()<<" ";
    } 
    cout<<"\n";
    cout<<"Player cards: ";
    for(int i=0; i<static_cast<int>(playerCards.size());++i){
        cout<<playerCards[i].toStringShort()<<" ";
    }
    cout<<"\n";
}

void Blackjack::play(){
    showBoardState();
    bool playerDone=false;
    if(playerBlackjack&&!dealerBlackjack){
        cout<<"Blackjack!! You won!\n";
        return;
    }
    while(!playerDone&&getPlayerScore()<=21){
        if(queryPlayerDraw()){
            playerCards.push_back(deck.drawCard());
            cout<<"Player draws.\n";
        } else{
            playerDone=true;
            cout<<"Player holds.\n";
        }
        if(decideDealerDraw()){
            dealerCards.push_back(deck.drawCard());
            cout<<"Dealer draws.\n";
        } else{
            cout<<"Dealer holds.\n";
        }
        if(!playerDone){
            showBoardState();
        }
    } 
    while(decideDealerDraw()){
        dealerCards.push_back(deck.drawCard());
        cout<<"Dealer draws.\n";
    }
    showAll();
    cout<<"\nDealer score: "<<getDealerScore()<<"\n";
    cout<<"Player score: "<<getPlayerScore()<<"\n";
    if(checkPlayerVictory()){
        cout<<"You won!\n";
    } else{
        cout<<"You barely lost this time, better try again.\n";
    }

}