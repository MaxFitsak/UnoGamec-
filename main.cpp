#include <iostream>
#include "game.h"


int main() {
    setlocale(0, "");

    Game myGame;
    myGame.setup();
    myGame.play();
    return 0;
}