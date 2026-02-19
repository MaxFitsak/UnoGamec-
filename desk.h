#pragma once
#include <vector>
#include "card.h"
using namespace std;

class Desk{
private:
    vector <Card> allCards;

public:
    void fill();
    void shuffle();
    Card draw();
};