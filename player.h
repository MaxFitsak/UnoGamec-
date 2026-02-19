#pragma once
#include "card.h" 
#include <vector>

class Card;

class Player {
private:
    std::vector<Card> hand; 
public:
    void addCard(Card newCard);
    void showHand();
    void removeCard(int); 
    int getSize(){ return hand.size(); };
    Card getCard(int index);
};