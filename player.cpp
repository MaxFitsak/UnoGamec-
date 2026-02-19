#include "player.h"
#include "card.h"
#include <iostream>


void Player::addCard(Card newCard) {
    hand.push_back(newCard);
}

void Player::showHand() {
    for (int i = 0; i < hand.size(); i++) {
        std::cout << i << ": ";
        hand[i].Print(); 
    }
}

void Player::removeCard(int index){
    hand.erase(hand.begin() + index);
}

Card Player::getCard(int index) { return hand[index]; }