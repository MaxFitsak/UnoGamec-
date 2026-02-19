#include "card.h"
#include <vector>
#include <iostream>
#include <string>


Card::Card(){ 
    idCard = 0;
    idNUmberCard = 0;
    Color = "Unklow";
    cout << "\033[31mConstructor Creater\033[0m" << endl;
};

Card::Card(int index){
    if(index > 107){
        cout << "\033[31mError index too dig\033[0m" << endl;
        return;
    }
    idCard = index;
    ColorCard();
    NumberCard();
};

void Card::ColorCard(){ 
    if (idCard / 25 == 0){ Color = "Red";}
    else if (idCard / 25 == 1){ Color =  "Yellow"; }
    else if (idCard / 25 == 2){ Color =  "Green"; }
    else if (idCard / 25 == 3){ Color =  "Blue"; }
    else if (idCard / 25 == 4){ Color =  "Black"; }
}

void Card::NumberCard() {
    if (idCard >= 100) {
        if (idCard >= 103) { 
            idNUmberCard = 14;
        } else { 
            idNUmberCard = 13;
        }
        return;
    }

    int localId = idCard % 25;

    if (localId == 0) {
        idNUmberCard = 0;
    } 
    else if (localId >= 1 && localId <= 18) {
        idNUmberCard = (localId + 1) / 2;
    } 
    else if (localId >= 19 && localId <= 20) {
        idNUmberCard = 10; 
    } 
    else if (localId >= 21 && localId <= 22) {
        idNUmberCard = 11;
    } 
    else if (localId >= 23 && localId <= 24) {
        idNUmberCard = 12; 
    }
}

bool Card::isSpecial() const {
    if (idNUmberCard >= 13){ return true; }
    return false;
}

bool Card::CanBePlayedOn(const Card& other) {
    // Черную карту (Wild) можно класть на что угодно
    if (this->Color == "Black") return true;
    
    // Если цвета совпали
    if (this->Color == other.Color) return true;
    
    // Если номера/типы совпали (например, Skip на Skip)
    if (this->idNUmberCard == other.idNUmberCard) return true;
    
    return false;
}

// Добавим этот метод в Card.cpp и Card.h, чтобы менять цвет Wild-карт
void Card::setColor(string newColor) {
    if (Color == "Black") {
        Color = newColor;
    }
}

void Card::Print(){
    cout << CARDS[idCard] << " ";
    cout << Color << " ";
    cout << idNUmberCard << endl;
};