#pragma once
#include <vector>
#include "player.h"
#include "desk.h" // У тебя класс называется Desk

class Game {
private:
    Desk deck;
    std::vector<Player> players;
    Card tableCard;
    int currentPlayerIdx;
    bool isGameRunning;

public:
    Game();
    void setup();
    void play();
};