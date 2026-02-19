#include "game.h"
#include <iostream>

using namespace std;

Game::Game() : currentPlayerIdx(0), isGameRunning(true) {}

void Game::setup() {
    deck.fill();
    deck.shuffle();

    // Создаем двух игроков
    players.push_back(Player()); 
    players.push_back(Player()); 

    // Раздаем карты
    for (int i = 0; i < 7; i++) {
        for (int p = 0; p < players.size(); p++) {
            players[p].addCard(deck.draw());
        }
    }

    // Стартовая карта (не должна быть черной)
    tableCard = deck.draw();
    while (tableCard.getColor() == "Black") {
        tableCard = deck.draw();
    }
}

void Game::play() {
    while (isGameRunning) {
        // Очистка экрана (визуальная)
        cout << string(20, '\n'); 
        cout << "========================================" << endl;
        cout << "КАРТА НА СТОЛЕ: ";
        tableCard.Print(); 
        cout << "========================================" << endl;

        Player& currentPlayer = players[currentPlayerIdx];
        cout << "СЕЙЧАС ХОДИТ ИГРОК №" << currentPlayerIdx << endl;
        currentPlayer.showHand();

        int choice;
        cout << "\nВыбери номер карты (или -1, чтобы взять из колоды): ";
        cin >> choice;

        if (choice == -1) {
            // Игрок берет карту и ход ПЕРЕДАЕТСЯ
            Card drawn = deck.draw();
            cout << "Вы взяли карту: ";
            drawn.Print();
            currentPlayer.addCard(drawn);
            
            // Переход хода
            currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
            continue; 
        } 

        if (choice >= 0 && choice < currentPlayer.getSize()) {
            Card chosenCard = currentPlayer.getCard(choice);

            if (chosenCard.CanBePlayedOn(tableCard)) {
                // ПРАВИЛЬНЫЙ ХОД
                tableCard = chosenCard;
                currentPlayer.removeCard(choice);

                // Если победа
                if (currentPlayer.getSize() == 0) {
                    cout << "ПОЗДРАВЛЯЕМ! ИГРОК №" << currentPlayerIdx << " ВЫИГРАЛ!" << endl;
                    isGameRunning = false;
                    break;
                }

                int effect = tableCard.getIdNumberCard();

                // Обработка Wild (черных карт)
                if (tableCard.getColor() == "Black") {
                    cout << "Выберите цвет (Red, Yellow, Green, Blue): ";
                    string newColor; 
                    cin >> newColor;
                    tableCard.setColor(newColor);
                }

                // Логика спецэффектов (Skip=10, Rev=11, +2=12, +4=14)
                // Если спецкарта, то индекс меняется ЕЩЕ РАЗ (пропуск хода)
                if (effect == 10 || effect == 11) {
                    cout << "СЛЕДУЮЩИЙ ИГРОК ПРОПУСКАЕТ ХОД!" << endl;
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }
                else if (effect == 12) {
                    cout << "СЛЕДУЮЩИЙ БЕРЕТ +2 И ПРОПУСКАЕТ ХОД!" << endl;
                    int next = (currentPlayerIdx + 1) % players.size();
                    players[next].addCard(deck.draw());
                    players[next].addCard(deck.draw());
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }
                else if (effect == 14) {
                    cout << "WILD +4! СЛЕДУЮЩИЙ БЕРЕТ 4 КАРТЫ!" << endl;
                    int next = (currentPlayerIdx + 1) % players.size();
                    for(int i=0; i<4; i++) players[next].addCard(deck.draw());
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }

                // Обычный переход хода после успешного действия
                currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
            } 
            else {
                // ОШИБОЧНЫЙ ХОД - Повтор без смены индекса
                cout << "\033[31mЭтой картой нельзя ходить! Попробуй выбрать другую.\033[0m" << endl;
                cout << "Нажми Enter, чтобы продолжить...";
                cin.ignore(); cin.get();
                // Мы не меняем currentPlayerIdx, поэтому цикл начнется заново для того же игрока
            }
        } else {
            cout << "Неверный ввод! Попробуй снова." << endl;
            cin.ignore(); cin.get();
        }
    }
}