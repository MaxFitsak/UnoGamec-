#include "desk.h"
#include <algorithm>
#include <random>

void Desk::fill(){
    for (int i = 0; i < 108; i++)
    {
        allCards.push_back(Card(i));
    }
}

void Desk::shuffle() {
    std::random_device rd; // Отримаємо випадкове число від системи
    std::mt19937 g(rd());// Ініціалізуем генератор Вихирь Мерсенна цим числом
    std::shuffle(allCards.begin(), allCards.end(), g); // Перемішаемо ветор віт початку до кінця
}

Card Desk::draw() {
    if (allCards.empty()) { // Якщо карти закінчились в колоді перемішати з початку
        fill();
        shuffle();
    }
    Card top = allCards.back();
    allCards.pop_back();
    return top;
}