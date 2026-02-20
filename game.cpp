#include "game.h"
#include <iostream>

using namespace std;

Game::Game() : currentPlayerIdx(0), isGameRunning(true) {}

void Game::setup() {
    deck.fill();
    deck.shuffle();

    players.push_back(Player()); 
    players.push_back(Player()); 

    // Роздача карти
    for (int i = 0; i < 7; i++) {
        for (int p = 0; p < players.size(); p++) {
            players[p].addCard(deck.draw());
        }
    }

    // Стартова карта 
    tableCard = deck.draw();
    while (tableCard.getColor() == "Black") {
        tableCard = deck.draw();
    }
}

void Game::play() {
    while (isGameRunning) {
        cout << string(20, '\n'); 
        cout << "========================================" << endl;
        cout << "Карта на столі: ";
        tableCard.Print(); 
        cout << "========================================" << endl;

        Player& currentPlayer = players[currentPlayerIdx];
        cout << "Зараз ходить ігрок №" << currentPlayerIdx << endl;
        currentPlayer.showHand();

        int choice;
        cout << "\nВибери номер карти (або -1, щоб взяти з колоди): ";
        cin >> choice;

        if (choice == -1) {
            // Ігрок бере карту і хід передаєтся
            Card drawn = deck.draw();
            cout << "Вы взяли карту: ";
            drawn.Print();
            currentPlayer.addCard(drawn);
            
            // перехід хода
            currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
            continue; 
        } 

        if (choice >= 0 && choice < currentPlayer.getSize()) {
            Card chosenCard = currentPlayer.getCard(choice);

            if (chosenCard.CanBePlayedOn(tableCard)) {
                // Привльний хід
                tableCard = chosenCard;
                currentPlayer.removeCard(choice);

                // перевірка на виграш
                if (currentPlayer.getSize() == 0) {
                    cout << "Вітаємо! Ігрок №" << currentPlayerIdx << " Виграв!" << endl;
                    isGameRunning = false;
                    break;
                }

                int effect = tableCard.getIdNumberCard();

                // Обробка карт Wild
                if (tableCard.getColor() == "Black") {
                    cout << "Вибери колір (Red, Yellow, Green, Blue): ";
                    string newColor; 
                    cin >> newColor;
                    tableCard.setColor(newColor);
                }

                // Логика спецэффектов (Skip=10, Rev=11, +2=12, +4=14)
                // Если спецкарта, то индекс меняется ЕЩЕ РАЗ (пропуск хода)
                if (effect == 10 || effect == 11) {
                    cout << "Наступний ігрок пропускає хід!" << endl;
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }
                else if (effect == 12) {
                    cout << "Наступний бере +2 і пропускає хід!" << endl;
                    int next = (currentPlayerIdx + 1) % players.size();
                    players[next].addCard(deck.draw());
                    players[next].addCard(deck.draw());
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }
                else if (effect == 14) {
                    cout << "WILD +4! Наступний бере 4 карти!" << endl;
                    int next = (currentPlayerIdx + 1) % players.size();
                    for(int i=0; i<4; i++) players[next].addCard(deck.draw());
                    currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
                }

                // Обычный переход хода после успешного действия
                currentPlayerIdx = (currentPlayerIdx + 1) % players.size();
            } 
            else {
                // ОШИБОЧНЫЙ ХОД - Повтор без смены индекса
                cout << "\033[31mЦією картою не можна ходити! Попробуй вибрати іншу.\033[0m" << endl;
                cout << "Нажми Enter, щоб продовжити...";
                cin.ignore(); cin.get();
                // Мы не меняем currentPlayerIdx, поэтому цикл начнется заново для того же игрока
            }
        } else {
            cout << "Невірний ввід! Попробуй знову." << endl;
            cin.ignore(); cin.get();
        }
    }
}