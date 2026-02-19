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
    // 1. Получаем случайное число от системы
    std::random_device rd;
    // 2. Инициализируем генератор Вихрь Мерсенна этим числом
    std::mt19937 g(rd());
    // 3. Перемешиваем вектор от начала до конца
    std::shuffle(allCards.begin(), allCards.end(), g);
}

Card Desk::draw() {
    if (allCards.empty()) {
        // Если карты кончились, можно заново заполнить и перемешать
        fill();
        shuffle();
    }
    Card top = allCards.back();
    allCards.pop_back();
    return top;
}